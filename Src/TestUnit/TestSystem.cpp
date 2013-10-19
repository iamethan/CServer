#include "TestSystem.h"
#include <iostream>
using namespace std;

TestSystem::TestSystem()
	: GSystem()
{
}

TestSystem::~TestSystem()
{
}

BOOL TestSystem::Initialize( VOID )
{
	

	return TRUE;
}

BOOL TestSystem::Finalize( VOID )
{
	return TRUE;
}

VOID TestSystem::InitPacketHandles( )
{
	DECLARE_PACKET_HANDLE( E_MOVE_REQ, TestSystem::OnTest );
}

VOID TestSystem::Tick( INT iSkip, FLOAT fTimePass)
{
	
}

PE_RESULT TestSystem::OnTest( CBasePack* pPacket, Stub* pStub )
{
	return PE_RESULT_OK;
}