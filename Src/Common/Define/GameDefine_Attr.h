#ifndef __GAMEDEFINE_ATTR_H__
#define __GAMEDEFINE_ATTR_H__
#include "GameDefine.h"
#include "Base/Type.h"

//��ɫ��������(һ������)
enum CHAR_ATTR_LEVEL1
{
	CATTR_LEVEL1_STR			=0, //���� ����	[[����]]
	CATTR_LEVEL1_CON			=1,	//���� ����	[[����]]
	CATTR_LEVEL1_INT			=2,	//���� ����	[[����]]
	CATTR_LEVEL1_DEX			=3,	//�� ����	[[��]]

	CATTR_LEVEL1_NUMBER, //��ɫ������������
};

enum CHAR_ATTR_LEVEL
{
	CATTR_LEVEL_STR			=0, //���� ����
	CATTR_LEVEL_CON			=1,	//���� ����
	CATTR_LEVEL_INT			=2,	//���� ����
	CATTR_LEVEL_DEX			=3,	//�� ����
	CATTR_LEVEL_SKILL		,
	CATTR_LEVEL_NUMBER, //��ɫ������������
};


//����: һЩ��ɫ���Ե����ֵ
enum CHAR_ATTR_CONSTANT1
{
	MAX_STRIKE_POINT = 9,
	BASE_MAX_STRIKE_POINT = 6,
	BASE_MAX_RAGE = 1000,
	MAX_RAGE = 1500,
	BASE_ATTACK_SPEED = 100,
	BASE_VISION_RANGE = 16,
	MAX_EXP_REFIX_IN_CHAR = 400,
	MAX_EXP_REFIX_IN_SYSTEM = 400,
	MAX_COOLDOWN_LIST_SIZE_FOR_HUMAN = 32,
	MAX_COOLDOWN_LIST_SIZE_FOR_PET = 8,
};
//����: һЩ��ɫ���Ե����ֵ
enum CHAR_ATTR_CONSTANT2
{
	MAX_EFFECTIVE_RESIST = 100,
	LL_GENERAL_ATTACK_DEFENCE = 0,
	LL_TRAIT_ATTACK = 0,
	LL_RESIST = 0,
	UL_RESIST = 100,
};
enum CHAR_ATTR_CONSTANT3
{
	LL_CRITICAL = 0,
	LL_HIT_MISS = 0,
	UL_CRITICAL = 100,
	UL_HIT_MISS = 1000,
};
//���ߺ�����У�����Ե���Чֵ
inline INT Attr_VerifyGeneralAttack(INT nAttr)
{
	if(LL_GENERAL_ATTACK_DEFENCE>nAttr)
	{
		nAttr = LL_GENERAL_ATTACK_DEFENCE;
	}
	return nAttr;
}

inline INT Attr_VerifyTraitAttack(INT nAttr)
{
	if(LL_TRAIT_ATTACK>nAttr)
	{
		nAttr = LL_TRAIT_ATTACK;
	}
	return nAttr;
}
inline INT Attr_VerifyDefence(INT nAttr)
{
	if(LL_GENERAL_ATTACK_DEFENCE>nAttr)
	{
		nAttr = LL_GENERAL_ATTACK_DEFENCE;
	}
	return nAttr;
}
inline INT Attr_VerifyResist(INT nAttr)
{
	if(LL_RESIST>nAttr)
	{
		nAttr = LL_RESIST;
	}
	if(UL_RESIST<nAttr)
	{
		nAttr = UL_RESIST;
	}
	return nAttr;
}

inline INT Attr_VerifyToughness(INT nAttr)
{
	return nAttr;
}

inline INT Attr_VerifyHitMiss(INT nAttr)
{
	if(LL_HIT_MISS>nAttr)
	{
		nAttr = LL_HIT_MISS;
	}
	if(UL_HIT_MISS<nAttr)
	{
		nAttr = UL_HIT_MISS;
	}
	return nAttr;
}

inline INT Attr_VerifyCritical(INT nAttr)
{
	if(LL_CRITICAL>nAttr)
	{
		nAttr = LL_CRITICAL;
	}
	if(UL_CRITICAL<nAttr)
	{
		nAttr = UL_CRITICAL;
	}
	return nAttr;
}

#endif
