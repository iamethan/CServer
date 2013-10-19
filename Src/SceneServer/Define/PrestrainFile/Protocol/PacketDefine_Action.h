//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_ACTION_H__
#define __PACKETDEFINE_ACTION_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 行为动作请求包
class CS_Action_REQ: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned int uObjectID;    // 动作作用于物体的ID
		unsigned char uActionID;    // 动作ID 
		MSGPACK_DEFINE(uObjectID, uActionID);
	};


	PacketBody stBody;    // 包体
};

    // 行为动作包 是否成功  发送给自己
class SC_Action_REV: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned short uResult;    // 是否成功
		MSGPACK_DEFINE(uResult);
	};


	PacketBody stBody;    // 包体
};

    // 行为动作包（更新状态、血、蓝等） 广播
class SC_Action_NTF: public BasePacket
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