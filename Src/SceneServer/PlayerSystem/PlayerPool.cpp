#include "StdAfx.h"
#include "PlayerPool.h"
#include "Player.h"

PlayerPool::PlayerPool( )
{
}

PlayerPool::~PlayerPool( )
{
}

BOOL PlayerPool::Init( UINT nMaxSize )
{
	return m_PlayerPool.Init( nMaxSize );
}

VOID PlayerPool::Fina( )
{
	m_PlayerPool.Term( );
}

Player*	PlayerPool::NewPlayer( )
{
	
	Player* pStub = m_PlayerPool.NewObj();

	return pStub;
}

VOID PlayerPool::DelPlayer( Player* pPlayer )
{
	if( !pPlayer )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "PlayerPool::DelPlayer Warning, delete null player" );
		return;
	}

	m_PlayerPool.DeleteObj( pPlayer );
}