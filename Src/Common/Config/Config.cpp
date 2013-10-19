#include "Config.h"
#include "Base/Type.h"
#include "Base/BaseType.h"
#include "Base/Ini.h"
#include "Log/Log.h"
#include "Define/LogDefine.h"
#include "Define/FileDef.h"
//#include "WXSJ_DBC.h"

//using namespace DBC;
Config g_Config ;

Config::Config( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

Config::~Config( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

BOOL Config::Init( )
{
__ENTER_FUNCTION

	LoadConfigInfo( ) ;
	//LoadServerInfo();
	//LoadSceneInfo();
	
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID Config::ReLoad( )
{
	LoadConfigInfo_ReLoad( ) ;
	LoadServerInfo_ReLoad();
	LoadSceneInfo_ReLoad();
	
}

VOID Config::LoadConfigInfo( )
{
__ENTER_FUNCTION

	LoadConfigInfo_Only( ) ;
	LoadConfigInfo_ReLoad( ) ;

	LoadServerInfo_Only();
	LoadServerInfo_ReLoad();
	
	LoadSceneInfo_Only();
	LoadSceneInfo_ReLoad();

__LEAVE_FUNCTION
}
VOID Config::LoadConfigInfo_Only( )
{//不能被重复读取的数据
__ENTER_FUNCTION

	Ini ini( FILE_CONFIG_INFO ) ;

	INT nValue;

	m_ConfigInfo.m_ServerID = (ID_t)(ini.ReadInt( "System", "ServerID" )) ;

	m_ConfigInfo.m_ZoneSize = ini.ReadInt( "Zone", "ZoneSize" ) ;
	m_ConfigInfo.m_MaxPortal = ini.ReadInt( "Portal", "MaxCount" ) ;
	m_ConfigInfo.m_MaxSkillObj = ini.ReadInt( "SkillObj", "MaxCount" ) ;
	m_ConfigInfo.m_MaxPlatform = ini.ReadInt( "Platform", "MaxCount" );
	m_ConfigInfo.m_MaxSpecial = ini.ReadInt( "SpecialObj", "MaxCount" );
	m_ConfigInfo.m_MaxPlayerShopNum = ini.ReadInt( "PlayerShop", "MaxCount" );
	m_ConfigInfo.m_MaxTimerCount = ini.ReadInt("SceneTimer","MaxCount");
	m_ConfigInfo.m_nMaxHumanUseTimer = ini.ReadInt("HumanTimer","MaxCount");

	m_ConfigInfo.m_nDelateNum           = ini.ReadInt("CountryDelate","DelateNum");
	m_ConfigInfo.m_nVoteNum             = ini.ReadInt("CountryDelate","VoteNum");
	m_ConfigInfo.m_nVoteTime            = ini.ReadInt("CountryDelate","VoteTime");

	if(TRUE==ini.ReadIntIfExist("BusObj", "MaxCount", nValue))
	{
		m_ConfigInfo.m_MaxBus = nValue;
	}
	else
	{
		//AssertEx(FALSE, "[Config::LoadConfigInfo_Only]: INI: read BusObj::MaxCount failed!!");
	}

 	GLog::SaveLog( CONFIG_LOGFILE, "Load ConfigInfo.ini ...Only OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadConfigInfo_ReLoad( )
{//可以重复读取的数据
__ENTER_FUNCTION

	Ini ini( FILE_CONFIG_INFO ) ;
	CHAR	szText[32];

	ini.ReadText( "Global", "DropParam", szText, sizeof( szText ) -1 ) ;
	m_ConfigInfo.m_DropParam = (FLOAT)(atof( szText ));

	ini.ReadText( "Global", "ExpParam", szText, sizeof( szText ) -1 ) ;
	m_ConfigInfo.m_ExpParam = (FLOAT)(atof( szText ));
	m_ConfigInfo.m_EquipmentDamagePoint = ini.ReadInt( "Global", "EquipmentDamagePoint" ) ;
	m_ConfigInfo.m_DropSearchRange = ini.ReadInt( "Global", "DropSearchRange" ) ;
	ini.ReadText( "Global", "DropPosDistance", szText, sizeof( szText ) -1 ) ;
	m_ConfigInfo.m_DropPosDistance = (FLOAT)(atof( szText ));
	m_ConfigInfo.m_LevelupAllocPoints = ini.ReadInt( "Global", "LevelupAllocPoints" ) ;

	m_ConfigInfo.m_RecoverTime = ini.ReadInt( "TimeSetting", "RecoverTime" ) ;
	m_ConfigInfo.m_MaxMonster = ini.ReadInt( "Monster", "MaxCount" ) ;
	m_ConfigInfo.m_MaxPet = ini.ReadInt( "Pet", "MaxCount" ) ;
	m_ConfigInfo.m_PetBodyTime = ini.ReadInt( "Pet", "PetBodyTime" ) ;
	m_ConfigInfo.m_PetHappinessInterval = ini.ReadInt( "Pet", "PetHappinessInterval" );
	m_ConfigInfo.m_nHorseCheckUpSpend = ini.ReadInt( "Pet", "HorseCheckUpSpend" );
	m_ConfigInfo.m_nHorseMattingSpend = ini.ReadInt( "Pet", "HorseMattingSpend" );

	m_ConfigInfo.m_PetLifeInterval = ini.ReadInt( "Pet", "PetLifeInterval" );
	m_ConfigInfo.m_PetCallUpHappiness = ini.ReadInt( "Pet", "PetCallUpHappiness" );
	m_ConfigInfo.m_PetPlacardTime = (uint)(ini.ReadInt( "Pet", "PetPlacardTime" ));
	m_ConfigInfo.m_PetPlacardNeedLevel = ini.ReadInt( "Pet", "PetPlacardNeedLevel" );
	m_ConfigInfo.m_PetPlacardNeedHappiness = ini.ReadInt( "Pet", "PetPlacardNeedHappiness" );
	m_ConfigInfo.m_PetPlacardNeedLife = ini.ReadInt( "Pet", "PetPlacardNeedLife" );
	m_ConfigInfo.m_DefaultRespawnTime = ini.ReadInt( "Monster", "DefaultRespawnTime" );
	m_ConfigInfo.m_ValidAttackTime = ini.ReadInt("TimeSetting","ValidAttack");
	m_ConfigInfo.m_DropBoxRecycleTime = ini.ReadInt("TimeSetting","DropBoxRecycle");
	m_ConfigInfo.m_DropProtectTime = ini.ReadInt("TimeSetting","DropProtectTime");
	m_ConfigInfo.m_TimeChangeInterval	= ini.ReadInt("TimeSetting","TimeChangeInterval");
	m_ConfigInfo.m_PositionRange = ini.ReadInt( "Monster", "DefaultPositionRange" ) ;
	m_ConfigInfo.m_AIType = ini.ReadInt( "Monster", "DefaultAIType" ) ;
	m_ConfigInfo.m_DisconnectTime = ini.ReadInt( "TimeSetting", "DisconnectTime" ) ;
	ini.ReadText( "Temp", "UserPath", m_ConfigInfo.m_UserPath, _MAX_PATH ) ;
	m_ConfigInfo.m_DefaultBodyTime = ini.ReadInt( "Monster", "DefaultBodyTime" ) ;
	m_ConfigInfo.m_DefaultRefuseScanTime = ini.ReadInt( "Monster", "DefaultRefuseScanTime");
	m_ConfigInfo.m_OutGhostTime = ini.ReadInt( "Human", "OutGhostTime" ) ;
	m_ConfigInfo.m_CanGetExpRange = (FLOAT)(ini.ReadInt( "Human", "CanGetExpRange" ));
	m_ConfigInfo.m_DefaultMoveSpeed = ini.ReadInt( "Human", "DefaultMoveSpeed" ) ;
	m_ConfigInfo.m_DefaultAttackSpeed = ini.ReadInt( "Human", "DefaultAttackSpeed" ) ;
	m_ConfigInfo.m_HumanVERecoverInterval = ini.ReadInt( "Human", "HumanVERecoverInterval" ) ;
	m_ConfigInfo.m_HumanHGRecoverInterval = ini.ReadInt( "Human", "HumanHGRecoverInterval" ) ;
	m_ConfigInfo.m_HumanPneumaRecoverInterval = ini.ReadInt( "Human", "HumanPneumaRecoverInterval" ) ;
	m_ConfigInfo.m_RAGERecoverInterval = ini.ReadInt( "Human", "RAGERecoverInterval" ) ;	

	m_ConfigInfo.m_nAvailableFollowDist = ini.ReadInt( "Team", "AvailableFollowDist" );
	m_ConfigInfo.m_nTimeForLoseFollow = ini.ReadInt( "Team", "TimeForLoseFollow" );
	m_ConfigInfo.m_nFoundDurationHour = ini.ReadInt( "Guild", "FoundDuration" );
	m_ConfigInfo.m_nDefaultMaxMemberCount = ini.ReadInt( "Guild", "DefaultMaxMemberCount" );
	m_ConfigInfo.m_nResponseUserCount = ini.ReadInt( "Guild", "ResponseUserCount" );
	m_ConfigInfo.m_nPasswdPoint = ini.ReadInt( "Relation", "PasswdPoint" );
	m_ConfigInfo.m_nPromptPoint = ini.ReadInt( "Relation", "PromptPoint" );
	m_ConfigInfo.m_nDeleteDelayTime = ini.ReadInt( "MinorPassword", "DeleteDelayTime" );
	m_ConfigInfo.m_nDeleteDelayTime *= 3600;
	m_ConfigInfo.m_nExpPoint = ini.ReadInt( "Relation", "ExpPoint" );
	//m_ConfigInfo.m_DefaultRefreshRate	=	ini.ReadInt("Obj_Human","DefaultRefreshRate")	;
	m_ConfigInfo.m_nHashOnlineUserCount = ini.ReadInt( "World", "HashOnlineUserCount" );
	m_ConfigInfo.m_nHashMailUserCount = ini.ReadInt( "World", "HashMailUserCount" );
	m_ConfigInfo.m_nMaxOfflineUserCount = ini.ReadInt( "World", "MaxOfflineUserCount" );
	ini.ReadText( "Global", "RespawnParam", szText, sizeof(szText)-1 ) ;
	m_ConfigInfo.m_fRespawnParam = (FLOAT)(atof(szText)) ;
	m_ConfigInfo.m_KickUserTime = ini.ReadInt( "TimeSetting", "KickUserTime" );
	m_ConfigInfo.m_SMU_KickUserTime = ini.ReadInt( "TimeSetting", "SMU_KickUserTime" );
	m_ConfigInfo.m_nDefaultDamageFluctuation = ini.ReadInt("Combat","DefaultDamageFluctuation");
	m_ConfigInfo.m_nCriticalDamageRate = ini.ReadInt("Combat","CriticalDamageRate");
	m_ConfigInfo.m_nToughEffCriticalDamage = ini.ReadInt("Combat","ToughnessEffCriticalDamage");

	m_ConfigInfo.m_nMinGoodBadValue = ini.ReadInt( "GoodBad", "MinGoodBadValue" );
	m_ConfigInfo.m_nMaxGoodBadValue = ini.ReadInt( "GoodBad", "MaxGoodBadValue" );
	m_ConfigInfo.m_nLevelNeeded = ini.ReadInt( "GoodBad", "LevelNeeded" );
	m_ConfigInfo.m_nMemberLevel = ini.ReadInt( "GoodBad", "MemberLevel" );
	m_ConfigInfo.m_fGoodBadRadius = (FLOAT)ini.ReadInt( "GoodBad", "GoodBadRadius" );
	m_ConfigInfo.m_nBonusPerMember = ini.ReadInt( "GoodBad", "BonusPerMember" );
	m_ConfigInfo.m_nMaxBonus = ini.ReadInt( "GoodBad", "MaxBonus" );
	m_ConfigInfo.m_nPenaltyWhenMemberDie = ini.ReadInt( "GoodBad", "PenaltyWhenMemberDie" );

	m_ConfigInfo.m_nMinPaiScore = ini.ReadInt( "Equip", "MinPaiScore" );
	m_ConfigInfo.m_nMinZiPaiScore = ini.ReadInt( "Equip", "MinZiPaiScore" );
	m_ConfigInfo.m_nComMonsterDrop = ini.ReadInt( "Equip", "ComMonsterDrop" );
	m_ConfigInfo.m_nSenMonsterDrop = ini.ReadInt( "Equip", "SenMonsterDrop" );
	m_ConfigInfo.m_nBossDrop = ini.ReadInt( "Equip", "BossDrop" );
	m_ConfigInfo.m_nRefreshAttrToWorldInterval = ini.ReadInt("World", "RefreshAttrToWorldInterval");

	m_ConfigInfo.m_nSubTrainExp = ini.ReadInt( "SubTrain", "SubTrainExp" );
	m_ConfigInfo.m_nSubTrainMoney = ini.ReadInt( "SubTrain", "SubTrainMoney" );
	GLog::SaveLog( CONFIG_LOGFILE, "Load ConfigInfo.ini ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}


VOID Config::LoadServerInfo( )
{
__ENTER_FUNCTION

	LoadServerInfo_Only( ) ;
	LoadServerInfo_ReLoad( ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadServerInfo_Only( )
{
__ENTER_FUNCTION

	Ini ini( FILE_SERVER_INFO ) ;
	m_ServerInfo.m_ServerCount = ini.ReadInt( "System", "ServerNumber" ) ;

	m_ServerInfo.m_pServer = new _SERVER_DATA[m_ServerInfo.m_ServerCount] ;
	memset( m_ServerInfo.m_pServer, 0, sizeof(_SERVER_DATA)*m_ServerInfo.m_ServerCount ) ;

	for( uint i=0; i<m_ServerInfo.m_ServerCount; i++ )
	{
		CHAR szSection[256] ;
		memset( szSection, 0, 256 ) ;

		//初始化数据
		m_ServerInfo.m_pServer[i].Init( ) ;

		//读取场景“i”
		sprintf( szSection, "Server%d", i ) ;
		m_ServerInfo.m_pServer[i].m_ServerID = (ID_t)(ini.ReadInt( szSection, "ServerID" )) ;
		m_ServerInfo.m_pServer[i].m_MachineID = (ID_t)(ini.ReadInt( szSection, "MachineID" )) ;
		ini.ReadText( szSection, "IP0", m_ServerInfo.m_pServer[i].m_IP0, IP_SIZE ) ;
		m_ServerInfo.m_pServer[i].m_Port0 = (uint)(ini.ReadInt( szSection, "Port0" )) ;
		ini.ReadText( szSection, "IP1", m_ServerInfo.m_pServer[i].m_IP1, IP_SIZE ) ;
		m_ServerInfo.m_pServer[i].m_Port1 = (uint)(ini.ReadInt( szSection, "Port1" )) ;
		//enum SERVER_TYPE
		m_ServerInfo.m_pServer[i].m_Type = (uint)(ini.ReadInt( szSection, "Type" )) ;
		m_ServerInfo.m_pServer[i].m_HumanSMKey	=	(SM_KEY)(ini.ReadInt(szSection,"HumanSMKey"));
		m_ServerInfo.m_pServer[i].m_ItemSerialKey = (SM_KEY)(ini.ReadInt(szSection,"ItemSerialKey"));
		m_ServerInfo.m_pServer[i].m_EnableShareMem = (BOOL)(ini.ReadInt(szSection,"EnableShareMem"));


	}

	ini.ReadText( "World", "IP", m_ServerInfo.m_World.m_IP, IP_SIZE ) ;
	m_ServerInfo.m_World.m_Port = (uint)(ini.ReadInt( "World", "Port" )) ;


	//
	for(UINT i=0; i<m_ServerInfo.m_ServerCount; i++ )
	{
		ID_t ServerID = m_ServerInfo.m_pServer[i].m_ServerID ;

		Assert( ServerID != INVALID_ID && ServerID < OVER_MAX_SERVER ) ;

		Assert( m_ServerInfo.m_HashServer[ServerID] == -1 ) ;

		m_ServerInfo.m_HashServer[ServerID] = i ;
	}

	GLog::SaveLog( CONFIG_LOGFILE, "Load ServerInfo.ini ...Only OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadServerInfo_ReLoad( )
{
__ENTER_FUNCTION

	GLog::SaveLog( CONFIG_LOGFILE, "Load ServerInfo.ini ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}

VOID Config::LoadSceneInfo( )
{
__ENTER_FUNCTION

	LoadSceneInfo_Only( ) ;
	LoadSceneInfo_ReLoad( ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadSceneInfo_Only( )
{
__ENTER_FUNCTION
	

__LEAVE_FUNCTION
}
VOID Config::LoadSceneInfo_ReLoad( )
{
__ENTER_FUNCTION

	GLog::SaveLog( CONFIG_LOGFILE, "Load scenedefines.tab ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}