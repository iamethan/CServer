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

	// ��ʼ��
	BOOL		Initialize( VOID );

	// ���մ���
	BOOL		Finalize( VOID );

	// ��������
	VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	///////////////////////////////////////////////////////////////////
	// ���ܺ���
	BOOL	UseSkill( ObjID_t nObjID, SkillID_t nSkillID );

	///////////////////////////////////////////////////////////////////
	// ��Ϣ���
protected:
	DECLARE_PACKET_HANDLE_BEGIN( SkillSystem );
		
	DECLARE_PACKET_HANDLE_END();

	///////////////////////////////////////////////////////////////////
	// �¼����
protected:
	DECLARE_EVENT_HANDLE_BEGIN( SkillSystem )
		
	DECLARE_EVENT_HANDLE_END()
};

#endif // __SKILL_SYSTEM_H__