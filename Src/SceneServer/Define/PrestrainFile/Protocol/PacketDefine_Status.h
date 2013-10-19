//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_STATUS_H__
#define __PACKETDEFINE_STATUS_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 行为动作包（更新状态、血、蓝等） 广播
class SC_PlayerStatus_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned int uObjectID;    // Object的ID
		unsigned char uActionID;    // 动作ID 
		unsigned int uHP;    // object的血
		unsigned int uMP;    // object的魔
		MSGPACK_DEFINE(uObjectID, uActionID, uHP, uMP);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif