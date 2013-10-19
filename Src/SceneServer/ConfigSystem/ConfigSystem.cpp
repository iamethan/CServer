
#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "ConfigSystem.h"
#include "PlayerSystem/PlayerSystem.h"
#include "SkillSystem/SkillSystem.h"
#include "Define/PrestrainFile/BirthPlace.h"
#include "Define/PrestrainFile/PlayerProperty.h"
#include "Define/PrestrainFile/Skill.h"

CBirthPlace** PlayerSystem::cBirthPlace  =NULL;
CPlayerProperty** PlayerSystem::cPlayerProperty  =NULL;
CSkill** SkillSystem::cSkill = NULL;
CSkillFight** SkillSystem::cSkillFight = NULL;
CSkillFightEvent** SkillSystem::cSkillFightEvent = NULL;

ConfigSystem::ConfigSystem()
{
}

ConfigSystem::~ConfigSystem()
{
}

BOOL ConfigSystem::Initialize()
{
	LoadData();
	return TRUE;
}

void ConfigSystem::LoadData()
{
	ReadFile();
}

//预加载 基本信息 （地图，人物，技能）
void ConfigSystem::ReadFile()
{
	char path[128] = {0};
	strcpy(path,"../Config/PrestrainFile/");
	strcat(path,"birthplace.bin");
	PerstrainFile<CBirthPlace>(PlayerSystem::cBirthPlace , path);

	memset(path,0,sizeof(path));
	strcpy(path,"../Config/PrestrainFile/");
	strcat(path,"playerproperty.bin");
	PerstrainFile<CPlayerProperty>(PlayerSystem::cPlayerProperty , path);

	memset(path,0,sizeof(path));
	strcpy(path,"../Config/PrestrainFile/");
	strcat(path,"skill.bin");
	PerstrainFile<CSkill>(SkillSystem::cSkill , path);

	memset(path,0,sizeof(path));
	strcpy(path,"../Config/PrestrainFile/");
	strcat(path,"skillFight.bin");
	PerstrainFile<CSkillFight>(SkillSystem::cSkillFight , path);

	memset(path,0,sizeof(path));
	strcpy(path,"../Config/PrestrainFile/");
	strcat(path,"skillFightEvent.bin");
	PerstrainFile<CSkillFightEvent>(SkillSystem::cSkillFightEvent , path);
}

