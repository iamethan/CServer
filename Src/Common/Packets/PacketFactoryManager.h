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
	//�ⲿ����ͨ�ýӿ�

	//��ʼ���ӿ�
	BOOL				Init( ) ;

	IPacketFactory*		GetFactory( PacketID_t packetID );

	//������Ϣ���ʹ��ڴ��������Ϣʵ�����ݣ�������߳�ͬʱ���ã�
	CBasePack*			CreatePacket( PacketID_t packetID ) ;

	//ɾ����Ϣʵ�壨������߳�ͬʱ���ã�
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
