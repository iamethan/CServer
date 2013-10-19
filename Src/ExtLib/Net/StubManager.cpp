#include "StubManager.h"

#define ACCEPT_ONESTEP 50

StubManager::StubManager( )
	: m_IDGen( 0, MAX_STUB_SIZE, INVALID_ID )
	, m_StubPool( )
{
__ENTER_FUNCTION

#if defined(__WINDOWS__)
	WORD wVersionRequested;
	WSADATA wsaData;
	INT err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData ); 
#endif

	FD_ZERO( &m_ReadFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_WriteFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_ExceptFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_ReadFDs[SELECT_USE] ) ;
	FD_ZERO( &m_WriteFDs[SELECT_USE] ) ;
	FD_ZERO( &m_ExceptFDs[SELECT_USE] ) ;

	m_Timeout[SELECT_BAK].tv_sec = 0;
	m_Timeout[SELECT_BAK].tv_usec = 0;

	m_MinFD = m_MaxFD = INVALID_SOCKET ;

	m_nFDSize = 0 ;

	m_pConnectedPtr = NULL;
	m_pDisconnectedPtr = NULL;

__LEAVE_FUNCTION
}

StubManager::~StubManager( )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pServerSocket ) ;

__LEAVE_FUNCTION
}

BOOL StubManager::Init( UINT nListenPort )
{
__ENTER_FUNCTION

	m_pServerSocket = new ServerSocket( nListenPort ) ;
	Assert( m_pServerSocket ) ;

	m_pServerSocket->setNonBlocking() ;

	m_SocketID = m_pServerSocket->getSOCKET() ;
	Assert( m_SocketID != INVALID_SOCKET ) ;

	FD_SET(m_SocketID , &m_ReadFDs[SELECT_BAK]);
	FD_SET(m_SocketID , &m_ExceptFDs[SELECT_BAK]);

	m_MinFD = m_MaxFD = m_SocketID;

	m_Timeout[SELECT_BAK].tv_sec = 0;
	m_Timeout[SELECT_BAK].tv_usec = 0;

	m_StubPool.Init( MAX_STUB_SIZE );

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::Select( )
{
__ENTER_FUNCTION

	m_Timeout[SELECT_USE].tv_sec  = m_Timeout[SELECT_BAK].tv_sec;
	m_Timeout[SELECT_USE].tv_usec = m_Timeout[SELECT_BAK].tv_usec;

	m_ReadFDs[SELECT_USE]   = m_ReadFDs[SELECT_BAK];
	m_WriteFDs[SELECT_USE]  = m_WriteFDs[SELECT_BAK];
	m_ExceptFDs[SELECT_USE] = m_ExceptFDs[SELECT_BAK];

	_MY_TRY 
	{
		INT iRet = SocketAPI::select_ex(	(INT)m_MaxFD+1 , 
											&m_ReadFDs[SELECT_USE] , 
											&m_WriteFDs[SELECT_USE] , 
											&m_ExceptFDs[SELECT_USE] , 
											&m_Timeout[SELECT_USE] ) ;
		Assert( iRet!=SOCKET_ERROR ) ;
	} 
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::ProcessInputs( )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	//新连接接入：
	if( FD_ISSET(m_SocketID,&m_ReadFDs[SELECT_USE]) )
	{
		for( INT i=0; i<ACCEPT_ONESTEP; i++ )
		{
			if( !AcceptNewConnection() )
				break;
		}
	}

	//数据读取
	StubsMap::iterator itEnd = m_mapStubs.end();
	for( StubsMap::iterator it = m_mapStubs.begin(); it != itEnd; )
	{
		Stub* pStub = it->second;
		Assert( pStub );

		SOCKET s = pStub->GetSocket()->getSOCKET() ;
		if( s == m_SocketID )
		{
			++it;
			continue ;
		}

		if( FD_ISSET( s, &m_ReadFDs[SELECT_USE] ) )
		{
			if( pStub->GetSocket()->isSockError() )
			{//连接出现错误
				++it;
				DelStub( pStub->InnerID() );
				continue;
			}
			else
			{//连接正常
				_MY_TRY
				{
					ret = pStub->ProcessInput( ) ;
					if( !ret )
					{
						++it;
						DelStub( pStub->InnerID() );
						continue;
					}
				}
				_MY_CATCH
				{
					SaveCodeLog( ) ;
					++it;
					DelStub( pStub->InnerID() );
					continue;
				}
			}
		}

		++it;
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::ProcessOutputs( )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	//数据发送
	StubsMap::iterator itEnd = m_mapStubs.end();
	for( StubsMap::iterator it = m_mapStubs.begin(); it != itEnd; )
	{
		Stub* pStub = it->second;
		Assert( pStub );

		SOCKET s = pStub->GetSocket()->getSOCKET() ;
		if( s == m_SocketID )
		{
			++it;
			continue ;
		}

		if( FD_ISSET( s, &m_WriteFDs[SELECT_USE] ) )
		{
			if( pStub->GetSocket()->isSockError() )
			{//连接出现错误
				++it;
				DelStub( pStub->InnerID() ) ;
				continue;
			}
			else
			{//连接正常
				_MY_TRY
				{
					ret = pStub->ProcessOutput( ) ;
					if( !ret )
					{
						++it;
						DelStub( pStub->InnerID() ) ;
						continue;
					}
				}
				_MY_CATCH
				{
					++it;
					SaveCodeLog( ) ;
					DelStub( pStub->InnerID() ) ;
					continue;
				}
			}
		}

		++it;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::ProcessExceptions( )
{
__ENTER_FUNCTION

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	StubsMap::iterator itEnd = m_mapStubs.end();
	for( StubsMap::iterator it = m_mapStubs.begin(); it != itEnd; )
	{
		//某个Stub断开网络连接

		Stub* pStub = it->second;
		Assert( pStub );

		SOCKET s = pStub->GetSocket()->getSOCKET() ;
		if( s == m_SocketID )
		{//侦听句柄出现问题
			Assert( FALSE ) ;
			++it;
			continue ;
		}

		if( FD_ISSET( s, &m_ExceptFDs[SELECT_USE] ) )
		{
			++it;
			DelStub( pStub->InnerID() ) ;
			continue;
		}
		
		++it;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::ProcessCommands( )
{
__ENTER_FUNCTION

	BOOL ret ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET) // no player exist
	{ 
		return TRUE ;
	}

	StubsMap::iterator itEnd = m_mapStubs.end();
	for( StubsMap::iterator it = m_mapStubs.begin(); it != itEnd; )
	{
		Stub* pStub = it->second;
		Assert( pStub ) ;

		SOCKET s = pStub->GetSocket()->getSOCKET() ;
		if( s == m_SocketID )
		{
			++it;
			continue ;
		}

		if( pStub->GetSocket()->isSockError() )
		{//连接出现错误
			++it;
			DelStub( pStub->InnerID() );
			continue;
		}
		else
		{//连接正常
			_MY_TRY
			{
				ret = pStub->ProcessCommand( FALSE ) ;
				if( !ret )
				{
					++it;
					DelStub( pStub->InnerID() );
					continue;
				}
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
				++it;
				DelStub( pStub->InnerID() );
				continue;
			}
		}

		++it;
	}


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::AcceptNewConnection( )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	Stub* pStub = m_StubPool.NewStub();
	if( !pStub )
		return FALSE ;

	pStub->CleanUp( ) ;

	INT fd = INVALID_SOCKET ;

	_MY_TRY
	{
		//接受客户端接入Socket句柄
		ret = m_pServerSocket->accept( pStub->GetSocket() ) ;
		if( !ret )
		{
			goto EXCEPTION ;
		}
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
		goto EXCEPTION ;
	}

	_MY_TRY
	{
		fd = (INT)pStub->GetSocket()->getSOCKET();
		if( fd == INVALID_SOCKET )
		{
			Assert(FALSE) ;
			goto EXCEPTION ;
		}

		ret = pStub->GetSocket()->setNonBlocking() ;
		if( !ret )
		{
			Assert(FALSE) ;
			goto EXCEPTION ;
		}

		if( pStub->GetSocket()->getSockError() )
		{
			Assert(FALSE) ;
			goto EXCEPTION ;
		}

		ret = pStub->GetSocket()->setLinger(0) ;
		if( !ret )
		{	
			Assert(FALSE) ;
			goto EXCEPTION ;
		}

		_MY_TRY
		{
			ret = AddStub( pStub ) ;
			if( !ret )
			{
				Assert(FALSE) ;
				goto EXCEPTION ;
			}
		}
		_MY_CATCH
		{
			SaveCodeLog( ) ;
			goto EXCEPTION ;
		}
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

	return TRUE ;


EXCEPTION:
	pStub->CleanUp() ;
	m_StubPool.DelStub( pStub );

	return FALSE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::AddStub( Stub* pStub )
{
__ENTER_FUNCTION

	if( m_nFDSize>=FD_SETSIZE )
	{//已经超出能够检测的网络句柄最大数；
		return FALSE ;
	}
	SOCKET fd = pStub->GetSocket()->getSOCKET() ;
	Assert( fd != INVALID_SOCKET ) ;

	if( FD_ISSET(fd,&m_ReadFDs[SELECT_BAK]) )
	{
		return FALSE ;
	}

	// 添加进管理器
	StubInnerID_t nInnerID = m_IDGen.GetUnusedID();

	if( !m_mapStubs.insert( StubsMap::value_type(nInnerID, pStub) ).second )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "StubManager::AddStub{sock<%d>, inner<%d>} faied!",
			pStub->GetSocket()->getHostIP(), nInnerID );
		return FALSE;
	}

	pStub->InnerID( nInnerID );
	m_IDGen.UseID( nInnerID );

	//
	m_MinFD = min(fd , m_MinFD);
	m_MaxFD = max(fd , m_MaxFD);

	FD_SET(fd , &m_ReadFDs[SELECT_BAK]);
	FD_SET(fd , &m_WriteFDs[SELECT_BAK]);
	FD_SET(fd , &m_ExceptFDs[SELECT_BAK]);

	m_nFDSize++ ;

	g_Log.SaveLog( LOG_LV_NORMAL, "AcceptNewConnection(SOCKET=%d, IP=%s)...OK", 
		pStub->GetSocket()->getSOCKET(), pStub->GetSocket()->m_Host ) ;

	OnConnected( pStub );

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL StubManager::DelStub( StubInnerID_t id )
{
__ENTER_FUNCTION

	Assert( id!=INVALID_ID ) ;

	Stub* pStub = GetStub( id );
	if( !pStub )
	{
		Assert( pStub );
		g_Log.SaveLog( LOG_LV_WARNING, "Disconnection<%d> error! can not find the stub!",
			id );
		return NULL;
	}

	SOCKET fd = pStub->GetSocket()->getSOCKET() ;

	Assert( m_MinFD!=INVALID_SOCKET ) ;
	Assert( m_MaxFD!=INVALID_SOCKET ) ;
	if( fd==INVALID_SOCKET ) 
	{
		Assert(FALSE) ;
	}

	g_Log.SaveLog( LOG_LV_NORMAL, "StubManager Delete Connection<SOCKET=%d, IP=%s>",
		pStub->GetSocket()->getSOCKET(), pStub->GetSocket()->m_Host );

	OnDisconnected( pStub );

	if( fd==m_MinFD ) 
	{
		SOCKET s = m_MaxFD ;
		StubsMap::iterator itEnd = m_mapStubs.end();
		for( StubsMap::iterator it = m_mapStubs.begin(); it != itEnd; ++it )
		{
			Stub* pStub = it->second;
			Assert( pStub ) ;
			if( pStub==NULL )
				continue ;


			SOCKET temp = pStub->GetSocket()->getSOCKET() ;
			if( temp == fd )
				continue ;
			if( temp==INVALID_SOCKET )
				continue ;

			if( temp < s )
			{
				s = temp ;
			}
		}

		if( m_MinFD == m_MaxFD )
		{
			m_MinFD = m_MaxFD = INVALID_SOCKET ;
		}
		else
		{
			if( s > m_SocketID )
			{
				m_MinFD = m_SocketID ;
			}
			else
			{
				m_MinFD = s ;
			}
		}
	} 
	else if( fd==m_MaxFD ) 
	{
		SOCKET s = m_MinFD ;
		StubsMap::iterator itEnd = m_mapStubs.end();
		for( StubsMap::iterator it = m_mapStubs.begin(); it != itEnd; ++it )
		{
			Stub* pStub = it->second;
			Assert( pStub ) ;
			if( pStub==NULL )
				continue ;

			SOCKET temp = pStub->GetSocket()->getSOCKET() ;
			if( temp == fd )
				continue ;
			if( temp==INVALID_SOCKET )
				continue ;

			if( temp > s )
			{
				s = temp ;
			}
		}

		if( m_MaxFD == m_MinFD )
		{
			m_MinFD = m_MaxFD = INVALID_SOCKET ;
		}
		else
		{
			if( s < m_SocketID )
			{
				m_MaxFD = m_SocketID ;
			}
			else
			{
				m_MaxFD = s ;
			}
		}
	}

	FD_CLR(fd , &m_ReadFDs[SELECT_BAK]);
	FD_CLR(fd , &m_ReadFDs[SELECT_USE]);
	FD_CLR(fd , &m_WriteFDs[SELECT_BAK]);
	FD_CLR(fd , &m_WriteFDs[SELECT_USE]);
	FD_CLR(fd , &m_ExceptFDs[SELECT_BAK]);
	FD_CLR(fd , &m_ExceptFDs[SELECT_USE]);

	m_nFDSize-- ;
	Assert( m_nFDSize>=0 ) ;

	// 从队列中删除
	StubsMap::iterator it = m_mapStubs.find( id );
	m_mapStubs.erase( it );

	m_IDGen.RecycleID( id );

	// 清除StubPool中的使用
	m_StubPool.DelStub( pStub );

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

Stub* StubManager::GetStub( StubInnerID_t nStubInnerID )
{
__ENTER_FUNCTION

	StubsMap::iterator it = m_mapStubs.find( nStubInnerID );
	if( it == m_mapStubs.end() )
	{
		return NULL;
	}

	return it->second;

__LEAVE_FUNCTION

	return NULL;
}

BOOL StubManager::Tick( INT iSkip, FLOAT fTimePass )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	_MY_TRY
	{
		ret = Select( ) ;
		Assert( ret ) ;

		ret = ProcessExceptions( ) ;
		Assert( ret ) ;

		ret = ProcessInputs( ) ;
		Assert( ret ) ;

		ret = ProcessOutputs( ) ;
		Assert( ret ) ;
	}
	_MY_CATCH
	{
	}

	_MY_TRY
	{
		ret = ProcessCommands( ) ;
		Assert( ret ) ;
	}
	_MY_CATCH
	{
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID StubManager::OnConnected( Stub* pStub )
{
__ENTER_FUNCTION

	if( m_pConnectedPtr )
	{
		m_pConnectedPtr( pStub );
	}

__LEAVE_FUNCTION
}

VOID StubManager::OnDisconnected( Stub* pStub )
{
__ENTER_FUNCTION

	if( m_pDisconnectedPtr )
	{
		m_pDisconnectedPtr( pStub );
	}

__LEAVE_FUNCTION
}

VOID StubManager::SetConnectedPtr( STUB_CALLBACK_PTR pFunc )
{
__ENTER_FUNCTION

	m_pConnectedPtr = pFunc;

__LEAVE_FUNCTION
}

VOID StubManager::SetDisconnectedPtr( STUB_CALLBACK_PTR pFunc )
{
__ENTER_FUNCTION

	m_pDisconnectedPtr = pFunc;

__LEAVE_FUNCTION
}