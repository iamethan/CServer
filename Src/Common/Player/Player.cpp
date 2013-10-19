#include "Player.h"
#include "Net/Socket.h"
#include "Packets/PacketFactoryManager.h"
#include "Base/TimeManager.h"
#include "Log/Log.h"
#include "Base/Assertx.h"
#include "Define/LogDefine.h"

Player::Player( BOOL bIsServer )
{
__ENTER_FUNCTION

	m_PID = INVALID_ID ;
	m_UID = INVALID_ID ;
	m_PlayerManagerID = INVALID_ID ;


	m_pSocket = new Socket ;
	Assert( m_pSocket ) ;

	if( bIsServer )
	{
		m_pSocketInputStream = new SocketInputStream( m_pSocket,DEFAULTSOCKETINPUTBUFFERSIZE,64*1024*1024 ) ;
		Assert( m_pSocketInputStream ) ;

		m_pSocketOutputStream = new SocketOutputStream( m_pSocket,DEFAULTSOCKETOUTPUTBUFFERSIZE,64*1024*1024 ) ;
		Assert( m_pSocketOutputStream ) ;
	}
	else
	{
		m_pSocketInputStream = new SocketInputStream( m_pSocket ) ;
		Assert( m_pSocketInputStream ) ;

		m_pSocketOutputStream = new SocketOutputStream( m_pSocket ) ;
		Assert( m_pSocketOutputStream ) ;
	}

	m_IsEmpty		= TRUE ;
	m_IsDisconnect	= FALSE ;

	m_PacketIndex	 = 0 ;

__LEAVE_FUNCTION
}

Player::~Player( )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pSocketInputStream ) ;
	SAFE_DELETE( m_pSocketOutputStream ) ;

	SAFE_DELETE( m_pSocket ) ;

__LEAVE_FUNCTION
}

VOID Player::CleanUp( )
{
__ENTER_FUNCTION

	m_pSocket->close() ;
	m_pSocketInputStream->CleanUp() ;
	m_pSocketOutputStream->CleanUp() ;
	SetPlayerManagerID( INVALID_ID ) ;
	SetUserID( INVALID_ID ) ;
	m_PacketIndex = 0 ;
	SetDisconnect(FALSE) ;


__LEAVE_FUNCTION
}

