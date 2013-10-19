#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Utility.h"
#include "Net.h"
#include "Obj/Obj.h"

#define PLAYER_NAME_MAX_SIZE	64

class PlayerManager;
class PlayerSystem;

class Player : public DynamicObj
{
	friend class ObjPool< Player >;
	friend class PlayerManager;
	friend class PlayerSystem;
public:
	Player();
	virtual ~Player();

	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	//////////////////////////////////////////////////////////
	// 行为

	// 单播
	BOOL		SendPacket( BasePacket* pPacket );

	// 广播给周围玩家
	BOOL		BroadCast( BasePacket* pPacket, BOOL bSelf = FALSE );

	////////////////////////////////////////////////////////
	// 基础属性
public:
	PlayerID_t	PlayerID( )							{ return m_nObjID;			}

	const CHAR*	PlayerName( )						{ return m_sPlayerName;		}

	VOID		Level( BYTE btLevel )				{ m_btLevel = btLevel;		}
	BYTE		Level( )							{ return m_btLevel;			}

	VOID		Sex( BYTE btSex )					{ m_btSex = btSex;			}
	BYTE		Sex( )								{ return m_btSex;			}

	VOID		HP( UINT nHP )						{ m_nHP = nHP;				}
	UINT		HP( )								{ return m_nHP;				}

	VOID		MP( UINT nMP )						{ m_nMP = nMP;				}
	UINT		MP( )								{ return m_nMP;				}

protected:
	VOID		PlayerID( PlayerID_t nPlayerID )	{ m_nObjID = nPlayerID;				}
	VOID		PlayerName( const CHAR* sName )		{ strcpy( m_sPlayerName, sName );	}

protected:
	// stub
	BOOL			AttachStub( Stub* pStub );
	VOID			UnAttachStub( );
	Stub*			AttachedStub( )					{ return m_pAttachedStub;												}
	StubInnerID_t	AttachedStubInnerID( )			{ return ( m_pAttachedStub ? m_pAttachedStub->InnerID() : INVALID_ID );	}

private:
	// 属性
	CHAR		m_sPlayerName[PLAYER_NAME_MAX_SIZE];
	BYTE		m_btLevel;
	BYTE		m_btSex;
	UINT		m_nHP;
	UINT		m_nMP;

	// stub
	Stub*		m_pAttachedStub;
};

#endif // __PLAYER_H__