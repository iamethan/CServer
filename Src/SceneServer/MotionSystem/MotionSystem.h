#ifndef __MOTION_SYSTEM_H__
#define __MOTION_SYSTEM_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "Define/SystemDefine.h"
#include "Define/PrestrainFile/Protocol/PacketDefine_Move.h"

#define MAX_ALLOWABLE_POS_RANGE	10	// 服务端与客户端允许的位置最大误差范围

class DynamicObj;

class MotionSystem : public GSystem
{
public:
	MotionSystem();
	~MotionSystem();

	const CHAR*	SystemName( VOID )	{ return "MotionSystem";	}
	const INT	SystemID( VOID )	{ return SYSTEM_ID_MOTION_SYSTEM;	}

	// 初始化
	BOOL		Initialize( VOID );

	// 回收处理
	BOOL		Finalize( VOID );

	// 心跳函数
	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	/////////////////////////////////////////////////////////
	// 功能函数
public:
	// 是否可移动到目标点
	BOOL		CheckMotion( DynamicObj* pObj, WORLD_POS& tSrcPos, WORLD_POS& tTarPos );
	// 是否可瞬移到目标点
	BOOL		CheckMoveTo( DynamicObj* pObj, WORLD_POS& tSrcPos, WORLD_POS& tTarPos );
	// 是否可停止
	BOOL		CheckStop( DynamicObj* pObj, WORLD_POS& tPos );

	/////////////////////////////////////////////////////////
	// 消息回调
protected:
	BOOL OnRecvMoveReq( BasePacket* pPacket, Stub* pStub );
	BOOL OnRecvMoveEndReq( BasePacket* pPacket, Stub* pStub );

	DECLARE_PACKET_HANDLE_BEGIN( MotionSystem );
		PACKET_HANDLE( PID_CS_PlayerMove_REQ, OnRecvMoveReq );
		PACKET_HANDLE( PID_CS_PlayerMoveEnd_REQ, OnRecvMoveEndReq );
	DECLARE_PACKET_HANDLE_END();

	/////////////////////////////////////////////////////////
	// 事件相关
protected:
	DECLARE_EVENT_HANDLE_BEGIN( MotionSystem )
		//EVENT_HANDLE( EVENT_TYPE_STUB, EVENT_ID_ON_CONNECTED, OnStubConnected );
		//EVENT_HANDLE( EVENT_TYPE_STUB, EVENT_ID_ON_DISCONNECTED, OnStubDisconnected );
	DECLARE_EVENT_HANDLE_END()

public:
	static MotionSystem*	m_pMotionSystem;
	
};

#endif // __MOTION_SYSTEM_H__