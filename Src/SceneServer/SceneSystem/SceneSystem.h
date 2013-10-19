#ifndef __SCENE_SYSTEM_H__
#define __SCENE_SYSTEM_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "Define/SystemDefine.h"

class Scene;

class SceneSystem : public GSystem
{
public:
	SceneSystem();
	virtual ~SceneSystem();

	const CHAR*	SystemName( VOID )	{ return "SceneSystem";				}
	const INT	SystemID( VOID )	{ return SYSTEM_ID_SCENE_SYSTEM;	}

	// 初始化
	BOOL		Initialize( VOID );

	// 回收处理
	BOOL		Finalize( VOID );

	// 心跳函数
	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	Scene*		GetScene( )	{ return m_pScene;	}

public:
	static SceneSystem*		m_pSceneSystem;

private:
	Scene*					m_pScene;
};

#endif // __SCENE_SYSTEM_H__