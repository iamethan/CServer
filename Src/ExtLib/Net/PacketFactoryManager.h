#ifndef __PACKET_FACTORY_MANAGER_H__
#define __PACKET_FACTORY_MANAGER_H__

#include "Utility.h"
#include "Packet.h"
#include <map>

#define MAX_HANDLE_PER_PACKET_SIZE	16

class PacketFactoryManager 
{
	// packet struct
	struct PACKET_FACTORY 
	{
		IPacketFactory*	m_pFactory;			// factory ptr
		UINT			m_nPacketCount;		// allocated packets count
	};
	typedef std::map< PacketID_t, PACKET_FACTORY* >	PacketFactoryMap;

public :
	
	PacketFactoryManager( ) ;
	~PacketFactoryManager( ) ;

public :
	IPacketFactory*		GetFactory( PacketID_t packetID );

	// 消息包
	BasePacket*			CreatePacket( PacketID_t packetID ) ;
	VOID				RemovePacket( BasePacket* pPacket ) ;

	// 消息处理
	BOOL				HandlePacket( BasePacket* pPacket, Stub* pStub );

	BOOL				RegistePacketHandle( PacketID_t nPacketID, IPacketListener* pListener, IPacketFactory::FuncAddr pHandleFunc );

	// 消息工厂
	BOOL				AddFactory( IPacketFactory* pFactory ) ;
	BOOL				FindFactory( PacketID_t nPacketID );

	UINT				GetCount( ) { return m_mapFactories.size();	}

protected:
	PACKET_FACTORY*		GetFactoryStruct( PacketID_t nPacketID );

private :
	// packet factories
	PacketFactoryMap		m_mapFactories;
};

extern PacketFactoryManager	g_PacketFactoryManager;

#define DECLARE_PACKET(PACKET, PID)	\
	g_PacketFactoryManager.AddFactory( new PacketFactory<PACKET, PID> );

//////////////////////////////////////////////////////
// 消息处理
#define DECLARE_PACKET_HANDLE_BEGIN( CLASS ) \
	typedef BOOL (CLASS::*__PACKET_HANDLE) ( BasePacket* pPacket, Stub* pStub );	\
	typedef CLASS	__THIS_CLASS__;  \
	BOOL __HandlePacket( BasePacket* pPacket, Stub* pStub, IEvent::FuncAddr pFunc )	\
	{	\
		__PACKET_HANDLE pCallBack = *((__PACKET_HANDLE*)&pFunc);	\
		return (this->*pCallBack)( pPacket, pStub );		\
	}	\
	VOID __InitPacketHandles( ) {

#define DECLARE_PACKET_HANDLE_END()	}

#define PACKET_HANDLE( PID, HANDLEFUNC )	{	\
	__PACKET_HANDLE func = &__THIS_CLASS__::HANDLEFUNC;	\
	IPacketFactory::FuncAddr pFunc = *((IPacketFactory::FuncAddr*)(&func));	\
	g_PacketFactoryManager.RegistePacketHandle(PID, this, pFunc); }

#endif // __PACKET_FACTORY_MANAGER_H__
