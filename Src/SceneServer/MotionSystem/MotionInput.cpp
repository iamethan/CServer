#include "StdAfx.h"
#include "MotionInput.h"
#include "Obj/Obj.h"
#include "PlayerSystem/Player.h"
#include "SceneSystem/Scene.h"
#include "Define/ProtocolDefine.h"

BOOL MotionInput::Motion( DynamicObj* pObj, WORLD_POS& tTarPos )
{
	if( !pObj )
	{
		return FALSE;
	}

	pObj->TarPos( tTarPos );

	// 通知周围玩家
	SC_PlayerMove_NTF msg;
	msg.uID = PID_SC_PlayerMove_NTF;
	msg.stBody.fTargetX = tTarPos.m_fX;
	msg.stBody.fTargetY = 0;
	msg.stBody.fTargetZ = tTarPos.m_fZ;
	msg.stBody.uObjectID = pObj->ObjID( );

	Scene* pScene = pObj->GetScene( );
	if( !pScene )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "MotionInput::Motion<%d, %d> Error!,has not entered scene!",
			pObj->ObjID(), pObj->ObjType() );
		return FALSE;
	}

	pScene->BroadCast( &msg, (Obj*)pObj );

	return TRUE;
}

BOOL MotionInput::MoveTo( DynamicObj* pObj, WORLD_POS& tTarPos )
{
	return TRUE;
}

BOOL MotionInput::Stop( DynamicObj* pObj )
{
	if( !pObj )
	{
		return FALSE;
	}

	pObj->MoveState( MOVE_STATE_STATIC );

	SC_PlayerMove_NTF msg;
	msg.uID = PID_SC_PlayerMove_NTF;
	msg.stBody.fTargetX = pObj->Pos().m_fX;
	msg.stBody.fTargetY = 0;
	msg.stBody.fTargetZ = pObj->Pos().m_fZ;
	msg.stBody.uObjectID = pObj->ObjID();

	Scene* pScene = pObj->GetScene( );
	if( !pScene )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "MotionInput::Stop<%d, %d> Error!,has not entered scene!",
			pObj->ObjID(), pObj->ObjType() );
		return FALSE;
	}

	pScene->BroadCast( &msg, (Obj*)pObj );

	return TRUE;
}

BOOL MotionInput::GoStart( DynamicObj* pObj )
{
	return TRUE;
}