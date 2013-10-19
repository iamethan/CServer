//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_MOVE_H__
#define __PACKETDEFINE_MOVE_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 坐标信息包 请求
class CS_PlayerMove_REQ: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fTargetX;    // 目标坐标
		float fTargetY;    // 目标坐标
		float fTargetZ;    // 目标坐标
		unsigned int uObjectID;    // 自己的ID
		MSGPACK_DEFINE(fTargetX, fTargetY, fTargetZ, uObjectID);
	};


	PacketBody stBody;    // 包体
};

    // 坐标信息包 广播
class SC_PlayerMove_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fTargetX;    // 目标坐标
		float fTargetY;    // 目标坐标
		float fTargetZ;    // 目标坐标
		unsigned int uObjectID;    // 坐标变换物体的ID
		MSGPACK_DEFINE(fTargetX, fTargetY, fTargetZ, uObjectID);
	};


	PacketBody stBody;    // 包体
};

    // 行为移动请求包
class CS_PlayerMoveEnd_REQ: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fCurrentX;    // 当前坐标
		float fCurrentY;    // 当前坐标
		float fCurrentZ;    // 当前坐标
		unsigned int uObjectID;    // 动作作用于物体的ID
		MSGPACK_DEFINE(fCurrentX, fCurrentY, fCurrentZ, uObjectID);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif