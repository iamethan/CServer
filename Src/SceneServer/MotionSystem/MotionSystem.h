#ifndef __MOTION_SYSTEM_H__
#define __MOTION_SYSTEM_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "Define/SystemDefine.h"
#include "Define/PrestrainFile/Protocol/PacketDefine_Move.h"

#define MAX_ALLOWABLE_POS_RANGE	10	// �������ͻ��������λ�������Χ

class DynamicObj;

class MotionSystem : public GSystem
{
public:
	MotionSystem();
	~MotionSystem();

	const CHAR*	SystemName( VOID )	{ return "MotionSystem";	}
	const INT	SystemID( VOID )	{ return SYSTEM_ID_MOTION_SYSTEM;	}

	// ��ʼ��
	BOOL		Initialize( VOID );

	// ���մ���
	BOOL		Finalize( VOID );

	// ��������
	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	/////////////////////////////////////////////////////////
	// ���ܺ���
public:
	// �Ƿ���ƶ���Ŀ���
	BOOL		CheckMotion( DynamicObj* pObj, WORLD_POS& tSrcPos, WORLD_POS& tTarPos );
	// �Ƿ��˲�Ƶ�Ŀ���
	BOOL		CheckMoveTo( DynamicObj* pObj, WORLD_POS& tSrcPos, WORLD_POS& tTarPos );
	// �Ƿ��ֹͣ
	BOOL		CheckStop( DynamicObj* pObj, WORLD_POS& tPos );

	/////////////////////////////////////////////////////////
	// ��Ϣ�ص�
protected:
	BOOL OnRecvMoveReq( BasePacket* pPacket, Stub* pStub );
	BOOL OnRecvMoveEndReq( BasePacket* pPacket, Stub* pStub );

	DECLARE_PACKET_HANDLE_BEGIN( MotionSystem );
		PACKET_HANDLE( PID_CS_PlayerMove_REQ, OnRecvMoveReq );
		PACKET_HANDLE( PID_CS_PlayerMoveEnd_REQ, OnRecvMoveEndReq );
	DECLARE_PACKET_HANDLE_END();

	/////////////////////////////////////////////////////////
	// �¼����
protected:
	DECLARE_EVENT_HANDLE_BEGIN( MotionSystem )
		//EVENT_HANDLE( EVENT_TYPE_STUB, EVENT_ID_ON_CONNECTED, OnStubConnected );
		//EVENT_HANDLE( EVENT_TYPE_STUB, EVENT_ID_ON_DISCONNECTED, OnStubDisconnected );
	DECLARE_EVENT_HANDLE_END()

public:
	static MotionSystem*	m_pMotionSystem;
	
};

#endif // __MOTION_SYSTEM_H__