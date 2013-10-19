//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __ENUMCONFIG_H__
#define __ENUMCONFIG_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

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

enum ETargetType
{
	E_NONE_TARGET = 0,    // 没有固定目标
	E_SELF = 1,    // 自己
	E_FRIEND = 2,    // 友军
	E_ENEMY = 3,    // 敌军
};

#pragma pack(pop)

#endif