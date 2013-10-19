//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_CLOSECONNECT_H__
#define __PACKETDEFINE_CLOSECONNECT_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 删除玩家
class SC_RemovePlayer_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned int uObjectID;    // Object的ID
		MSGPACK_DEFINE(uObjectID);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif