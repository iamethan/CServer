#include "StdAfx.h"
#include "MotionSystem.h"
//
#include "PlayerSystem/PlayerSystem.h"
#include "PlayerSystem/Player.h"
#include "MotionInput.h"

MotionSystem* MotionSystem::m_pMotionSystem = NULL;

MotionSystem::MotionSystem()
{
}

MotionSystem::~MotionSystem()
{
}

BOOL MotionSystem::Initialize( VOID )
{


	return TRUE;
}

BOOL MotionSystem::Finalize( VOID )
{
	return TRUE;
}

VOID MotionSystem::HeartBeat( INT iSkip, FLOAT fTimePass)
{
}

BOOL MotionSystem::CheckMotion( DynamicObj* pObj, WORLD_POS& tSrcPos, WORLD_POS& tTarPos )
{
	OBJ_TYPE eObjType = pObj->ObjType();
	if( OBJ_TYPE_PLAYER == eObjType )
	{
		if( MyLengthSq(&pObj->Pos(), &tSrcPos) > MAX_ALLOWABLE_POS_RANGE * MAX_ALLOWABLE_POS_RANGE )
		{
			MotionInput::GoStart( pObj );
			return FALSE;
		}
	}
	
	// 设置起始点
	pObj->Pos( tSrcPos );

	// 开始移动
	BOOL bRet = MotionInput::Motion( pObj, tTarPos );

	return bRet;
}

BOOL MotionSystem::CheckMoveTo( DynamicObj* pObj, WORLD_POS& tSrcPos, WORLD_POS& tTarPos )
{
	OBJ_TYPE eObjType = pObj->ObjType();
	if( OBJ_TYPE_PLAYER == eObjType )
	{
		if( MyLengthSq(&pObj->Pos(), &tSrcPos) > MAX_ALLOWABLE_POS_RANGE * MAX_ALLOWABLE_POS_RANGE )
		{
			MotionInput::GoStart( pObj );
			return FALSE;
		}
	}

	// 直接传送到目标点
	BOOL bRet = MotionInput::MoveTo( pObj, tTarPos );

	return bRet;
}

BOOL MotionSystem::CheckStop( DynamicObj* pObj, WORLD_POS& tPos )
{
	OBJ_TYPE eObjType = pObj->ObjType();
	if( OBJ_TYPE_PLAYER == eObjType )
	{
		if( MyLengthSq(&pObj->Pos(), &tPos) > MAX_ALLOWABLE_POS_RANGE * MAX_ALLOWABLE_POS_RANGE )
		{
			MotionInput::GoStart( pObj );
			return FALSE;
		}
	}

	// 设置起始点
	pObj->Pos( tPos );

	BOOL bRet = MotionInput::Stop( pObj );

	return bRet;
}

BOOL MotionSystem::OnRecvMoveReq( BasePacket* pPacket, Stub* pStub )
{
	//CTransformPack_REQ* pTransformPacket = (CTransformPack_REQ*)pPacket;
	CS_PlayerMove_REQ* pMoveReq = (CS_PlayerMove_REQ*)pPacket;
	Player* pPlayer = PlayerSystem::m_pPlayerSystem->GetPlayer( pStub->StubID() );
	Assert( pPlayer );

	WORLD_POS tTarPos( pMoveReq->stBody.fTargetX, pMoveReq->stBody.fTargetZ );

	if( !m_pMotionSystem->CheckMotion( (DynamicObj*)pPlayer, pPlayer->Pos(), tTarPos ) )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "MotionSystem::OnRecvMoveReq Warning! player<%d, %s> send unsafe pos<%0.2f, %0.2f> svr<%0.2f, %0.2f>",
			pPlayer->PlayerID(), pPlayer->PlayerName(), pPlayer->Pos().m_fX, pPlayer->Pos().m_fZ, pPlayer->Pos().m_fX, pPlayer->Pos().m_fZ );
	}

	return TRUE;
}

BOOL MotionSystem::OnRecvMoveEndReq( BasePacket* pPacket, Stub* pStub )
{
	//CTransformEndPack_REQ* pEndPacket = (CTransformEndPack_REQ*)pPacket;
	CS_PlayerMoveEnd_REQ* pEndPacket = (CS_PlayerMoveEnd_REQ*)pPacket;
	Player* pPlayer = PlayerSystem::m_pPlayerSystem->GetPlayer( pStub->StubID() );
	Assert( pPlayer );

	WORLD_POS tPos( pEndPacket->stBody.fCurrentX, pEndPacket->stBody.fCurrentZ );

	if( !m_pMotionSystem->CheckStop( (DynamicObj*)pPlayer, tPos ) )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "MotionSystem::OnRecvMoveEndReq Warning! player<%d, %s> send unsafe pos<%0.2f, %0.2f> svr<%0.2f, %0.2f>",
			pPlayer->PlayerID(), pPlayer->PlayerName(), pPlayer->Pos().m_fX, pPlayer->Pos().m_fZ, tPos.m_fX, tPos.m_fZ );
	}

	return TRUE;
}