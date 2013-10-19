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

	//ģ���ʼ���ӿ�
	BOOL				Init( UINT nListenPort ) ;
	//�������
	BOOL				Select( ) ;
	//���ݽ��ܽӿ�
	BOOL				ProcessInputs( ) ;
	//���ݷ��ͽӿ�
	BOOL				ProcessOutputs( ) ;
	//�쳣���Ӵ���
	BOOL				ProcessExceptions( ) ;
	//��Ϣִ��
	BOOL				ProcessCommands( ) ;
	//�����ӽ��մ���
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
	//���������ķ�����Socket
	ServerSocket*		m_pServerSocket ;
	//���������ķ�����SOCKET���ֵ�������ݼ�m_pServerSocket��ӵ�е�SOCKET���ֵ��
	SOCKET				m_SocketID ;

	//
	//�����������
	enum{
		SELECT_BAK = 0,	//��ǰϵͳ��ӵ�е������������
		SELECT_USE = 1,	//����select���õľ������
		SELECT_MAX = 2, //�ṹʹ������
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