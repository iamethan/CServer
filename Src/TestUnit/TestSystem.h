#ifndef __TEST_SYSTEM_H__
#define __TEST_SYSTEM_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "CS_PACK.h"

class TestSystem : public GSystem
{
public:
	TestSystem();
	virtual ~TestSystem();

	const CHAR*	SystemName( VOID )	{ return "TestSystem";	}
	const INT	SystemID( VOID )	{ return 1;	}

	BOOL		Initialize( VOID );
	BOOL		Finalize( VOID );

	VOID		InitPacketHandles( );

	VOID		Tick( INT iSkip, FLOAT fTimePass);

public:
	static PE_RESULT OnTest( CBasePack* pPacket, Stub* pStub );

};

#endif // __TEST_SYSTEM_H__