//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <vector>
#include "Net.h"

#pragma pack(push)
#pragma pack(1)

    // 技能属性
struct CSkill
{
	unsigned short uID;    // 技能ID
	char strName[16];    // 技能名字
	unsigned char uAttackType;    // 攻击类型
	unsigned char uAttackTarget;    // 目标个数
	unsigned char uAttackRadius;    // 攻击半径
	unsigned short uAttackRange;    // 范围度数
	unsigned char uRange;    // 射程
	float fSpeed;    // 速度
	unsigned short uChantTime;    // 吟唱时间
	unsigned short uLeadTime;    // 引导时间
	unsigned short uCDTime;    // CD时间
	unsigned char uIsChantBreak;    // 吟唱打断
	unsigned short uBeforeChantEventID;    // 吟唱前事件ID
	unsigned short uAfterChantEventID;    // 吟唱后事件ID
	unsigned char uIsLeadBreak;    // 引导打断
	unsigned short uBeforeLeadEventID;    // 引导前事件ID
	unsigned short uAfterLeadEventID;    // 引导后事件ID
	unsigned short uBeforeHitEventID;    // 命中前事件ID
	unsigned short uAfterHitEventID;    // 命中后事件ID
	unsigned short uFightID;    // 战斗表ID
};

    // 战斗属性
struct CSkillFight
{
	unsigned short uID;    // 战斗ID
	unsigned short uFightType;    // 战斗类型
	unsigned short uFightEffect;    // 基础效果
};

    // 战斗事件
struct CSkillFightEvent
{
	unsigned short uID;    // 战斗事件ID
	unsigned short uEventType;    // 战斗事件类型
	char strParm[64];    // 参数
	char strDesc[64];    // 描述
};

#pragma pack(pop)