#include "StdAfx.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

BOOL PlayerManager::Initialize( )
{
	if( !m_PlayerPool.Init(DEFAULT_MAX_PLAYER_POOL_SIZE) )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PlayerManager::Initialize Failed, the player pool init failed!" );
		return FALSE;
	}

	m_mapPlayers.clear( );

	return TRUE;
}

BOOL PlayerManager::Finalize( )
{
	m_PlayerPool.Fina( );

	m_mapPlayers.clear( );

	return TRUE;
}

VOID PlayerManager::HeartBeat( INT iSkip, FLOAT fTimePass)
{
	PlayersMap::iterator itEnd = m_mapPlayers.end();
	for( PlayersMap::iterator it = m_mapPlayers.begin(); it != itEnd; ++it )
	{
		if( !it->second )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "PlayerManager::HeartBeat Error! the player list has null player!" );
			continue;
		}

		it->second->HeartBeat( iSkip, fTimePass );
	}
}

Player* PlayerManager::CreatePlayer( PlayerID_t nPlayerID )
{
	// find if has been created
	PlayersMap::iterator it = m_mapPlayers.find( nPlayerID );
	if( it != m_mapPlayers.end() )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "PlayerManager::CreatePlayer<%d> Warning, the player has been created!",
			nPlayerID );
		return it->second;
	}

	Player* pPlayer = m_PlayerPool.NewPlayer( );

	if( !pPlayer )
	{
		return NULL;
	}

	pPlayer->PlayerID( nPlayerID );

	if( !m_mapPlayers.insert( PlayersMap::value_type(nPlayerID, pPlayer) ).second )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PlayerManager::CreatePlayer<%d> Error!, insert to map failed!",
			nPlayerID );
		m_PlayerPool.DelPlayer( pPlayer );
		
		return NULL;
	}

	return pPlayer;
}

VOID PlayerManager::RemovePlayer( PlayerID_t nPlayerID )
{
	PlayersMap::iterator it = m_mapPlayers.find( nPlayerID );
	if( it == m_mapPlayers.end() )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "PlayerManager::RemovePlayer<%d> Warning!, does not find the player!",
			nPlayerID );
		return;
	}

	m_PlayerPool.DelPlayer( it->second );
	m_mapPlayers.erase( it );
}

Player*	PlayerManager::GetPlayer( PlayerID_t nPlayerID )
{
	PlayersMap::iterator it = m_mapPlayers.find( nPlayerID );
	if( it == m_mapPlayers.end() )
	{
		return NULL;
	}

	return it->second;
}