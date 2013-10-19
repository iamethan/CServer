#include "PacketFactoryManager.h"

PacketFactoryManager g_PacketFactoryManager ;

PacketFactoryManager::PacketFactoryManager( ) 
{
__ENTER_FUNCTION

			
__LEAVE_FUNCTION
}

PacketFactoryManager::~PacketFactoryManager( ) 
{
__ENTER_FUNCTION
		
	PacketFactoryMap::iterator itEnd = m_mapFactories.end();
	for( PacketFactoryMap::iterator iter = m_mapFactories.begin(); iter!=itEnd; ++iter )
	{
		SAFE_DELETE( iter->second )
	}

	m_mapFactories.clear();
			
__LEAVE_FUNCTION
}

BOOL PacketFactoryManager::AddFactory( IPacketFactory* pFactory ) 
{
__ENTER_FUNCTION

	Assert( pFactory );

	PacketID_t packet_id = pFactory->GetPacketID();

	PACKET_FACTORY* pFactoryStruct = new PACKET_FACTORY;
	pFactoryStruct->m_pFactory = pFactory;
	pFactoryStruct->m_nPacketCount = 0;

	BOOL ret = m_mapFactories.insert( PacketFactoryMap::value_type(packet_id, pFactoryStruct) ).second;

	if( !ret )
	{
		SAFE_DELETE( pFactoryStruct );

		g_Log.SaveLog( LOG_LV_ERROR, "PacketFactoryManager::AddFactory<%d> Error!", (int)packet_id );
		return FALSE;
	}

	return TRUE;
			
__LEAVE_FUNCTION

	return FALSE;
}

IPacketFactory* PacketFactoryManager::GetFactory( PacketID_t packetID )
{
__ENTER_FUNCTION

	PACKET_FACTORY* pStruct = GetFactoryStruct( packetID );
	if( !pStruct )
	{
		return NULL;
	}

	return pStruct->m_pFactory;

__LEAVE_FUNCTION

	return NULL;
}

PacketFactoryManager::PACKET_FACTORY* PacketFactoryManager::GetFactoryStruct( PacketID_t nPacketID )
{
	PacketFactoryMap::iterator iter = m_mapFactories.find( nPacketID );
	if( iter == m_mapFactories.end() )
	{
		return NULL;
	}

	return iter->second;
}

BasePacket* PacketFactoryManager::CreatePacket( PacketID_t packetID ) 
{
__ENTER_FUNCTION

	PACKET_FACTORY* pStruct = GetFactoryStruct( packetID );
	if( !pStruct )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PacketFactoryManager::CreatePacket<%d> Error! can not find the factory!",
			packetID );
		return NULL;
	}

	BasePacket* pPacket = pStruct->m_pFactory->CreatePacket();
	if( pPacket )
	{
		++(pStruct->m_nPacketCount);
	}
	else
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PacketFactoryManager::CreatePacket<%d> Error! get null packet!",
			packetID );
	}

	return pPacket ;
			
__LEAVE_FUNCTION

	return NULL ;
}

VOID PacketFactoryManager::RemovePacket( BasePacket* pPacket )
{
__ENTER_FUNCTION

	if( pPacket==NULL )
	{
		Assert(FALSE) ;
		return ;
	}

	PacketID_t packetID = pPacket->uID ;

	PACKET_FACTORY* pStruct = GetFactoryStruct( packetID );
	if( !pStruct )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "PacketFactoryManager::RemovePacket<%d> Error! can not find the factory!",
			packetID );
		return;
	}

	SAFE_DELETE( pPacket );
	--(pStruct->m_nPacketCount);
	
	return ;

__LEAVE_FUNCTION

	return ;
}

BOOL PacketFactoryManager::HandlePacket( BasePacket* pPacket, Stub* pStub )
{
__ENTER_FUNCTION

	if( !pPacket || !pStub )
	{
		return FALSE;
	}

	IPacketFactory* pFactory = GetFactory( pPacket->uID );
	if( !pFactory )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "the packet<%d> has not been declared!",
			pPacket->uID );
		return FALSE;
	}

	IPacketFactory::HandleList::iterator itEnd = pFactory->m_lstHandles.end();
	for( IPacketFactory::HandleList::iterator it = pFactory->m_lstHandles.begin(); it != itEnd; ++it )
	{
		IPacketFactory::Handle* pHandle = *it;
		Assert( pHandle );

		if( !(pHandle->m_pListener->__HandlePacket(pPacket, pStub, pHandle->m_pFuncHandle) ) )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "sys<%s> handle packet<%d> error!",
				pHandle->m_pListener->SystemName(), pPacket->uID );
		}
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL PacketFactoryManager::RegistePacketHandle( PacketID_t nPacketID, IPacketListener* pListener, IPacketFactory::FuncAddr pHandleFunc )
{
__ENTER_FUNCTION

	IPacketFactory* pFactory = GetFactory( nPacketID );
	if( !pFactory )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "register packet handle error! the packet<%d> has not been registed!",
			nPacketID );
		return FALSE;
	}

	return pFactory->RegisterHandle( pListener, pHandleFunc );

__LEAVE_FUNCTION

	return FALSE;
}