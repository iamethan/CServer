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
// 事件处理
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

// 发送建立连接事件
BOOL SendConnectedEvent( Stub* pStub );

// 发送断开连接事件
BOOL SendDisconnectedEvent( Stub* pStub );

// 发送进入场景事件
BOOL SendEnterSceneEvent( EVENT_TYPE eType, UINT nSenderID, UINT nSceneID );

// 发送离开场景事件
BOOL SendLeaveSceneEvent( EVENT_TYPE eType, UINT nSenderID, UINT nSceneID );

#endif // __EVENT_MANAGER_H__