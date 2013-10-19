#ifndef __PLAYER_SYSTEM_H__
#define __PLAYER_SYSTEM_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "Define/SystemDefine.h"
#include "Define/PrestrainFile/BirthPlace.h"
#include "Define/PrestrainFile/PlayerProperty.h"
#include "Define/ProtocolDefine.h"

class Player;
class PlayerManager;

class PlayerSystem : public GSystem
{
public:
	PlayerSystem();
	virtual ~PlayerSystem();

	const CHAR*	SystemName( VOID )	{ return "PlayerSystem";	}
	const INT	SystemID( VOID )	{ return SYSTEM_ID_PLAYER_SYSTEM;	}

	// ��ʼ��
	BOOL		Initialize( VOID );

	// ���մ���
	BOOL		Finalize( VOID );

	// ��������
	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	///////////////////////////////////////////////////////////////////
	// ���ܺ���
	Player*		GetPlayer( PlayerID_t nPlayerID );

	///////////////////////////////////////////////////////////////////
	// ��Ϣ���
protected:
	BOOL OnStubCreareReq( BasePacket* pPacket, Stub* pStub );

	DECLARE_PACKET_HANDLE_BEGIN( PlayerSystem );
		PACKET_HANDLE( PID_CS_Create_REQ, OnStubCreareReq );
	DECLARE_PACKET_HANDLE_END();

	///////////////////////////////////////////////////////////////////
	// �¼����
protected:
	//BOOL OnStubConnected( IEvent* pEvent );
	BOOL OnStubDisconnected( IEvent* pEvent );

	DECLARE_EVENT_HANDLE_BEGIN( PlayerSystem )
		//EVENT_HANDLE( EVENT_TYPE_STUB, EVENT_ID_ON_CONNECTED, OnStubConnected );
		EVENT_HANDLE( EVENT_TYPE_STUB, EVENT_ID_ON_DISCONNECTED, OnStubDisconnected );
	DECLARE_EVENT_HANDLE_END()

public:
	static PlayerSystem*	m_pPlayerSystem;

	//��ʼ����  ������ ��ҳ�����
	static CBirthPlace** cBirthPlace;
	//��ʼ����  ������ �������
	static CPlayerProperty** cPlayerProperty;

private:
	PlayerManager*			m_pPlayerManager;

	// test
	IDGenerator< PlayerID_t > m_IDGen;
};

#endif // __PLAYER_SYSTEM_H__