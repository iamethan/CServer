#include "Scene.h"
#include "PlayerSystem/Player.h"
#include "Define/ProtocolDefine.h"

Scene::Scene( )
{
}

Scene::~Scene( )
{
}

BOOL Scene::Initialize( )
{
	for( int i = 0; i < OBJ_TYPE_COUNT; ++i )
	{
		m_mapObjs[i].clear();
	}

	return TRUE;
}

BOOL Scene::Finalize( )
{
	// 通知场景内所有玩家离开
	ObjsMap::iterator itEnd = m_mapObjs[OBJ_TYPE_PLAYER].end();
	for( ObjsMap::iterator it = m_mapObjs[OBJ_TYPE_PLAYER].begin(); it != itEnd; ++it )
	{
		Player* pPlayer = (Player*)it->second;

		// 离开场景事件
		SendLeaveSceneEvent( EVENT_TYPE_PLAYER, pPlayer->PlayerID(), SceneID() );
	}

	for( int i = 0; i < OBJ_TYPE_COUNT; ++i )
	{
		m_mapObjs[i].clear();
	}

	return TRUE;
}

BOOL Scene::CheckEnterScene( Player* pPlayer )
{
	return TRUE;
}

BOOL Scene::CheckLeaveScene( Player* pPlayer )
{
	return TRUE;
}

BOOL Scene::EnterScene( Player* pPlayer )
{
	if( !AddObj((Obj*)pPlayer) )
	{
		return FALSE;
	}

	g_Log.SaveLog( LOG_LV_NORMAL, "Player<%d, %s> enter scene successed!",
		pPlayer->PlayerID(), pPlayer->PlayerName() );

	// 进入场景事件
	SendEnterSceneEvent( EVENT_TYPE_PLAYER, pPlayer->PlayerID(), SceneID() );

	// 给自己发送创建消息
	SC_Create_REV resultRevSelf;
	resultRevSelf.uID = PID_SC_Create_REV;
	resultRevSelf.stBody.uHP = pPlayer->HP();
	resultRevSelf.stBody.uMP = pPlayer->MP();
	resultRevSelf.stBody.fPosX = pPlayer->Pos().m_fX;
	resultRevSelf.stBody.fPosY = 0.0f;
	resultRevSelf.stBody.fPosZ = pPlayer->Pos().m_fZ;
	resultRevSelf.stBody.uObjectID = (unsigned int)pPlayer->PlayerID();
	resultRevSelf.stBody.strPlayerName = pPlayer->PlayerName();
	resultRevSelf.stBody.uTeamID = 1;
	resultRevSelf.stBody.uProfession = 1;

	SendPacket( &resultRevSelf, pPlayer );

	// 将自身进入消息广播给周围其他玩家
	SC_Create_NTF resultNtfOther;
	resultNtfOther.uID = PID_SC_Create_NTF;
	resultNtfOther.stBody.uHP = pPlayer->HP();
	resultNtfOther.stBody.uMP = pPlayer->MP();
	resultNtfOther.stBody.fPosX = pPlayer->Pos().m_fX;
	resultNtfOther.stBody.fPosY = 0.0f;
	resultNtfOther.stBody.fPosZ = pPlayer->Pos().m_fZ;
	resultNtfOther.stBody.uObjectID = (unsigned int)pPlayer->PlayerID();
	resultNtfOther.stBody.strPlayerName = pPlayer->PlayerName();
	resultNtfOther.stBody.uTeamID = 1;
	resultNtfOther.stBody.uProfession = 1;

	BroadCast( &resultNtfOther, pPlayer );

	// 创建周围玩家信息
	ObjsMap::iterator itEnd = m_mapObjs[OBJ_TYPE_PLAYER].end();
	for( ObjsMap::iterator it = m_mapObjs[OBJ_TYPE_PLAYER].begin(); it !=itEnd; ++it )
	{
		Player* pOther = (Player*)it->second;
		if( !pOther || pOther==pPlayer )
		{
			continue;
		}

		resultNtfOther.stBody.fPosX = pOther->Pos().m_fX;
		resultNtfOther.stBody.fPosY = 0.0f;
		resultNtfOther.stBody.fPosZ = pOther->Pos().m_fZ;
		resultNtfOther.stBody.uObjectID = (unsigned int)pOther->PlayerID();
		resultNtfOther.stBody.strPlayerName = pOther->PlayerName();

		SendPacket( &resultNtfOther, pPlayer );
	}

	return TRUE;
}

BOOL Scene::LeaveScene( Player* pPlayer )
{
	if( !pPlayer )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::LeaveScene failed, the player is null!" );
		return FALSE;
	}

	PlayerID_t nPlayerID = pPlayer->PlayerID();
	CHAR sName[64];
	strcpy( sName, pPlayer->PlayerName() );

	// 广播离开消息
	SC_RemovePlayer_NTF msg;
	msg.uID = PID_SC_PlayerMove_NTF;
	msg.stBody.uObjectID = pPlayer->PlayerID();
	pPlayer->BroadCast( &msg );

	if( !DelObj((Obj*)pPlayer) )
	{
		return FALSE;
	}

	// 离开事件
	SendLeaveSceneEvent( EVENT_TYPE_PLAYER, nPlayerID, SceneID() );

	g_Log.SaveLog( LOG_LV_NORMAL, "Player<%d, %s> leave scene successed!",
		nPlayerID, sName );

	return TRUE;
}

