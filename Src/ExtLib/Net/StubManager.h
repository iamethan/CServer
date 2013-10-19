#ifndef __STUB_MANAGER_H__
#define __STUB_MANAGER_H__

#include "Utility.h"
#include <map>
#include "Packet.h"
#include "Stub.h"
#include "StubPool.h"
#include "ServerSocket.h"
#include "PacketFactoryManager.h"

#define  MAX_STUB_SIZE	2000

typedef VOID	(*STUB_CALLBACK_PTR) ( Stub* pStub );

class StubManager
{
	typedef std::map<StubInnerID_t, Stub*>	StubsMap;

public:
	StubManager( ) ;
	~StubManager( ) ;

	//模块初始化接口
	BOOL				Init( UINT nListenPort ) ;
	//网络侦测
	BOOL				Select( ) ;
	//数据接受接口
	BOOL				ProcessInputs( ) ;
	//数据发送接口
	BOOL				ProcessOutputs( ) ;
	//异常连接处理
	BOOL				ProcessExceptions( ) ;
	//消息执行
	BOOL				ProcessCommands( ) ;
	//新连接接收处理
	BOOL				AcceptNewConnection( ) ;

	BOOL				Tick( INT iSkip, FLOAT fTimePass ) ;

public:
	BOOL				AddStub( Stub* pStub ) ;
	BOOL				DelStub( StubInnerID_t nStubInnerID ) ;
	Stub*				GetStub( StubInnerID_t nStubInnerID ) ;

	VOID				SetConnectedPtr( STUB_CALLBACK_PTR pFunc );
	VOID				SetDisconnectedPtr( STUB_CALLBACK_PTR pFunc );

	VOID				OnConnected( Stub* pStub );
	VOID				OnDisconnected( Stub* pStub );

private:
	//用于侦听的服务器Socket
	ServerSocket*		m_pServerSocket ;
	//用于侦听的服务器SOCKET句柄值（此数据即m_pServerSocket内拥有的SOCKET句柄值）
	SOCKET				m_SocketID ;

	//
	//网络相关数据
	enum{
		SELECT_BAK = 0,	//当前系统中拥有的完整句柄数据
		SELECT_USE = 1,	//用于select调用的句柄数据
		SELECT_MAX = 2, //结构使用数量
	};
	fd_set		m_ReadFDs[SELECT_MAX];
	fd_set		m_WriteFDs[SELECT_MAX];
	fd_set		m_ExceptFDs[SELECT_MAX];

	timeval		m_Timeout[SELECT_MAX];

	SOCKET		m_MinFD;
	SOCKET		m_MaxFD;

	INT			m_nFDSize ;

	// stubs
	StubsMap					m_mapStubs;
	IDGenerator<StubInnerID_t>	m_IDGen;

	StubPool					m_StubPool;

	STUB_CALLBACK_PTR			m_pConnectedPtr;
	STUB_CALLBACK_PTR			m_pDisconnectedPtr;
};

#endif // __STUB_MANAGER_H__