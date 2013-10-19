#include "StdAfx.h"
#include "SceneServer.h"
#include "PlayerSystem/PlayerSystem.h"
#include "SceneSystem/SceneSystem.h"
#include "MotionSystem/MotionSystem.h"
#include "SkillSystem/SkillSystem.h"
#include "ConfigSystem/ConfigSystem.h"
#include "Define/ProtocolDefine.h"


SceneServer::SceneServer()
	: GApp()
{
	m_pApp = this;
}

SceneServer::~SceneServer()
{
}

BOOL SceneServer::Initialize( ) 
{
	if( !GApp::Initialize() )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL SceneServer::Finalize( ) 
{
	BOOL bRet = GApp::Finalize();

	SAFE_DELETE( m_pMotionSystem );
	SAFE_DELETE( m_pSceneSystem );
	SAFE_DELETE( m_pPlayerSystem );
	SAFE_DELETE( m_pSkillSystem );
	SAFE_DELETE( m_pConfigSystem );

	return bRet;
}

VOID SceneServer::InitSystems( )
{
	m_pPlayerSystem = new PlayerSystem;
	RegisterSystem( (GSystem*)m_pPlayerSystem );

	m_pSceneSystem = new SceneSystem;
	RegisterSystem( (GSystem*)m_pSceneSystem );

	m_pMotionSystem = new MotionSystem;
	RegisterSystem( (GSystem*)m_pMotionSystem );

	m_pSkillSystem = new SkillSystem;
	RegisterSystem( (GSystem*)m_pSkillSystem );

	m_pConfigSystem = new ConfigSystem;
	RegisterSystem( (GSystem*)m_pConfigSystem );
}

VOID SceneServer::InitPacketFactories( ) 
{
	DECLARE_PACKET( SC_ConnectStatus_REV, PID_SC_ConnectStatus_REV ) ;
	DECLARE_PACKET( CS_ReCreate_REQ, PID_CS_ReCreate_REQ ) ;
	DECLARE_PACKET( SC_Create_NTF, PID_SC_Create_NTF ) ;
	DECLARE_PACKET( CS_Create_REQ, PID_CS_Create_REQ ) ;
	DECLARE_PACKET( SC_Create_REV, PID_SC_Create_REV ) ;
	DECLARE_PACKET( CS_Action_REQ, PID_CS_Action_REQ ) ;
	DECLARE_PACKET( SC_Action_REV, PID_SC_Action_REV ) ;
	DECLARE_PACKET( SC_Action_NTF, PID_SC_Action_NTF ) ;
	DECLARE_PACKET( CS_SkillStart_REQ, PID_CS_SkillStart_REQ ) ;
	DECLARE_PACKET( SC_SkillStatus_REV, PID_SC_SkillStatus_REV ) ;
	DECLARE_PACKET( SC_SkillStatus_NTF, PID_SC_SkillStatus_NTF ) ;
	DECLARE_PACKET( SC_SkillEnd_NTF, PID_SC_SkillEnd_NTF ) ;
	DECLARE_PACKET( SC_PlayerStatus_NTF, PID_SC_PlayerStatus_NTF ) ;
	DECLARE_PACKET( CS_PlayerMove_REQ, PID_CS_PlayerMove_REQ ) ;
	DECLARE_PACKET( SC_PlayerMove_NTF, PID_SC_PlayerMove_NTF ) ;
	DECLARE_PACKET( CS_PlayerMoveEnd_REQ, PID_CS_PlayerMoveEnd_REQ ) ;
	DECLARE_PACKET( SC_RelieveBuff_NTF, PID_SC_RelieveBuff_NTF ) ;
	DECLARE_PACKET( SC_RemovePlayer_NTF, PID_SC_RemovePlayer_NTF ) ;
}

#if defined(__WINDOWS__)
char * g_dump_exe_name = "SceneServer";
#endif

#ifdef __WINDOWS__
#include <Windows.h>
// 控制台回调
BOOL WINAPI ConsoleHandle( DWORD dwCtrlType )
{
	switch( dwCtrlType )
	{
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_C_EVENT:
		{
			GetApp()->Quit( TRUE );
		}
		break;
	}

	return TRUE;
}
#endif

INT main(INT argc, CHAR* argv[])
{

#if defined(__WINDOWS__)
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	_CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);

	// 添加控制台回调
	SetConsoleCtrlHandler( ConsoleHandle, TRUE );
#endif

__ENTER_FUNCTION

	g_Log.ChangeFileName( "../Log/SceneServer" );

	g_Log.SaveLog( LOG_LV_NORMAL, "SceneServer starting..." );
	
	SceneServer svr;

	if( !svr.Initialize() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "SceneServer Initialize failed!" );
		return 0;
	}

	svr.DumpRPSInfo( FALSE );

	g_Log.SaveLog( LOG_LV_NORMAL, "SceneServer Initialize Successed!" );

	g_Log.SaveLog( LOG_LV_NORMAL, "SceneServer started!" );

	svr.Run();

	if( !svr.Finalize() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "SceneServer Finalize failed!" );
		return 0;
	}

	g_Log.SaveLog( LOG_LV_NORMAL, "SceneServer Finalize Successed!" );
		

__LEAVE_FUNCTION
	
	return 0;
}
