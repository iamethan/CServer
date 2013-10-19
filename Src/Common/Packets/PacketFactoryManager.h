#ifndef __PACKET_FACTORY_MANAGER_H__
#define __PACKET_FACTORY_MANAGER_H__

#include "Base/Type.h"
#include "Net/Packet.h"

#define PACKET_ID_MAX 65535

class PacketFactoryManager 
{
public :
	
	PacketFactoryManager( ) ;
	
	~PacketFactoryManager( ) ;

private :
	VOID				AddFactory( IPacketFactory* pFactory ) ;
	
public :
	//外部调用通用接口

	//初始化接口
	BOOL				Init( ) ;

	IPacketFactory*		GetFactory( PacketID_t packetID );

	//根据消息类型从内存里分配消息实体数据（允许多线程同时调用）
	CBasePack*			CreatePacket( PacketID_t packetID ) ;

	//删除消息实体（允许多线程同时调用）
	VOID				RemovePacket( CBasePack* pPacket ) ;

	VOID				Lock( ){ m_Lock.Lock() ; } ;
	VOID				Unlock( ){ m_Lock.Unlock() ; } ;

private :
	
	IPacketFactory **	m_Factories ;
	
	USHORT				m_Size ;

	MyLock				m_Lock ;

public :
	UINT*				m_pPacketAllocCount ;

};

extern PacketFactoryManager* g_pPacketFactoryManager ;

#endif // __PACKET_FACTORY_MANAGER_H__
