#include "EventManager.h"
#include "Event.h"
#include "../GSystem.h"

EventManager g_EventManager;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	EventMap::iterator itEnd = m_mapEvents.end();
	for( EventMap::iterator it = m_mapEvents.begin(); it != m_mapEvents.end(); ++it )
	{
		SAFE_DELETE( it->second );
	}
	m_mapEvents.clear();
}

IEvent* EventManager::CreateEvent( EVENT_ID eID )
{
	switch( eID )
	{
	case EVENT_ID_ON_CONNECTED:
		return new ConnectedEvent;
	case EVENT_ID_ON_DISCONNECTED:
		return new DisconnectedEvent;
	case EVENT_ID_ON_ENTERSCENE:
		return new EnterSceneEvent;
	case EVENT_ID_ON_LEAVESCENE:
		return new LeaveSceneEvent;
	case EVENT_ID_ON_READY:
		return new ReadyEvent;
	case EVENT_ID_ON_MOTION:
		return new MotionEvent;
	case EVENT_ID_ON_USESKILL:
		return new UseSkillEvent;
	case EVENT_ID_ON_BE_DAMAGE:
		return new BeDamageEvent;
	case EVENT_ID_ON_BE_KILLED:
		return new BeKilledEvent;
	case EVENT_ID_ON_DAMAGE:
		return new DamageEvent;
	case EVENT_ID_ON_KILL:
		return new KillEvenet;
	}

	return NULL;
}

IEvent* EventManager::GetEvent( EVENT_TYPE eType, EVENT_ID eID )
{
	UINT nTypeID = EVENT_TYPEID( eType, eID );

	EventMap::iterator it = m_mapEvents.find( nTypeID );
	if( it == m_mapEvents.end() )
	{
		g_Log.SaveLog( LOG_LV_WARNING, "get event warning, the event<%d, %d> has not been register handle",
			eType, eID );

		IEvent* pEvent = CreateEvent( eID );
		pEvent->Type( eType );

		if( !m_mapEvents.insert(EventMap::value_type(nTypeID, pEvent)).second )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "event manager error! when insert event<%d, %d> to map",
				eType, eID );
			SAFE_DELETE( pEvent );
			return NULL;
		}

		return pEvent;
	}

	return it->second;
}

BOOL EventManager::SendEvent( IEvent* pEvent )
{
	if( !pEvent )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "send null event!" );
		return FALSE;
	}

	IEvent::HandleList::iterator itEnd = pEvent->m_lstHandles.end();
	for( IEvent::HandleList::iterator it = pEvent->m_lstHandles.begin(); it != itEnd; ++it )
	{
		IEvent::Handle* pHandle = *it;
		Assert( pHandle );

		if( !(pHandle->m_pListener->__HandleEvent(pEvent, pHandle->m_pFuncHandle)) )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "the system<%s> handle event<%d, %d> failed",
				pHandle->m_pListener->SystemName(), pEvent->Type(), pEvent->ID() );
		}
	}

	return TRUE;
}

BOOL EventManager::RegisterEventHandle( EVENT_TYPE eType, EVENT_ID eID, GSystem* pListener, IEvent::FuncAddr pHandleFunc )
{
	UINT nTypeID = EVENT_TYPEID( eType, eID );

	IEvent* pEvent = NULL;

	EventMap::iterator it = m_mapEvents.find( nTypeID );
	if( it == m_mapEvents.end() )
	{
		pEvent = CreateEvent( eID );
		pEvent->Type( eType );

		if( !m_mapEvents.insert(EventMap::value_type(nTypeID, pEvent)).second )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "event manager register event<%d, %d> handle failed when insert to map",
				nTypeID, eID );
			SAFE_DELETE( pEvent );
			return FALSE;
		}
	}
	else
	{
		pEvent = it->second;
	}

	Assert( pEvent );

	return pEvent->RegisterHandle( pListener, pHandleFunc );
}

////////////////////////////////////////////////////////////////////
// helper

BOOL SendConnectedEvent( Stub* pStub )
{
	ConnectedEvent* pEvent = (ConnectedEvent*)g_EventManager.GetEvent( EVENT_TYPE_STUB, EVENT_ID_ON_CONNECTED );
	if( pEvent )
	{
		pEvent->SetStub( pStub );
	}

	return g_EventManager.SendEvent( pEvent );
}

BOOL SendDisconnectedEvent( Stub* pStub )
{
	DisconnectedEvent* pEvent = (DisconnectedEvent*)g_EventManager.GetEvent( EVENT_TYPE_STUB, EVENT_ID_ON_DISCONNECTED );
	if( pEvent )
	{
		pEvent->SetStub( pStub );
	}

	return g_EventManager.SendEvent( pEvent );
}

BOOL SendEnterSceneEvent( EVENT_TYPE eType, UINT nSenderID, UINT nSceneID )
{
	EnterSceneEvent* pEvent = (EnterSceneEvent*)g_EventManager.GetEvent( eType, EVENT_ID_ON_ENTERSCENE );
	if( pEvent )
	{
		pEvent->Sender( nSenderID );
		pEvent->SceneID( nSceneID );
	}

	return g_EventManager.SendEvent( pEvent );
}

BOOL SendLeaveSceneEvent( EVENT_TYPE eType, UINT nSenderID, UINT nSceneID )
{
	LeaveSceneEvent* pEvent = (LeaveSceneEvent*)g_EventManager.GetEvent( eType, EVENT_ID_ON_LEAVESCENE );
	if( pEvent )
	{
		pEvent->Sender( nSenderID );
		pEvent->SceneID( nSceneID );
	}

	return g_EventManager.SendEvent( pEvent );
}