//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_SKILL_H__
#define __PACKETDEFINE_SKILL_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 技能释放请求包
class CS_SkillStart_REQ: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned int uObjectID;    // 技能释放对象
		unsigned short uSkillID;    // 技能ID 
		MSGPACK_DEFINE(uObjectID, uSkillID);
	};


	PacketBody stBody;    // 包体
};

    // 技能释放 （判断是否释放成功）发给自己
class SC_SkillStatus_REV: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fDirX;    // 技能起始坐标x
		float fDirY;    // 技能起始坐标y
		float fDirZ;    // 技能起始坐标z
		unsigned short uResult;    // 是否成功
		unsigned short uSkillID;    // 技能ID 
		unsigned short uSkillObjID;    // 技能唯一ID 
		MSGPACK_DEFINE(fDirX, fDirY, fDirZ, uResult, uSkillID, uSkillObjID);
	};


	PacketBody stBody;    // 包体
};

    // 技能释放 （释放成功时）广播
class SC_SkillStatus_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fDirX;    // 技能起始坐标x
		float fDirY;    // 技能起始坐标y
		float fDirZ;    // 技能起始坐标z
		unsigned char cDirection;    // 技能释放方向
		unsigned short uSkillID;    // 技能ID 
		unsigned short uSkillObjID;    // 技能唯一ID 
		MSGPACK_DEFINE(fDirX, fDirY, fDirZ, cDirection, uSkillID, uSkillObjID);
	};


	PacketBody stBody;    // 包体
};

    // 技能释放结束 状态  广播
class SC_SkillEnd_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fDirX;    // 技能释放结束 技能坐标x
		float fDirY;    // 技能释放结束 技能坐标y
		float fDirZ;    // 技能释放结束 技能坐标z
		unsigned short uSkillID;    // 技能ID 
		unsigned short uSkillObjID;    // 技能的唯一id
		unsigned int uObjectID;    // Object的ID
		unsigned char uActionID;    // 动作ID 
		unsigned int uHP;    // object的血
		unsigned int uMP;    // object的魔
		MSGPACK_DEFINE(fDirX, fDirY, fDirZ, uSkillID, uSkillObjID, uObjectID, uActionID, uHP, uMP);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif