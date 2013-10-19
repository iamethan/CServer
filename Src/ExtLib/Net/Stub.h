#ifndef __STUB_H__
#define __STUB_H__

#include "Utility.h"
#include "Socket.h"
#include "Packet.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PacketFactoryManager.h"

#define MAX_CACHE_SIZE 1024

//如果在一定时间内没有收到任何消息，则断开此客户端的网络连接
#define MAX_SERVER_STUB_KICK_TIME 6000000
#define MAX_CLIENT_STUB_KICK_TIME 6000000

class StubPool;
class StubManager;

enum STUB_TYPE
{
	STUB_TYPE_INVALID = -1,	// 未分配stub用处
	STUB_TYPE_PLAYER = 0,	// 用于侦听客户端玩家连接
	STUB_TYPE_SERVER,		// 用于服务端连接
};

class Stub
{
	friend class StubPool;
	friend class ObjPool<Stub>;
	friend class StubManager;
	
public :
	BOOL	ProcessInput( ) ;
	BOOL	ProcessOutput( ) ;
	BOOL	ProcessCommand( BOOL Option = TRUE ) ;

	BOOL	SendPacket( BasePacket* pPacket ) ;

public :
	//通用接口
	VOID				StubID( StubID_t stubID )	{ m_nStubID = stubID;		}
	StubID_t			StubID( )					{ return m_nStubID;			}

	VOID				StubType(STUB_TYPE eType )	{ m_eStubType = eType;		}
	STUB_TYPE			StubType( )					{ return m_eStubType;		}

	//读取当前玩家的Socket类
	//网络连接接口
	Socket*		GetSocket(){ return m_pSocket ; }

	//断开与当前玩家的网络连接
	virtual VOID			Disconnect( ) ;

	//判断当前玩家的网络连接是否有效
	virtual	BOOL			IsValid( ) ; 

	//清除当前网络连接数据和缓存数据
	virtual	VOID			CleanUp( ) ;

	//判断当前玩家数据块是否是空块；
	//如果是空块，则可以被PlayerPool分配出去用于接收新连接
	BOOL					IsEmpty( ) { return m_bIsEmpty ; }
	VOID					SetEmpty( BOOL opt = TRUE ) { m_bIsEmpty = opt ; }

	BOOL					IsDisconnect( ) { return m_IsDisconnect ; }
	VOID					SetDisconnect( BOOL opt = TRUE ) { m_IsDisconnect = opt ; }

	virtual VOID			ResetKick( ) ;

	BOOL					IsServerStub( ) { return m_bIsServerStub;	}

	StubInnerID_t			InnerID( )		{ return m_nInnerID;	}

protected:
	Stub( );
	~Stub( );

	// 初始化, 只能由StubPool进行初始化
	VOID Init( BOOL bIsServer=FALSE );

	// 只能由StubManager进行管理
	VOID			InnerID( StubInnerID_t id )	{ m_nInnerID = id;		}

protected :
	// 具有实际意义
	StubID_t				m_nStubID;

	STUB_TYPE				m_eStubType;

	// 内部使用ID, 由StubManager统一管理
	StubInnerID_t			m_nInnerID;

	//网络连接句柄
	Socket*					m_pSocket ;

	//输入输出数据缓存
	SocketInputStream*		m_pSocketInputStream ;
	SocketOutputStream*		m_pSocketOutputStream ;

	BYTE					m_PacketIndex ;

	// 是否为服务端节点，服务端节点缓冲区比客户端大很多
	BOOL					m_bIsServerStub;

	BOOL					m_IsDisconnect ;

private:
	// POOL相关
	UINT	GetPoolID( )			{ return m_nPoolID;	}
	VOID	SetPoolID( UINT id )	{ m_nPoolID = id;	}
	BOOL	m_bIsEmpty;	// 是否空闲，空闲中，可以被Pool分配出去继续使用
	UINT	m_nPoolID;
};

#endif // __STUB_H__
