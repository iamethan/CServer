#ifndef __STUB_H__
#define __STUB_H__

#include "Utility.h"
#include "Socket.h"
#include "Packet.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PacketFactoryManager.h"

#define MAX_CACHE_SIZE 1024

//�����һ��ʱ����û���յ��κ���Ϣ����Ͽ��˿ͻ��˵���������
#define MAX_SERVER_STUB_KICK_TIME 6000000
#define MAX_CLIENT_STUB_KICK_TIME 6000000

class StubPool;
class StubManager;

enum STUB_TYPE
{
	STUB_TYPE_INVALID = -1,	// δ����stub�ô�
	STUB_TYPE_PLAYER = 0,	// ���������ͻ����������
	STUB_TYPE_SERVER,		// ���ڷ��������
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
	//ͨ�ýӿ�
	VOID				StubID( StubID_t stubID )	{ m_nStubID = stubID;		}
	StubID_t			StubID( )					{ return m_nStubID;			}

	VOID				StubType(STUB_TYPE eType )	{ m_eStubType = eType;		}
	STUB_TYPE			StubType( )					{ return m_eStubType;		}

	//��ȡ��ǰ��ҵ�Socket��
	//�������ӽӿ�
	Socket*		GetSocket(){ return m_pSocket ; }

	//�Ͽ��뵱ǰ��ҵ���������
	virtual VOID			Disconnect( ) ;

	//�жϵ�ǰ��ҵ����������Ƿ���Ч
	virtual	BOOL			IsValid( ) ; 

	//�����ǰ�����������ݺͻ�������
	virtual	VOID			CleanUp( ) ;

	//�жϵ�ǰ������ݿ��Ƿ��ǿտ飻
	//����ǿտ飬����Ա�PlayerPool�����ȥ���ڽ���������
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

	// ��ʼ��, ֻ����StubPool���г�ʼ��
	VOID Init( BOOL bIsServer=FALSE );

	// ֻ����StubManager���й���
	VOID			InnerID( StubInnerID_t id )	{ m_nInnerID = id;		}

protected :
	// ����ʵ������
	StubID_t				m_nStubID;

	STUB_TYPE				m_eStubType;

	// �ڲ�ʹ��ID, ��StubManagerͳһ����
	StubInnerID_t			m_nInnerID;

	//�������Ӿ��
	Socket*					m_pSocket ;

	//����������ݻ���
	SocketInputStream*		m_pSocketInputStream ;
	SocketOutputStream*		m_pSocketOutputStream ;

	BYTE					m_PacketIndex ;

	// �Ƿ�Ϊ����˽ڵ㣬����˽ڵ㻺�����ȿͻ��˴�ܶ�
	BOOL					m_bIsServerStub;

	BOOL					m_IsDisconnect ;

private:
	// POOL���
	UINT	GetPoolID( )			{ return m_nPoolID;	}
	VOID	SetPoolID( UINT id )	{ m_nPoolID = id;	}
	BOOL	m_bIsEmpty;	// �Ƿ���У������У����Ա�Pool�����ȥ����ʹ��
	UINT	m_nPoolID;
};

#endif // __STUB_H__
