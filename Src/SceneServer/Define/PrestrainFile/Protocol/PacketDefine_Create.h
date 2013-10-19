//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_CREATE_H__
#define __PACKETDEFINE_CREATE_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

    // 复活请求包
class CS_ReCreate_REQ: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		unsigned int uObjectID;    // 玩家ID
		MSGPACK_DEFINE(uObjectID);
	};


	PacketBody stBody;    // 包体
};

    // 创建他人
class SC_Create_NTF: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fPosX;    // 玩家坐标X
		float fPosY;    // 玩家坐标Y
		float fPosZ;    // 玩家坐标Z
		unsigned int uObjectID;    // Object的ID
		std::string strPlayerName;    // 人物名字
		unsigned int uHP;    // object的血
		unsigned int uMP;    // object的魔
		unsigned char uTeamID;    // object所属正营
		unsigned char uProfession;    // object的职业
		MSGPACK_DEFINE(fPosX, fPosY, fPosZ, uObjectID, strPlayerName, uHP, uMP, uTeamID, uProfession);
	};


	PacketBody stBody;    // 包体
};

    // 创建请求
class CS_Create_REQ: public BasePacket
{
public:
    // 包体
	struct CPackBody
	{
		unsigned char uTeamID;    // object所属正营
		unsigned char uProfession;    // object的职业
		MSGPACK_DEFINE(uTeamID, uProfession);
	};


	CPackBody stBody;    // 包体
};

    // 创建自己
class SC_Create_REV: public BasePacket
{
public:
    // 包体
	struct PacketBody
	{
		float fPosX;    // 玩家坐标X
		float fPosY;    // 玩家坐标Y
		float fPosZ;    // 玩家坐标Z
		unsigned int uObjectID;    // Object的ID
		std::string strPlayerName;    // 人物名字
		unsigned int uHP;    // object的血
		unsigned int uMP;    // object的魔
		unsigned char uTeamID;    // object所属正营
		unsigned char uProfession;    // object的职业
		MSGPACK_DEFINE(fPosX, fPosY, fPosZ, uObjectID, strPlayerName, uHP, uMP, uTeamID, uProfession);
	};


	PacketBody stBody;    // 包体
};

#pragma pack(pop)

#endif