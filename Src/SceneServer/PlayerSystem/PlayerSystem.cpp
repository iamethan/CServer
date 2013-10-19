#include "StdAfx.h"
#include "PlayerSystem.h"
#include "Player.h"
#include "PlayerManager.h"
#include "SceneSystem/SceneSystem.h"
#include "SceneSystem/Scene.h"
#include "Define/ProtocolDefine.h"


PlayerSystem* PlayerSystem::m_pPlayerSystem = NULL;

PlayerSystem::PlayerSystem()
	: GSystem()
	, m_IDGen( 1, DEFAULT_MAX_PLAYER_POOL_SIZE, INVALID_ID )
{
	m_pPlayerSystem = this;

	m_pPlayerManager = new PlayerManager;
}

PlayerSystem::~PlayerSystem()
{
	SAFE_DELETE( m_pPlayerManager );
}

BOOL PlayerSystem::Initialize( VOID )
{
	if( !m_pPlayerManager->Initialize() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PlayerSystem::Initialize Failed, the player manager init failed!" );
		return FALSE;
	}

	return TRUE;
}

BOOL PlayerSystem::Finalize( VOID )
{
	if( !m_pPlayerManager->Finalize() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PlayerSystem::Finalize Failed, the player manager fina failed!" );
		return FALSE;
	}

	return TRUE;
}

VOID PlayerSystem::HeartBeat( INT iSkip, FLOAT fTimePass)
{
}

Player* PlayerSystem::GetPlayer( PlayerID_t nPlayerID )
{
	return m_pPlayerManager->GetPlayer( nPlayerID );
}

BOOL PlayerSystem::OnStubCreareReq( BasePacket* pPacket, Stub* pStub )
{
	/*CS_PlayerMove_REQ* pMoveReq = (CS_PlayerMove_REQ*)pPacket;
	Player* pPlayer = PlayerSystem::m_pPlayerSystem->GetPlayer( pStub->StubID() );
	Assert( pPlayer );

	WORLD_POS tTarPos( pMoveReq->stBody.fTargetX, pMoveReq->stBody.fTargetZ );

	if( !m_pMotionSystem->CheckMotion( (DynamicObj*)pPlayer, pPlayer->Pos(), tTarPos ) )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "MotionSystem::OnRecvMoveReq Warning! player<%d, %s> send unsafe pos<%0.2f, %0.2f> svr<%0.2f, %0.2f>",
			pPlayer->PlayerID(), pPlayer->PlayerName(), pPlayer->Pos().m_fX, pPlayer->Pos().m_fZ, pPlayer->Pos().m_fX, pPlayer->Pos().m_fZ );
	}

	return TRUE;*/

	CS_Create_REQ* pCreateReq = (CS_Create_REQ*)pPacket;
	
	PlayerID_t nPlayerID = m_IDGen.GetUnusedID( );
	CHAR name[64];
	sprintf( name, "test_%d", nPlayerID );

	Player* pPlayer = m_pPlayerManager->CreatePlayer( nPlayerID );
	if( !pPlayer )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PlayerSystem::OnConnected Error! can not create new player<%d>",
			nPlayerID );
		pStub->Disconnect();
		return TRUE;
	}

	pPlayer->PlayerName( name );
	pPlayer->Level( 1 );
	pPlayer->Sex( 1 );
	pPlayer->HP( 1000 );
	pPlayer->MP( 1000 );
	pPlayer->Speed( 1.5f );
	pPlayer->Pos( 5.0f, 5.0f );
	pPlayer->Dir( 0.0f );

	// 关联Stub
	pPlayer->AttachStub( pStub );

	// 直接进入Scene
	if( !SceneSystem::m_pSceneSystem->GetScene()->EnterScene( pPlayer ) )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "player<%d> enter scene error!", pPlayer->PlayerID() );
	}
	return TRUE;
}
// 
// BOOL PlayerSystem::OnStubConnected( IEvent* pEvent )
// {
// 	ConnectedEvent* pConnectedEvent = (ConnectedEvent*)pEvent;
// 	Stub* pStub = pConnectedEvent->GetStub();
// 
// 	// 连接后直接创建玩家
// 	PlayerID_t nPlayerID = m_IDGen.GetUnusedID( );
// 	CHAR name[64];
// 	sprintf( name, "test_%d", nPlayerID );
// 
// 	Player* pPlayer = m_pPlayerManager->CreatePlayer( nPlayerID );
// 	if( !pPlayer )
// 	{
// 		g_Log.SaveLog( LOG_LV_ERROR, "PlayerSystem::OnConnected Error! can not create new player<%d>",
// 			nPlayerID );
// 		pStub->Disconnect();
// 		return TRUE;
// 	}
// 
// 	pPlayer->PlayerName( name );
// 	pPlayer->Level( 1 );
// 	pPlayer->Sex( 1 );
// 	pPlayer->HP( 1000 );
// 	pPlayer->MP( 1000 );
// 	pPlayer->Speed( 1.5f );
// 	pPlayer->Pos( 5.0f, 5.0f );
// 	pPlayer->Dir( 0.0f );
// 
// 	// 关联Stub
// 	pPlayer->AttachStub( pStub );
// 
// 	// 直接进入Scene
// 	if( !SceneSystem::m_pSceneSystem->GetScene()->EnterScene( pPlayer ) )
// 	{
// 		g_Log.SaveLog( LOG_LV_ERROR, "player<%d> enter scene error!", pPlayer->PlayerID() );
// 	}
// 
// 
// 	return TRUE;
// }

BOOL PlayerSystem::OnStubDisconnected( IEvent* pEvent )
{
	ConnectedEvent* pConnectedEvent = (ConnectedEvent*)pEvent;
	Stub* pStub = pConnectedEvent->GetStub();

	if( pStub->StubType() != STUB_TYPE_PLAYER )
	{
		return TRUE;
	}

	PlayerID_t nPlayerID = pStub->StubID( );

	Player* pPlayer = m_pPlayerManager->GetPlayer( nPlayerID );
	if( !pPlayer )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "PlayerSystem::OnDisconnected Error! can not find the player<%d>",
			nPlayerID );
		return TRUE;
	}

	// 离开场景
	if( !SceneSystem::m_pSceneSystem->GetScene()->LeaveScene(pPlayer) )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "player<%d> leave scene error!", pPlayer->PlayerID() );
	}

	pPlayer->UnAttachStub( );

	m_pPlayerManager->RemovePlayer( nPlayerID );

	return TRUE;
}