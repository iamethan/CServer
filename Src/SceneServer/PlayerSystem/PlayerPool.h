#ifndef __PLAYER_POOL_H__
#define __PLAYER_POOL_H__

#include "Utility.h"

class Player;

class PlayerPool
{
public:
	PlayerPool( );
	~PlayerPool( );

	BOOL Init( UINT nMaxSize );
	VOID Fina( );

	Player*	NewPlayer( );

	VOID	DelPlayer( Player* pPlayer );

private:
	ObjPool< Player >	m_PlayerPool;
};

#endif // __PLAYER_POOL_H__