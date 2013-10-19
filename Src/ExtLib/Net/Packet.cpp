#include "Packet.h"

BOOL IPacketFactory::RegisterHandle( IPacketListener* pListener, FuncAddr pFuncHandle )
{
	// 查找是否已经注册
	HandleList::iterator itEnd = m_lstHandles.end();
	for( HandleList::iterator it = m_lstHandles.begin(); it != itEnd; ++it )
	{
		if( (*it)->m_pListener == pListener )
		{
			g_Log.SaveLog(LOG_LV_WARNING, "register event handle warning! the listener<%s> has been registed!",
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