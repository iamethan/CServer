//////////////////////////////////////////////////////////////////////////
// This head file defines the bin data structure.
// It's created automatically. Don't change the file manually!
//////////////////////////////////////////////////////////////////////////
#ifndef __PACKETDEFINE_H__
#define __PACKETDEFINE_H__

#include <string>
#include <vector>
#include "Net.h"
//#include "Define/PrestrainFile/Protocol/PacketDefine.h"

#pragma pack(push)
#pragma pack(1)

enum PacketMessageID
{
	PID_SC_ConnectStatus_REV = 0,
	PID_CS_ReCreate_REQ,
	PID_SC_Create_NTF,
	PID_CS_Create_REQ,
	PID_SC_Create_REV,
	PID_CS_Action_REQ,
	PID_SC_Action_REV,
	PID_SC_Action_NTF,
	PID_CS_SkillStart_REQ,
	PID_SC_SkillStatus_REV,
	PID_SC_SkillStatus_NTF,
	PID_SC_SkillEnd_NTF,
	PID_SC_PlayerStatus_NTF,
	PID_CS_PlayerMove_REQ,
	PID_SC_PlayerMove_NTF,
	PID_CS_PlayerMoveEnd_REQ,
	PID_SC_RelieveBuff_NTF,
	PID_SC_RemovePlayer_NTF,
	PID_MSG_COUNT,
};

 

#pragma pack(pop)

#endif