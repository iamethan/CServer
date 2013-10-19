#ifndef __SERVER_H__
#define __SERVER_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"

class TestSystem;

class Server : public GApp
{
public:
	Server();
	virtual ~Server();

	BOOL Initialize( ) ;
	BOOL Finalize( ) ;

	VOID InitSystems( );
	VOID InitPacketFactories( ) ;

private:
	TestSystem* m_pTestSystem;
};

#endif // __SERVER_H__