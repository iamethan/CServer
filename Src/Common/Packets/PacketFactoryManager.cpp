#include "PacketFactoryManager.h"
#include "BasePackets.h"
#include "PacketHandle.h"

PacketFactoryManager* g_pPacketFactoryManager = NULL ;

PacketFactoryManager::PacketFactoryManager( ) 
{
__ENTER_FUNCTION

	m_Factories = NULL ;
	m_Size = E_MESSAGE_COUNT ;

	Assert( m_Size>0 ) ;
	
	m_Factories = new IPacketFactory*[ m_Size ];
	Assert( m_Factories ) ;
	m_pPacketAllocCount = new UINT[m_Size] ;
	Assert( m_pPacketAllocCount ) ;
	
	for( INT i=0; i<m_Size; i++ ) 
	{
		m_Factories[i] = NULL ;
		m_pPacketAllocCount[i] = 0 ;
	}
			
__LEAVE_FUNCTION
}

PacketFactoryManager::~PacketFactoryManager( ) 
{
__ENTER_FUNCTION
		
	Assert( m_Factories!=NULL ) ;

	for( INT i=0; i<m_Size; i++ ) 
	{
		SAFE_DELETE(m_Factories[i]) ;
	}
	
	SAFE_DELETE_ARRAY(m_Factories) ;
	SAFE_DELETE_ARRAY(m_pPacketAllocCount) ;
			
__LEAVE_FUNCTION
}

BOOL PacketFactoryManager::Init( )
{
__ENTER_FUNCTION

	AddFactory( new PacketFactory<CTransformPack_REQ, E_MOVE_REQ>(CTransformPack_REQ_Handle::Execute) ) ;
	AddFactory( new PacketFactory<CTransformPack_NTF, E_MOVE_NTF>() ) ;
	AddFactory( new PacketFactory<CTransformEndPack_REQ, E_MOVE_END_REQ>(CTransformEndPack_REQ_Handle::Execute) ) ;
	AddFactory( new PacketFactory<CReCreate_REQ, E_RECREATE_REQ>() ) ;
	AddFactory( new PacketFactory<CActionPack_REQ, E_ACTION_REQ>() ) ;
	AddFactory( new PacketFactory<CActionPack_REV, E_ACTION_REV>() ) ;
	AddFactory( new PacketFactory<CStatusPack_NTF, E_STATUS_NTF>() ) ;
	AddFactory( new PacketFactory<CSkillPack_REQ, E_SKILL_REQ>() ) ;
	AddFactory( new PacketFactory<CSkillPack_REV, E_SKILL_REV>() ) ;
	AddFactory( new PacketFactory<CSkillPack_NTF, E_SKILL_NTF>() ) ;
	AddFactory( new PacketFactory<CSkillStatus_NTF, E_SKILLSTUAS_NTF>() ) ;
	AddFactory( new PacketFactory<CCreatePlayer_NTF, E_CREATE_NTF>() ) ;
	AddFactory( new PacketFactory<CCreatePlayer_REV, E_CREATE_REV>() ) ;
	AddFactory( new PacketFactory<CRemovePlayer_NTF, E_REMOVE_NTF>() ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID PacketFactoryManager::AddFactory( IPacketFactory* pFactory ) 
{
__ENTER_FUNCTION
		
	if( m_Factories[pFactory->GetPacketID()]!=NULL ) 
	{//ÖØ¸´Éè¶¨
		Assert( FALSE ) ;
		return ;
	}
	
	m_Factories[pFactory->GetPacketID()] = pFactory ;
			
__LEAVE_FUNCTION
}

IPacketFactory* PacketFactoryManager::GetFactory( PacketID_t packetID )
{
__ENTER_FUNCTION

	if( packetID>=m_Size || m_Factories[packetID]==NULL ) 
	{
		Assert(FALSE) ;
		return NULL ;
	}

	return m_Factories[packetID];

__LEAVE_FUNCTION

	return NULL;
}

CBasePack* PacketFactoryManager::CreatePacket( PacketID_t packetID ) 
{
__ENTER_FUNCTION

	if( packetID>=m_Size || m_Factories[packetID]==NULL ) 
	{
		Assert(FALSE) ;
		return NULL ;
	}

	CBasePack* pPacket = NULL ;
	Lock() ;
	_MY_TRY
	{
		pPacket = m_Factories[packetID]->CreatePacket();
		m_pPacketAllocCount[packetID]++ ;
	}
	_MY_CATCH
	{
		pPacket = NULL ;
	}
	Unlock() ;

	return pPacket ;
			
__LEAVE_FUNCTION

	return NULL ;
}

VOID PacketFactoryManager::RemovePacket( CBasePack* pPacket )
{
__ENTER_FUNCTION

	if( pPacket==NULL )
	{
		Assert(FALSE) ;
		return ;
	}

	PacketID_t packetID = pPacket->uID ;
	if( packetID>=m_Size ) 
	{
		Assert(FALSE) ;
		return ;
	}

	Lock() ;
	_MY_TRY
	{
		SAFE_DELETE( pPacket ) ;
		m_pPacketAllocCount[packetID] -- ;
	}
	_MY_CATCH
	{
	}
	Unlock() ;
	return ;

__LEAVE_FUNCTION

	return ;
}

