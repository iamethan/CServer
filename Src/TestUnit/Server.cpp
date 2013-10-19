#include "server.h"
#include "CS_PACK.h"
#include "TestSystem.h"

Server::Server()
	: GApp()
{
}

Server::~Server()
{
}

BOOL Server::Initialize( ) 
{
	

	return GApp::Initialize();
}

BOOL Server::Finalize( ) 
{
	return GApp::Finalize();
}

VOID Server::InitSystems( )
{
	m_pTestSystem = new TestSystem;
	RegisterSystem( (GSystem*)m_pTestSystem );
}

VOID Server::InitPacketFactories( ) 
{
	DECLARE_PACKET( CTransformPack_REQ, E_MOVE_REQ ) ;
	DECLARE_PACKET( CTransformPack_NTF, E_MOVE_NTF ) ;
	DECLARE_PACKET( CTransformEndPack_REQ, E_MOVE_END_REQ ) ;
	DECLARE_PACKET( CReCreate_REQ, E_RECREATE_REQ ) ;
	DECLARE_PACKET( CActionPack_REQ, E_ACTION_REQ ) ;
	DECLARE_PACKET( CActionPack_REV, E_ACTION_REV ) ;
	DECLARE_PACKET( CStatusPack_NTF, E_STATUS_NTF ) ;
	DECLARE_PACKET( CSkillPack_REQ, E_SKILL_REQ ) ;
	DECLARE_PACKET( CSkillPack_REV, E_SKILL_REV ) ;
	DECLARE_PACKET( CSkillPack_NTF, E_SKILL_NTF ) ;
	DECLARE_PACKET( CSkillStatus_NTF, E_SKILLSTUAS_NTF ) ;
	DECLARE_PACKET( CCreatePlayer_NTF, E_CREATE_NTF ) ;
	DECLARE_PACKET( CCreatePlayer_REV, E_CREATE_REV ) ;
	DECLARE_PACKET( CRemovePlayer_NTF, E_REMOVE_NTF ) ;
}