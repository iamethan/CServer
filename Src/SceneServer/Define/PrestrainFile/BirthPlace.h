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
struct CBirthPlace
{
	unsigned char uTeamID;    // 队伍编号
	unsigned short uPosX;    // 坐标X
	unsigned short uPosZ;    // 坐标Z
};

#pragma pack(pop)