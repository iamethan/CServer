#ifndef __SKILL_SYSTEM_H__
#define __SKILL_SYSTEM_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "Define/SystemDefine.h"

class SkillSystem : public GSystem
{
public:
	SkillSystem();
	virtual ~SkillSystem();

	const CHAR*	SystemName( VOID )	{ return "PlayerSystem";	}
	const INT	SystemID( VOID )	{ return SYSTEM_ID_SKILL_SYSTEM;	}

	// 初始化
	BOOL		Initialize( VOID );

	// 回收处理
	BOOL		Finalize( VOID );

	// 心跳函数
	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	///////////////////////////////////////////////////////////////////
	// 功能函数
	BOOL	UseSkill( ObjID_t nObjID, SkillID_t nSkillID );

	///////////////////////////////////////////////////////////////////
	// 消息相关
protected:
	DECLARE_PACKET_HANDLE_BEGIN( SkillSystem );
		
	DECLARE_PACKET_HANDLE_END();

	///////////////////////////////////////////////////////////////////
	// 事件相关
protected:
	DECLARE_EVENT_HANDLE_BEGIN( SkillSystem )
		
	DECLARE_EVENT_HANDLE_END()
};

#endif // __SKILL_SYSTEM_H__