#include "SceneSystem.h"
#include "Scene.h"

SceneSystem* SceneSystem::m_pSceneSystem = NULL;

SceneSystem::SceneSystem()
	: GSystem( )
{
	m_pSceneSystem = this;
}

SceneSystem::~SceneSystem()
{
}

BOOL SceneSystem::Initialize( VOID )
{
	m_pScene = new Scene();
	if( !m_pScene->Initialize() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "SceneSystem::Initialize Failed, when create scene" );
		return FALSE;
	}

	g_Log.SaveLog( LOG_LV_NORMAL, "SceneSystem::Initialize Successed!" );

	return TRUE;
}

BOOL SceneSystem::Finalize( VOID )
{
	if( !m_pScene->Finalize() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "scene finalize failed!" );
	}

	SAFE_DELETE( m_pScene );

	return TRUE;
}

VOID SceneSystem::HeartBeat( INT iSkip, FLOAT fTimePass)
{
}