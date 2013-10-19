//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __BASECONFIG_H__
#define __BASECONFIG_H__

#include <string>
#include <vector>
#include "Net.h"
#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

const float fWalkStep = 1.5f;

const float fAngleStep = 22.5f;

const float fSafeRang = 3.0f;

const unsigned char g_uPackHeadSize = 4;

#pragma pack(pop)

#endif