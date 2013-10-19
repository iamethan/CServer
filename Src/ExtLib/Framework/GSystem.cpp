#include "GSystem.h"
#include "Net.h"

GSystem::GSystem()
{
}

GSystem::~GSystem()
{
}

BOOL GSystem::__Initialize( )
{
__ENTER_FUNCTION

	__InitEventHandles();
	__InitPacketHandles();

	return Initialize( );

__LEAVE_FUNCTION
	
	return FALSE;
}

BOOL GSystem::__Finalize( )
{
__ENTER_FUNCTION

	BOOL ret = Finalize( );

	return ret;

__LEAVE_FUNCTION

	return FALSE;
}
