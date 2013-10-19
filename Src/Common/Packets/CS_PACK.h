//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <vector>
#include "Net/MsgPack/msgpack.hpp"

#pragma pack(push)
#pragma pack(1)

const float g_fWalkStep = 1.5f;

const float g_fAngleStep = 22.5f;

const float g_fSafeRang = 3.0f;

enum EMessageID
{
	E_MOVE_REQ = 0,
	E_MOVE_NTF,
	E_MOVE_END_REQ,
	E_ACTION_REQ,
	E_ACTION_REV,
	E_STATUS_NTF,
	E_CREATE_REV,
	E_CREATE_NTF,
	E_REMOVE_NTF,
	E_SKILL_REQ,
	E_SKILL_REV,
	E_SKILL_NTF,
	E_SKILLSTUAS_NTF,
	E_RECREATE_REQ,
	E_MESSAGE_COUNT,
};

enum EError
{
	E_NONE_ERROR = 0,
	E_ERROR = 1,
};

enum EProfession
{
	E_WARRIOR = 0,    // 战士
	E_ARCHER,    // 弓箭手
	E_WIZARD,    // 巫师
};

enum EAction
{
	E_IDLE = 0,    // 待机
	E_MOVE = 1,    // 移动
	E_ATTACK = 2,    // 攻击
	E_BLOCK = 3,    // 格挡
	E_HURT = 4,    // 受伤
	E_DEAD = 5,    // 死亡
	E_SKILL = 6,    // 释放技能
};

enum EBufState
{
	E_FROZEN = 1,    // 冰冻效果 期间不能移动
};

enum ESkillType
{
	E_HARM = 1,    // 伤害技
	E_BUFF = 2,    // buff技
	E_TREATMENT = 3,    // 治疗技
	E_DISPLACEMENT = 4,    // 位移技
};

const unsigned char g_uPackHeadSize = 4;

    // 坐标信息包 请求
class CTransformPack_REQ: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		float fTargetX;    // 目标坐标
		float fTargetY;    // 目标坐标
		float fTargetZ;    // 目标坐标
		unsigned int uObjectID;    // 自己的ID
		MSGPACK_DEFINE(fTargetX, fTargetY, fTargetZ, uObjectID);
	};


	CPackBody stBody;    // 包体
};

    // 坐标信息包 广播
class CTransformPack_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		float fTargetX;    // 目标坐标
		float fTargetY;    // 目标坐标
		float fTargetZ;    // 目标坐标
		unsigned int uObjectID;    // 坐标变换物体的ID
		MSGPACK_DEFINE(fTargetX, fTargetY, fTargetZ, uObjectID);
	};


	CPackBody stBody;    // 包体
};

    // 行为动作请求包
class CTransformEndPack_REQ: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		float fCurrentX;    // 当前坐标
		float fCurrentY;    // 当前坐标
		float fCurrentZ;    // 当前坐标
		unsigned int uObjectID;    // 动作作用于物体的ID
		MSGPACK_DEFINE(fCurrentX, fCurrentY, fCurrentZ, uObjectID);
	};


	CPackBody stBody;    // 包体
};

    // 复活请求包
class CReCreate_REQ: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned int uObjectID;    // 玩家ID
		MSGPACK_DEFINE(uObjectID);
	};


	CPackBody stBody;    // 包体
};

    // 行为动作请求包
class CActionPack_REQ: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned int uObjectID;    // 动作作用于物体的ID
		unsigned char uActionID;    // 动作ID 
		MSGPACK_DEFINE(uObjectID, uActionID);
	};


	CPackBody stBody;    // 包体
};

    // 行为动作包 是否成功  发送给自己
class CActionPack_REV: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned short uResult;    // 是否成功
		MSGPACK_DEFINE(uResult);
	};


	CPackBody stBody;    // 包体
};

    // 行为动作包（更新状态、血、蓝等） 广播
class CStatusPack_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned int uObjectID;    // Object的ID
		unsigned char uActionID;    // 动作ID 
		unsigned int uHP;    // object的血
		unsigned int uMP;    // object的魔
		MSGPACK_DEFINE(uObjectID, uActionID, uHP, uMP);
	};


	CPackBody stBody;    // 包体
};

    // 技能释放请求包
class CSkillPack_REQ: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned char cDirection;    // 技能释放方向
		unsigned short uSkillID;    // 技能ID 
		MSGPACK_DEFINE(cDirection, uSkillID);
	};


	CPackBody stBody;    // 包体
};

    // 技能释放 （判断是否释放成功）发给自己
class CSkillPack_REV: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		float fDirX;    // 技能起始坐标x
		float fDirY;    // 技能起始坐标y
		float fDirZ;    // 技能起始坐标z
		unsigned short uResult;    // 是否成功
		unsigned short uSkillID;    // 技能ID 
		unsigned short uSkillObjID;    // 技能唯一ID 
		MSGPACK_DEFINE(fDirX, fDirY, fDirZ, uResult, uSkillID, uSkillObjID);
	};


	CPackBody stBody;    // 包体
};

    // 技能释放 （释放成功时）广播
class CSkillPack_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		float fDirX;    // 技能起始坐标x
		float fDirY;    // 技能起始坐标y
		float fDirZ;    // 技能起始坐标z
		unsigned char cDirection;    // 技能释放方向
		unsigned short uSkillID;    // 技能ID 
		unsigned short uSkillObjID;    // 技能唯一ID 
		MSGPACK_DEFINE(fDirX, fDirY, fDirZ, cDirection, uSkillID, uSkillObjID);
	};


	CPackBody stBody;    // 包体
};

    // 技能释放结束 状态  广播
class CSkillStatus_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
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


	CPackBody stBody;    // 包体
};

    // 解除 玩家buff 广播
class CRelieveBuff_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned short uSkillID;    // 技能ID 
		unsigned int uObjectID;    // Object的ID
		MSGPACK_DEFINE(uSkillID, uObjectID);
	};


	CPackBody stBody;    // 包体
};

    // 创建他人
class CCreatePlayer_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
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


	CPackBody stBody;    // 包体
};

    // 创建自己
class CCreatePlayer_REV: public CBasePack
{
public:
    // 包体
	struct CPackBody
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


	CPackBody stBody;    // 包体
};

    // 删除玩家
class CRemovePlayer_NTF: public CBasePack
{
public:
    // 包体
	struct CPackBody
	{
		unsigned int uObjectID;    // Object的ID
		MSGPACK_DEFINE(uObjectID);
	};


	CPackBody stBody;    // 包体
};

#pragma pack(pop)