BOOL Scene::AddObj( Obj* pObj )
{
	if( !pObj )
	{
		return FALSE;
	}

	OBJ_TYPE eType = pObj->ObjType( );
	if( eType < 0 || eType >= OBJ_TYPE_COUNT )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::AddObj<%d> failed, the type<%d> is invalid!",
			pObj->ObjID(), eType );
		return FALSE;
	}

	ObjID_t nObjID = pObj->ObjID( );
	if( nObjID == INVALID_ID )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::AddObj<%d> failed, the id is invalid",
			nObjID );
		return FALSE;
	}

	ObjsMap::iterator it = m_mapObjs[eType].find( nObjID );
	if( it != m_mapObjs[eType].end() )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "Scene::AddObj<%d, %d> warning, the obj has been added!",
			nObjID, eType );
		return TRUE;
	}

	if( !m_mapObjs[eType].insert(ObjsMap::value_type(nObjID, pObj) ).second )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::AddObj<%d, %d> error, when insert to map",
			nObjID, eType );
		return FALSE;
	}

	pObj->SetScene( this );

	return TRUE;
}

BOOL Scene::DelObj( Obj* pObj )
{
	if( !pObj )
	{
		return FALSE;
	}

	OBJ_TYPE eType = pObj->ObjType( );
	if( eType < 0 || eType >= OBJ_TYPE_COUNT )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::DelObj<%d> failed, the type<%d> is invalid!",
			pObj->ObjID(), eType );
		return FALSE;
	}

	ObjID_t nObjID = pObj->ObjID( );
	if( nObjID == INVALID_ID )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::DelObj<%d> failed, the id is invalid",
			nObjID );
		return FALSE;
	}

	ObjsMap::iterator it = m_mapObjs[eType].find( nObjID );
	if( it == m_mapObjs[eType].end() )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "Scene::DelObj<%d, %d> warning, the obj has not been added!",
			nObjID, eType );
		return TRUE;
	}

	if( it->second )
	{
		it->second->SetScene( NULL );
	}

	m_mapObjs[eType].erase( it );

	return TRUE;
}

///////////////////////////////////////////////////////////////
// 消息相关
BOOL Scene::SendPacket( BasePacket* pPacket, Player* pPlayer )
{
	if( !pPacket )
	{
		return FALSE;
	}

	if( !pPlayer )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::SendPacket<%d> failed, the player is null!",
			pPacket->uID );
		return FALSE;
	}

	return pPlayer->SendPacket( pPacket );
}

BOOL Scene::BroadCast( BasePacket* pPacket, Obj* pObj, BOOL bSendSelf/* = FALSE*/ )
{
	if( !pPacket || !pObj )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::BroadCast error! the packet or obj is null" );
		return FALSE;
	}

	BOOL bIsPlayer = ( pObj->ObjType() == OBJ_TYPE_PLAYER );

	Player* pStepPlayer = NULL;
	ObjsMap::iterator itEnd = m_mapObjs[OBJ_TYPE_PLAYER].end();
	for( ObjsMap::iterator it = m_mapObjs[OBJ_TYPE_PLAYER].begin(); it != itEnd; ++it )
	{
		pStepPlayer = (Player*)it->second;
		if( !pStepPlayer )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "Scene::BroadCast error! the map have null player" );
			continue;
		}

		if( bIsPlayer && pObj == pStepPlayer && !bSendSelf )
		{
			continue;
		}

		if( !pStepPlayer->SendPacket(pPacket) )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "Scene::BroadCast error! when send packet<%d> to player<%d>",
				pPacket->uID, pStepPlayer->PlayerID() );
		}
	}

	return TRUE;
}

BOOL Scene::BroadCast( BasePacket* pPacket )
{
	if( !pPacket )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Scene::BroadCast error! the packet is null" );
		return FALSE;
	}

	Player* pStepPlayer = NULL;
	ObjsMap::iterator itEnd = m_mapObjs[OBJ_TYPE_PLAYER].end();
	for( ObjsMap::iterator it = m_mapObjs[OBJ_TYPE_PLAYER].begin(); it != itEnd; ++it )
	{
		pStepPlayer = (Player*)it->second;
		if( !pStepPlayer )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "Scene broadcast to the whole scene error! the map have null player" );
			continue;
		}

		if( !pStepPlayer->SendPacket(pPacket) )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "Scene broadcast to the whole scene error! when send packet<%d> to player<%d>",
				pPacket->uID, pStepPlayer->PlayerID() );
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////
// 场景事件
VOID Scene::OnSceneInit( )
{

}

VOID Scene::OnEnterScene( Obj* pObj )
{

}

VOID Scene::OnLeaveScene( Obj* pObj, LEAVE_SCENE_REASON eReason/* = LEAVE_SCENE_REASON_NORMAL*/ )
{

}