VOID Player::Disconnect( )
{
__ENTER_FUNCTION

	_MY_TRY
	{
		m_pSocket->close() ;
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

__LEAVE_FUNCTION
}

BOOL Player::IsValid( )
{
__ENTER_FUNCTION

	if( m_pSocket==NULL ) return FALSE ;

	if( !m_pSocket->isValid() ) return FALSE ;


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessInput( )
{
__ENTER_FUNCTION

	if( IsDisconnect() )
		return TRUE ;

	_MY_TRY 
	{
		uint ret = m_pSocketInputStream->Fill( ) ;
		if( (INT)ret <= SOCKET_ERROR )
		{
			GLog::SaveLog( SERVER_ERRORFILE, "[%d] m_pSocketInputStream->Fill ret:%d %s", 
				g_pTimeManager->Time2DWORD(), (INT)ret, MySocketError() ) ;
			return FALSE ;
		}
	} 
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		return FALSE ;
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessCommand( BOOL Option )
{
__ENTER_FUNCTION

	BOOL ret ;

	CHAR header[PACKET_HEADER_SIZE];
	PacketID_t packetID;
	PacketLen_t packetLen;

	CBasePack* pPacket = NULL ;

	if( IsDisconnect( ) )
		return TRUE ;

	_MY_TRY
	{
		if( Option ) 
		{//执行部分选项操作
		}

//每帧可以执行的消息数量上限
#define EXE_COUNT_PER_TICK 12
		for( INT i=0;i<EXE_COUNT_PER_TICK; i++ )
		{
			if( !m_pSocketInputStream->Peek(&header[0], PACKET_HEADER_SIZE) )
			{//数据不能填充消息头
				break ;
			}

			memcpy( &packetID, &header[0], sizeof(PacketID_t) ) ;	
			memcpy( &packetLen, &header[sizeof(PacketID_t)], sizeof(PacketLen_t) );

			if( packetID >= (PacketID_t)PACKET_ID_MAX )
			{//无效的消息类型
				return FALSE ;
			}

			_MY_TRY
			{

				if( m_pSocketInputStream->Length()<PACKET_HEADER_SIZE+packetLen )
				{//消息没有接收全
					break;
				}

				CBasePack* pPacket = g_pPacketFactoryManager->CreatePacket( packetID ) ;
				if( pPacket==NULL )
				{
					return FALSE ;
				}

				//设置消息序列号
				pPacket->uID = packetID;
				pPacket->uBodyLen = packetLen;

				IPacketFactory* pFactory = g_pPacketFactoryManager->GetFactory( packetID );
				if( !pFactory )
				{
					g_pPacketFactoryManager->RemovePacket( pPacket );
					return FALSE;
				}

				ret = pFactory->Read(pPacket, *m_pSocketInputStream);
				if( ret==FALSE )
				{//读取消息内容错误
					g_pPacketFactoryManager->RemovePacket( pPacket ) ;
					return FALSE ;
				}

				BOOL bNeedRemove = TRUE ;
				BOOL bException = FALSE ;

				_MY_TRY
				{
					//修正m_KickTime信息，m_KickTime信息中的值为判断是否需要踢掉
					//客户端的依据
					ResetKick( ) ;

					PACKET_EXE uret = pFactory->Execute(pPacket, this);

					if( uret==PACKET_EXE_ERROR )
					{//出现异常错误，断开此玩家连接
						g_pPacketFactoryManager->RemovePacket( pPacket ) ;
						return FALSE ;
					}
					else if( uret==PACKET_EXE_BREAK )
					{//当前消息的解析执行将停止
					 //直到下个循环时才继续对缓存中的数据进行消息格式
					 //化和执行。
					 //当需要将客户端的执行从一个场景转移到另外一个场景时：
					 //需要在发送转移消息后将执行在本线程中停止。
						g_pPacketFactoryManager->RemovePacket( pPacket ) ;
						break ;
					}
					else if( uret==PACKET_EXE_CONTINUE )
					{//继续解析剩下的消息
					}
					else if( uret==PACKET_EXE_NOTREMOVE )
					{//继续解析剩下的消息，并且不回收当前消息
						bNeedRemove = FALSE ;
					}
					else if( uret == PACKET_EXE_NOTREMOVE_ERROR )
					{
						return FALSE ;
					}
					else
					{//未知的返回值
					}
				}
				_MY_CATCH
				{
					SaveCodeLog( ) ;
					bException = TRUE ;
				}

				if( pPacket && bNeedRemove ) 
					g_pPacketFactoryManager->RemovePacket( pPacket ) ;

				if( bException )
					return FALSE ;
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
				return FALSE ;
			}
		}
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		return FALSE ;
	}



	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::ProcessOutput( )
{
__ENTER_FUNCTION

	if( IsDisconnect( ) )
		return TRUE ;

	_MY_TRY
	{
		uint size = m_pSocketOutputStream->Length() ;
		if( size==0 )
		{
			return TRUE ;
		}

		uint ret = m_pSocketOutputStream->Flush( ) ;
		if( (INT)ret <= SOCKET_ERROR )
		{
			GLog::SaveLog( SERVER_ERRORFILE, "[%d] m_pSocketOutputStream->Flush ret:%d %s", 
				g_pTimeManager->Time2DWORD(), (INT)ret, MySocketError() ) ;
			return FALSE ;
		}
	} 
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		return FALSE ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::SendPacket( CBasePack* pPacket )
{
__ENTER_FUNCTION

	if( IsDisconnect( ) )
		return TRUE ;

	if( m_pSocketOutputStream!=NULL )
	{
		IPacketFactory* pFactory = g_pPacketFactoryManager->GetFactory( pPacket->uID );
		if( !pFactory )
			return FALSE;

		BOOL ret = pFactory->Write(pPacket, *m_pSocketOutputStream);
		if( !ret )
			return FALSE;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Player::HeartBeat( UINT uTime, INT nFlag )
{
__ENTER_FUNCTION



	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID Player::ResetKick( )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}


