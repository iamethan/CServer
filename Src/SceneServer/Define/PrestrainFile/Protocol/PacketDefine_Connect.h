//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_CONNECT_H__
#define __PACKETDEFINE_CONNECT_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 玩家连接状态（是否成功）
class SC_ConnectStatus_REV: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned char uStatus;    // 连接是否成功
		MSGPACK_DEFINE(uStatus);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif