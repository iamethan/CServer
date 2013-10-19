#ifndef __SERVER_SCENE_H__
#define __SERVER_SCENE_H__

#include "Framework.h"

class PlayerSystem;
class SceneSystem;
class MotionSystem;
class ConfigSystem;
class SkillSystem;

class SceneServer : public GApp
{
public:
	SceneServer();
	virtual ~SceneServer();

	BOOL Initialize( ) ;
	BOOL Finalize( ) ;

	VOID InitSystems( );
	VOID InitPacketFactories( ) ;

public:
	PlayerSystem*	m_pPlayerSystem;
	SceneSystem*	m_pSceneSystem;
	MotionSystem*	m_pMotionSystem;
	SkillSystem*	m_pSkillSystem;
	ConfigSystem*	m_pConfigSystem;
};

#endif // __SERVER_SCENE_H__