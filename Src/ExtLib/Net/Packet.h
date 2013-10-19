#ifndef __PACKET_H__
#define __PACKET_H__

#include "Utility.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "MsgPack/msgpack.h"
#include "MsgPack/msgpack.hpp"
#include <list>

class Socket;
class Stub;
class PacketFactoryManager;

#define GET_PACKET_ID(a) ((a)>>16)
#define SET_PACKET_ID(a, index) (((a)&0xffff)+((index)<<16))
#define GET_PACKET_LEN(a) ((a)&0xffff)
#define SET_PACKET_LEN(a, len) ((a)=((a)&0xff00)+(len))

#define PACKET_HEADER_SIZE (sizeof(PacketID_t)+sizeof(PacketLen_t))

// 定义包头
class BasePacket
{
public:
	unsigned short uID;    // 数据包类型
	unsigned short uBodyLen;    // 测试用
};


class IPacketListener;

class IPacketFactory
{
public:
	typedef int	FuncAddr;

private:
	friend class PacketFactoryManager;

	struct Handle
	{
		IPacketListener*	m_pListener;
		FuncAddr			m_pFuncHandle;
	};
	typedef std::list< Handle* >	HandleList;

public:
	virtual PacketID_t	GetPacketID() = 0;

	virtual BOOL		Read(BasePacket* pPacket, SocketInputStream& iStream) = 0;
	virtual BOOL		Write(BasePacket* pPacket, SocketOutputStream& oStream) = 0;

protected:
	virtual BasePacket*	CreatePacket() = 0;
	virtual BOOL		RegisterHandle( IPacketListener* pListener, FuncAddr pFuncHandle );

private:
	HandleList	m_lstHandles;
};

class IPacketListener
{
	friend class PacketFactoryManager;
public:
	virtual const CHAR*	SystemName( VOID )	= 0;

protected:
	virtual BOOL	__HandlePacket( BasePacket* pPacket, Stub* pStub, IPacketFactory::FuncAddr pFunc ) { return TRUE;	}
	virtual VOID	__InitPacketHandles( ) {}
};

template< class T, PacketID_t PID >
class PacketFactory : public IPacketFactory
{
	friend class PacketFactoryManager;

public:
	PacketFactory() {}

	PacketID_t GetPacketID() { return PID; }

	virtual BOOL Read(BasePacket* pPacket, SocketInputStream& iStream)
	{
	__ENTER_FUNCTION_FOXNET

		T* pNetPacket = static_cast<T*>(pPacket);
		if( !pNetPacket )
			return FALSE;

		BOOL ret = FALSE;

		const PacketLen_t len = pNetPacket->uBodyLen;
		ret = iStream.Skip( PACKET_HEADER_SIZE );
		if( !ret )
			return FALSE;

		if( len > iStream.Length() )
			return FALSE;

		const CHAR* buff = iStream.GetHeadBuffer();
		if( !buff )
			return FALSE;

		_MY_TRY {
			msgpack::unpacked msg;
			msgpack::unpack(&msg, buff, len);
			msgpack::object obj = msg.get();
			obj.convert( &(pNetPacket->stBody) );
		} _MY_CATCH {
			return FALSE;
		}

		ret = iStream.Skip( len );
		if( !ret )
			return FALSE;

		return TRUE;

	__LEAVE_FUNCTION_FOXNET

		return FALSE;
	}

	BOOL Write(BasePacket* pPacket, SocketOutputStream& oStream)
	{
	__ENTER_FUNCTION_FOXNET

		T* pNetPacket = static_cast<T*>(pPacket);
		if( !pNetPacket )
			return FALSE;

		msgpack::sbuffer body;
		msgpack::pack(&body, pNetPacket->stBody);

		PacketLen_t len = body.size();

		if( len == 0 )
			return FALSE;

		PacketID_t id = pNetPacket->uID;

		UINT retLen = 0;

		retLen = oStream.Write( (CHAR*)&id, sizeof(PacketID_t) );
		if( retLen == 0 )
			return FALSE;

		retLen = oStream.Write( (CHAR*)&len, sizeof(PacketLen_t) );
		if( retLen == 0 )
			return FALSE;

		retLen = oStream.Write( (CHAR*)body.data(), len );
		if( retLen == 0 )
		{
			return FALSE;
		}
		
		return TRUE;

	__LEAVE_FUNCTION_FOXNET

		return FALSE;
	}

protected:
	inline BasePacket* CreatePacket() 
	{
		BasePacket* pPacket = new T; 
		pPacket->uID = PID;

		return pPacket;
	}
};

#endif
