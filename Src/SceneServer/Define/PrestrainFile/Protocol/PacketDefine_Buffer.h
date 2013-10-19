//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_BUFFER_H__
#define __PACKETDEFINE_BUFFER_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 解除 玩家buff 广播
class SC_RelieveBuff_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned short uSkillID;    // 技能ID 
		unsigned int uObjectID;    // Object的ID
		MSGPACK_DEFINE(uSkillID, uObjectID);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif