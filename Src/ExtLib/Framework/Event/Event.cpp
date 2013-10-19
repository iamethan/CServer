#include "Event.h"
#include "../GSystem.h"

IEvent::IEvent()
{
}

IEvent::~IEvent( )
{
	HandleList::iterator itEnd = m_lstHandles.end();
	for( HandleList::iterator it = m_lstHandles.begin(); it != itEnd; ++it )
	{
		delete (*it);
	}

	m_lstHandles.clear();
}

BOOL IEvent::RegisterHandle( GSystem* pListener, FuncAddr pFuncHandle )
{
	// 查找是否已经注册
	HandleList::iterator itEnd = m_lstHandles.end();
	for( HandleList::iterator it = m_lstHandles.begin(); it != itEnd; ++it )
	{
		if( (*it)->m_pListener == pListener )
		{
			g_Log.SaveLog(LOG_LV_WARNING, "register event handle warning! the sys<%s> has been registed!",
				pListener->SystemName() );
			return FALSE;
		}
	}

	Handle* pHandle = new Handle;
	pHandle->m_pListener = pListener;
	pHandle->m_pFuncHandle = pFuncHandle;

	m_lstHandles.push_back( pHandle );

	return TRUE;
}