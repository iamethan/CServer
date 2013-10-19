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

    // 玩家属性
struct CPlayerProperty
{
	unsigned int uHP;    // 血量
	unsigned int uMP;    // 魔力
	unsigned int uReliveAddHP;    // 复活增加血量
	unsigned int uReliveAddMP;    // 复活增加蓝量
};

#pragma pack(pop)