#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "Utility.h"
#include "Event.h"
#include <map>

class IEventListener;

class EventManager
{
	typedef	std::map< UINT, IEvent* >	EventMap;

public:
	EventManager();
	virtual ~EventManager();

	IEvent* GetEvent( EVENT_TYPE eType, EVENT_ID eID );

	BOOL SendEvent( IEvent* pEvent );

	BOOL RegisterEventHandle( EVENT_TYPE eType, EVENT_ID eID, GSystem* pListener, IEvent::FuncAddr pHandleFunc );

protected:
	IEvent* CreateEvent( EVENT_ID eID );

protected:
	EventMap	m_mapEvents;
};

extern EventManager g_EventManager;

/////////////////////////////////////////////////////////////////////////////
// �¼�����
#define DECLARE_EVENT_HANDLE_BEGIN( CLASS ) \
	typedef BOOL (CLASS::*__EVENT_HANDLE) (IEvent* pEvent);	\
	typedef CLASS	__THIS_CLASS__;  \
	BOOL __HandleEvent( IEvent* pEvent, IEvent::FuncAddr pFunc )	\
	{	\
		__EVENT_HANDLE pCallBack = *((__EVENT_HANDLE*)&pFunc);	\
		return (this->*pCallBack)( pEvent );		\
	}	\
	VOID __InitEventHandles( ) {

#define DECLARE_EVENT_HANDLE_END()	}

#define EVENT_HANDLE( EVENTTYPE, EVENTID, HANDLEFUNC )	{	\
	__EVENT_HANDLE func = &__THIS_CLASS__::HANDLEFUNC;	\
	IEvent::FuncAddr pFunc = *((IEvent::FuncAddr*)(&func));	\
	g_EventManager.RegisterEventHandle(EVENTTYPE, EVENTID, this, pFunc); }

////////////////////////////////////////////////////////////////////
// helper

// ���ͽ��������¼�
BOOL SendConnectedEvent( Stub* pStub );

// ���ͶϿ������¼�
BOOL SendDisconnectedEvent( Stub* pStub );

// ���ͽ��볡���¼�
BOOL SendEnterSceneEvent( EVENT_TYPE eType, UINT nSenderID, UINT nSceneID );

// �����뿪�����¼�
BOOL SendLeaveSceneEvent( EVENT_TYPE eType, UINT nSenderID, UINT nSceneID );

#endif // __EVENT_MANAGER_H__