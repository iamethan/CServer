#include "StdAfx.h"
#include "Player.h"
#include "SceneSystem/Scene.h"
#include "SceneServer.h"

Player::Player()
	: DynamicObj()
{
	m_pAttachedStub = NULL;
	memset( m_sPlayerName, NULL, sizeof(m_sPlayerName) );
	m_btLevel = 0;
	m_btSex = 0;
	m_nHP = 0;
	m_nMP = 0;

	ObjType( OBJ_TYPE_PLAYER );
}

Player::~Player()
{
}

VOID Player::HeartBeat( INT iSkip, FLOAT fTimePass)
{
	DynamicObj::HeartBeat( iSkip, fTimePass );

	// do yourself
}

BOOL Player::SendPacket( BasePacket* pPacket )
{
	if( !m_pAttachedStub )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Player<%d> send packet failed! do not attach to stub",
			PlayerID() );
		return FALSE;
	}

	return m_pAttachedStub->SendPacket( pPacket );
}

BOOL Player::BroadCast( BasePacket* pPacket, BOOL bSelf/* = FALSE*/ )
{
	if( !m_pScene )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "Player<%d> broadcast packet failed! do not enter any scene",
			PlayerID() );
		return FALSE;
	}

	return m_pScene->BroadCast( pPacket, this, bSelf );
}

BOOL Player::AttachStub( Stub* pStub )
{
	if( m_pAttachedStub  )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "Player<%d>::AttachStub Warning, the player has been attached stub<%d>!",
			PlayerID(), AttachedStubInnerID() );
		return FALSE;
	}

	if( pStub->StubID() != INVALID_ID )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "Player<%d>::AttachStub Warning, the stub has been used for player<%d>!",
			PlayerID(), pStub->StubID() );
		return FALSE;
	}

	// attach
	pStub->StubID( PlayerID() );
	pStub->StubType( STUB_TYPE_PLAYER );
	m_pAttachedStub = pStub;

	return TRUE;
}

VOID Player::UnAttachStub( )
{
	if( !m_pAttachedStub )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "Player<%d>::UnAttachStub Warning!, has not been attached to stub",
			PlayerID() );
		return;
	}

	// unattach
	m_pAttachedStub->StubID( INVALID_ID );
	m_pAttachedStub->StubType( STUB_TYPE_INVALID );
	m_pAttachedStub = NULL;
}