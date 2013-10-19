#include "Utility.h"
#include "Stub.h"
#include "Packet.h"
#include "PacketFactoryManager.h"

Stub::Stub( )
{
__ENTER_FUNCTION

	m_nStubID = INVALID_ID ;
	m_eStubType = STUB_TYPE_INVALID ;
	m_nPoolID = INVALID_ID ;

	m_pSocket = new Socket ;
	Assert( m_pSocket ) ;

	m_bIsEmpty		= TRUE ;
	m_IsDisconnect	= FALSE ;
	
	m_PacketIndex	 = 0 ;

	m_pSocketInputStream = NULL;
	m_pSocketOutputStream = NULL;

__LEAVE_FUNCTION
}

Stub::~Stub( )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pSocketInputStream ) ;
	SAFE_DELETE( m_pSocketOutputStream ) ;

	SAFE_DELETE( m_pSocket ) ;

__LEAVE_FUNCTION
}

VOID Stub::Init( BOOL bIsServer/*=FALSE*/ )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pSocketInputStream );
	SAFE_DELETE( m_pSocketOutputStream );

	if( bIsServer )
	{
		m_pSocketInputStream = new SocketInputStream( m_pSocket, DEFAULTSOCKETINPUTBUFFERSIZE, 64*1024*1024 ) ;
		Assert( m_pSocketInputStream ) ;

		m_pSocketOutputStream = new SocketOutputStream( m_pSocket, DEFAULTSOCKETOUTPUTBUFFERSIZE, 64*1024*1024 ) ;
		Assert( m_pSocketOutputStream ) ;
	}
	else
	{
		m_pSocketInputStream = new SocketInputStream( m_pSocket ) ;
		Assert( m_pSocketInputStream ) ;

		m_pSocketOutputStream = new SocketOutputStream( m_pSocket ) ;
		Assert( m_pSocketOutputStream ) ;
	}

	m_bIsServerStub = bIsServer ;

__LEAVE_FUNCTION
}

VOID Stub::CleanUp( )
{
__ENTER_FUNCTION

	m_pSocket->close() ;
	m_pSocketInputStream->CleanUp() ;
	m_pSocketOutputStream->CleanUp() ;
	m_PacketIndex = 0 ;
	SetDisconnect(FALSE) ;

__LEAVE_FUNCTION
}

VOID Stub::Disconnect( )
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

BOOL Stub::IsValid( )
{
__ENTER_FUNCTION

	if( m_pSocket==NULL ) return FALSE ;

	if( !m_pSocket->isValid() ) return FALSE ;


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Stub::ProcessInput( )
{
__ENTER_FUNCTION

	if( IsDisconnect() )
		return TRUE ;

	_MY_TRY 
	{
		uint ret = m_pSocketInputStream->Fill( ) ;
		if( (INT)ret <= SOCKET_ERROR )
		{
			g_Log.SaveLog( LOG_LV_ERROR,  "m_pSocketInputStream->Fill ret:%d %s", 
				(INT)ret, MySocketError() ) ;
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

BOOL Stub::ProcessCommand( BOOL Option )
{
__ENTER_FUNCTION

	BOOL ret ;

	CHAR header[PACKET_HEADER_SIZE];
	PacketID_t packetID;
	PacketLen_t packetLen;

	BasePacket* pPacket = NULL ;

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

			_MY_TRY
			{
				if( m_pSocketInputStream->Length()<PACKET_HEADER_SIZE+packetLen )
				{//消息没有接收全
					break;
				}

				BasePacket* pPacket = g_PacketFactoryManager.CreatePacket( packetID ) ;
				if( pPacket==NULL )
				{
					return FALSE ;
				}

				//设置消息序列号
				pPacket->uID = packetID;
				pPacket->uBodyLen = packetLen;

				IPacketFactory* pFactory = g_PacketFactoryManager.GetFactory( packetID );
				if( !pFactory )
				{
					g_PacketFactoryManager.RemovePacket( pPacket );
					return FALSE;
				}

				ret = pFactory->Read(pPacket, *m_pSocketInputStream);
				if( ret==FALSE )
				{//读取消息内容错误
					g_PacketFactoryManager.RemovePacket( pPacket ) ;
					return FALSE ;
				}

				BOOL bNeedRemove = TRUE ;
				BOOL bException = FALSE ;

				_MY_TRY
				{
					//修正m_KickTime信息，m_KickTime信息中的值为判断是否需要踢掉
					//客户端的依据
					ResetKick( ) ;

					BOOL ret = g_PacketFactoryManager.HandlePacket( pPacket, this );

					if( !ret )
					{//出现异常错误，断开此玩家连接
						g_PacketFactoryManager.RemovePacket( pPacket ) ;
						return FALSE ;
					}
				}
				_MY_CATCH
				{
					SaveCodeLog( ) ;
					bException = TRUE ;
				}

				if( pPacket && bNeedRemove ) 
					g_PacketFactoryManager.RemovePacket( pPacket ) ;

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

BOOL Stub::ProcessOutput( )
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
			g_Log.SaveLog( LOG_LV_ERROR, "[%d] m_pSocketOutputStream->Flush ret:%d %s", 
				g_TimeManager.Time2DWORD(), (INT)ret, MySocketError() ) ;
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

BOOL Stub::SendPacket( BasePacket* pPacket )
{
__ENTER_FUNCTION

	if( IsDisconnect( ) )
		return TRUE ;

	if( m_pSocketOutputStream!=NULL )
	{
		IPacketFactory* pFactory = g_PacketFactoryManager.GetFactory( pPacket->uID );
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

VOID Stub::ResetKick( )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}


