#ifndef __G_SYSTEM_H__
#define __G_SYSTEM_H__

#include <map>
#include "Utility.h"
#include "Net.h"
#include "Event/Event.h"

class GApp;
class Stub;
class Obj;

class GSystem : public IPacketListener
{
	friend class GApp;
	friend class EventManager;

public:
	GSystem();
	virtual ~GSystem();

	virtual const CHAR*	SystemName( VOID )	= 0;
	virtual const INT	SystemID( VOID )	= 0;

	virtual	BOOL		Initialize( VOID )	{ return TRUE;	}
	virtual	BOOL		Finalize( VOID )	{ return TRUE;	}

	virtual VOID		HeartBeat( INT iSkip, FLOAT fTimePass) {}

	virtual VOID		OnConnected( Stub* pStub ) {}
	virtual VOID		OnDisconnected( Stub* pStub ) {}

private:
	BOOL			__Initialize( );
	BOOL			__Finalize( );
	virtual BOOL	__HandleEvent( IEvent* pEvent, IEvent::FuncAddr pFunc )		{ return TRUE;	}
	virtual VOID	__InitEventHandles( VOID )	{}
};

typedef std::map< INT, GSystem* >	SystemPtrMap;

#endif // __G_SYSTEM_H__