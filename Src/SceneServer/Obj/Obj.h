#ifndef __OBJ_H__
#define __OBJ_H__

#include "Utility.h"

enum OBJ_TYPE
{
	OBJ_TYPE_INVALID = -1,	// 无效类型
	OBJ_TYPE_PLAYER = 0,	// 玩家

	OBJ_TYPE_COUNT,
};

class Scene;

class Obj
{

	struct Attr
	{
		UINT	m_nID : 31 ;
		UINT	m_bDirty : 1 ;
		UINT	m_nValue ;
	};

public:
	Obj( ) 
		: m_nObjID( INVALID_ID ) 
		, m_eObjType( OBJ_TYPE_INVALID )
		, m_pScene( NULL )
	{}

	virtual ~Obj( ) 
	{}

	VOID		ObjID( ObjID_t nObjID )		{ m_nObjID = nObjID;				}
	ObjID_t		ObjID( )					{ return m_nObjID;					}

	VOID		ObjType( OBJ_TYPE eType )	{ m_eObjType = eType;				}
	OBJ_TYPE	ObjType( )					{ return m_eObjType;				}

	VOID		SetScene( Scene* pScene )	{ m_pScene = pScene;				}
	Scene*		GetScene( )					{ return m_pScene;					}

	VOID		Pos( WORLD_POS& tPos )		{ m_tPos = tPos;					}
	VOID		Pos( FLOAT fX, FLOAT fZ )	{ m_tPos.m_fX=fX; m_tPos.m_fZ=fZ;	}
	WORLD_POS&	Pos( )						{ return m_tPos;					}

	VOID		Dir( FLOAT fDir )			{ m_fDir = fDir;					}
	FLOAT		Dir( )						{ return m_fDir;					}

	//////////////////////////////////////////////////////////////////
	// Actions
	virtual	BOOL	SyncBaseAttrs( VOID ) { return TRUE;}
	virtual	BOOL	SyncMotifyAttrs( VOID ) { return TRUE ;}

protected:
	ObjID_t			m_nObjID;
	OBJ_TYPE		m_eObjType;		
	
	WORLD_POS		m_tPos;		// 场景中坐标
	FLOAT			m_fDir;		// 朝向

	Scene*			m_pScene;	// 所在场景

protected:
	// POOL相关
	UINT	GetPoolID( )			{ return m_nPoolID;	}
	VOID	SetPoolID( UINT id )	{ m_nPoolID = id;	}
	BOOL	m_bIsEmpty;	// 是否空闲，空闲中，可以被Pool分配出去继续使用
	UINT	m_nPoolID;
};

class StaticObj : public Obj
{
public:
	StaticObj( )
		: Obj( )
	{}

	virtual ~StaticObj( )
	{}

protected:
};

enum MOVE_STATE
{
	MOVE_STATE_STATIC = 0,	// 静止
	MOVE_STATE_MOTION,		// 陆地行走
	MOVE_STATE_JUMP,		// 跳跃
};

class DynamicObj : public Obj
{
public:
	DynamicObj( )
		: Obj( )
	{}

	virtual ~DynamicObj( )
	{}

	VOID			Speed( FLOAT fSpeed )			{ m_fSpeed = fSpeed;		}
	FLOAT			Speed( )						{ return m_fSpeed;			}

	VOID			MoveState( MOVE_STATE eState )	{ m_eMoveState = eState;	}
	MOVE_STATE		MoveState( )					{ return m_eMoveState;		}

	VOID			TarPos( WORLD_POS& tPos );
	VOID			TarPos( FLOAT fX, FLOAT fZ );
	WORLD_POS&		TarPos( )						{ return m_tTarPos;			}

	virtual VOID	HeartBeat( INT iSkip, FLOAT fTimePass);

protected:
	WORLD_POS		m_tTarPos;		// 目标位置
	FLOAT			m_fSpeed;		// 移动速度
	MOVE_STATE		m_eMoveState;	// 移动状态
};

#endif // __OBJ_H__