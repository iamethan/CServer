#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__

#include "Utility.h"
#include <map>
#include "Player.h"
#include "PlayerPool.h"

#define DEFAULT_MAX_PLAYER_POOL_SIZE 2000

class PlayerManager
{
	typedef std::map< PlayerID_t, Player* >		PlayersMap;
public:
	PlayerManager();
	~PlayerManager();

	BOOL	Initialize( );
	BOOL	Finalize( );

	VOID	HeartBeat( INT iSkip, FLOAT fTimePass);

	Player* CreatePlayer( PlayerID_t nPlayerID );
	VOID	RemovePlayer( PlayerID_t nPlayerID );
	Player*	GetPlayer( PlayerID_t nPlayerID );

protected:
	PlayerPool			m_PlayerPool;
	PlayersMap			m_mapPlayers;
};

#endif // __PLAYER_MANAGER_H__