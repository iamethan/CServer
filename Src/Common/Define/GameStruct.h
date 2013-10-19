
#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "Base/Type.h"
#include "GameDefine.h"

//用来定义在世界的网格位置
struct MAP_POS
{
	Coord_t	 m_nX ;
	Coord_t	 m_nZ ;

	MAP_POS(VOID)					: m_nX(0)	, m_nZ(0)	{}
	MAP_POS(Coord_t nX, Coord_t nZ)	: m_nX(nX)	, m_nZ(nZ)	{}
	VOID	CleanUp( ){
		m_nX = 0 ;
		m_nX = 0 ;
	};
};


//玩家基本序列化信息
struct PLAYER_OWN
{
	GUID_t    m_nGUID;						//玩家完全唯一ID
	CHAR	  m_szName[MAX_CHARACTER_NAME];	//玩家姓名
	
	Coord_t   m_nX;						//玩家位置X
	Coord_t   m_nZ;						//玩家位置Z

	FLOAT     m_fDir;						//玩家面朝的方向（范围：0~1.0）
										//
										//       0.25 
										//    \   |   /
										// 0.5  \ | /
										//   ----   ----  0.0 (1.0f)
										//      / | \
										//    /   |   \
										//       0.75

	PLAYER_OWN( )
	{
		m_nGUID = INVALID_ID ;
		memset( m_szName, 0, MAX_CHARACTER_NAME ) ;
		m_nX = 0 ;
		m_nZ = 0 ;
		m_fDir = 0.0 ;
	};
};

struct PLAYER_S
{
	GUID_t    m_nGUID;						//玩家完全唯一ID
	CHAR	  m_szName[MAX_CHARACTER_NAME];	//玩家姓名
	
	Coord_t   m_nX;						//玩家位置X
	Coord_t   m_nZ;						//玩家位置Z

	FLOAT     m_fDir;						//玩家面朝的方向（范围：0~1.0）
										//
										//       0.25 
										//    \   |   /
										// 0.5  \ | /
										//   ----   ----  0.0 (1.0f)
										//      / | \
										//    /   |   \
										//       0.75

	PLAYER_S( )
	{
		m_nGUID = INVALID_ID ;
		memset( m_szName, 0, MAX_CHARACTER_NAME ) ;
		m_nX = 0 ;
		m_nZ = 0 ;
		m_fDir = 0.0 ;
	};
};

struct VRECT
{
	INT nStartx ;
	INT nStartz ;
	INT nEndx ;
	INT nEndz ;

	VRECT( )
	{
		nStartx = 0 ;
		nStartz = 0 ;
		nEndx = 0 ;
		nEndz = 0 ;
	};

	BOOL IsContinue( INT x, INT z )const
	{
		if ( x < nStartx || x > nEndx || z < nStartz || z > nEndz )
			return FALSE;
		else
			return TRUE;
	}
};




//最大伤害纪录
#define		MAX_DAMAGE_REC_COUNT	10


#endif
