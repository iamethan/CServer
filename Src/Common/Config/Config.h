

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Base/Type.h"
#include "Define/GameDefine.h"

//Config
struct _CONFIG_INFO
{
	ID_t			m_ServerID ;
	INT				m_SystemMode;				//系统模式0表示轻量级模式,1表示完整模式
	INT				m_ZoneSize ;
	FLOAT			m_DropParam;				//全局掉落修正参数
	FLOAT			m_ExpParam;					//全局经验修正参数
	INT				m_EquipmentDamagePoint;		//物品耐久度的微调值
	INT				m_DropSearchRange;			//掉落搜索格子数
	FLOAT			m_DropPosDistance;			//掉落物品间隔
	INT				m_LevelupAllocPoints;		//升级分配点数（可用于玩家可手动调点）
	INT				m_RecoverTime ;
	INT				m_MaxMonster ;
	INT				m_MaxPet ;
	INT				m_PetBodyTime ;
	INT				m_PetHappinessInterval;		// 宠物快乐度下降1的时间间隔(毫少)
	INT				m_PetLifeInterval;			// 宠物寿命下降1的时间间隔(毫少)
	INT				m_PetCallUpHappiness;		// 宠物快乐度大于才可以召出
	UINT			m_PetPlacardTime;			// 发布一个宠物公告的持续时间
	INT				m_PetPlacardNeedLevel;		// 发布宠物公告的宠物所需级别
	INT				m_PetPlacardNeedHappiness;	// 发布宠物公告的宠物所需快乐度
	INT				m_PetPlacardNeedLife;		// 发布宠物公告的宠物所需寿命
	INT				m_nHorseCheckUpSpend;		// 马鉴定花费的游戏币
	INT				m_nHorseMattingSpend;		// 马交配要花费的游戏币
	INT				m_DefaultRespawnTime ;
	INT				m_ValidAttackTime;
	INT				m_DropBoxRecycleTime;
	INT				m_DropProtectTime;
	INT				m_TimeChangeInterval;		//时辰变更间隔
	INT				m_PositionRange ;
	INT				m_AIType ;
	INT				m_DisconnectTime ;
	CHAR			m_UserPath[_MAX_PATH] ;
	INT				m_MaxPortal ;
	INT				m_MaxSkillObj ;
	INT				m_DefaultBodyTime ;			//尸体存在时间
	INT				m_OutGhostTime ;			//释放灵魂时间
	FLOAT			m_CanGetExpRange ;			//杀死角色后可以得到EXP的范围
	INT				m_DefaultMoveSpeed ;
	INT				m_DefaultAttackSpeed ;
	INT				m_HumanVERecoverInterval;	// 精力与活力的恢复时间间隔(毫少)
	INT				m_HumanHGRecoverInterval;	// 血的恢复时间间隔（毫秒）
	INT				m_HumanPneumaRecoverInterval;	// 元气的恢复时间间隔（毫秒）
	INT				m_RAGERecoverInterval;		//怒气的恢复时间间隔（毫秒）

	INT				m_DefaultRefreshRate ;		//活力点刷新时间
	INT				m_DefaultCheckZoneRate ;	//刷新区域信息的时间间隔
	INT				m_DefaultRefuseScanTime;	//缺省怪物重生后不会扫描敌人的时间
	INT				m_MaxPlatform;
	INT				m_MaxSpecial;				// 技能OBJ的数量
	INT				m_MaxBus;					//最大Bus数量
	INT				m_MaxPlayerShopNum;			// 玩家商店的数量
	INT             m_MaxTimerCount;			//场景计时器数目
	INT				m_nMaxHumanUseTimer;		//Obj_Human可使用计时器数目
	INT				m_nAvailableFollowDist;		// 组队跟随的有效距离
	INT				m_nTimeForLoseFollow;		// 组队跟随超出有效距离多长时间后主动退出组队跟随(秒)
	INT				m_nFoundDurationHour;		// 创建周期
	INT				m_nDefaultMaxMemberCount;	// 默认帮会容纳帮众数
	INT				m_nResponseUserCount;		// 建立帮会需要的响应玩家数（含帮主）
	INT				m_nPasswdPoint;				// 多少点友好度需要输入二级密码
	INT				m_nPromptPoint;				// 多少点友好度需要提示上下线
	INT				m_nDeleteDelayTime;			// 多少小时以后再次强制解除则删除二级密码
	INT				m_nExpPoint;				// 获得多少经验可以提升友好度
	INT				m_nHashOnlineUserCount ;	//在线玩家的hash表大小
	INT				m_nHashMailUserCount ;		//拥有邮件的玩家hash表大小
	INT				m_nMaxOfflineUserCount ;	//登陆过游戏的玩家数量最大值
	FLOAT			m_fRespawnParam ;			//怪物刷新修正系数
	INT				m_KickUserTime ;			//不是正常游戏玩家的踢除倒计时间
	INT				m_SMU_KickUserTime;			//保存玩家档案的踢除剩余时间
	INT				m_nDefaultDamageFluctuation; // 缺省得伤害浮动
	INT				m_nCriticalDamageRate;		//基础爆击伤害比例
	INT				m_nToughEffCriticalDamage;	//韧性对爆击伤害的影响参数

	INT				m_nMinGoodBadValue;			// 最小善恶值
	INT				m_nMaxGoodBadValue;			// 最大善恶值
	INT				m_nLevelNeeded;				// 获得善恶值的最低等级
	INT				m_nMemberLevel;				// 能给队长带来善恶值的队友最高等级
	FLOAT			m_fGoodBadRadius;			// 获得善恶值的半径
	INT				m_nBonusPerMember;			// 每个有效队友能增加的善恶值点数
	INT				m_nMaxBonus;				// 杀死一只怪能给队长带来的最大善恶值点数
	INT				m_nPenaltyWhenMemberDie;	// 有效队友的死亡减少队长的善恶值点数

	INT				m_nMinPaiScore;				//最小牌型需求分数
	INT				m_nMinZiPaiScore;			//最小字牌需求分数
	INT				m_nComMonsterDrop;			//普通怪影响属性等级加成
	INT				m_nSenMonsterDrop;			//特殊怪影响属性等级加成
	INT				m_nBossDrop;				//Boss影响属性等级加成
	INT				m_nRefreshAttrToWorldInterval;	//向World刷新数据的时间间隔

	INT				m_nSubTrainExp;				//带练经验效率常量
	INT				m_nSubTrainMoney;			//带练金钱效率常量
    INT				m_nDelateNum;	    		//弹劾发起票数，策划默认3
    INT				m_nVoteNum;	    		    //投票数有效的下限，策划默认100
    INT				m_nVoteTime;                //投票持续时间，策划默认4个小时,单位分钟

	_CONFIG_INFO( )
	{
		m_ServerID				= INVALID_ID ;
		m_SystemMode			= 0;
		m_ZoneSize				= 10 ;
		m_EquipmentDamagePoint	= 1000;
		m_DropSearchRange		= 200;
		m_DropPosDistance		= 2.0;
		m_RecoverTime			= 1000 ;
		m_MaxMonster			= 1000 ;
		m_MaxPet				= 1000 ;
		m_PetBodyTime			= 2000 ;
		m_PetHappinessInterval	= 600000;
		m_PetLifeInterval		= 30 * 60 * 1000;
		m_PetCallUpHappiness	= 60;
		m_PetPlacardTime		= 1000*60*30;
		m_DefaultRespawnTime	= 300000 ;
		m_DropBoxRecycleTime	= 300000 ;
		m_ValidAttackTime		= 6000;
		m_DropProtectTime		= 100000 ;
		m_TimeChangeInterval	= 300000 ;
		m_PositionRange			= 10 ;
		m_AIType				= 1 ;
		m_DisconnectTime		= 0 ;
		memset( m_UserPath, 0, _MAX_PATH ) ;
		m_MaxPortal				= 0 ;
		m_MaxPlatform			= 0;
		m_MaxSpecial			= 1024;
		m_MaxBus	=64;
		m_MaxPlayerShopNum		= 512;
		m_MaxSkillObj			= 1024;
		m_DefaultBodyTime		= 0 ;
		m_OutGhostTime			= 0 ;
		m_CanGetExpRange		= 30.f;
		m_DefaultMoveSpeed      = 2800 ;
		m_DefaultAttackSpeed    = 2000 ;
		m_HumanVERecoverInterval= 300000;
		m_HumanHGRecoverInterval= 5000;
		m_RAGERecoverInterval= 5000;		

		m_DefaultRefreshRate    = 60000 ;
		m_DefaultCheckZoneRate  = 1000 ;
		m_nAvailableFollowDist	= 15;
		m_nTimeForLoseFollow	= 30;
		m_nFoundDurationHour	= 24;
		m_nDefaultMaxMemberCount= 160;
		m_nResponseUserCount	= 10;
		m_nPasswdPoint			= 0;
		m_nPromptPoint			= 0;
		m_nDeleteDelayTime		= 0;
		m_nExpPoint				= 0;
		m_nHashOnlineUserCount	= 1000 ;
		m_nHashMailUserCount	= 1000 ;
		m_nMaxOfflineUserCount	= 0 ;
		m_fRespawnParam			= 1.0f ;
		m_KickUserTime			= 300000 ;
		m_nDefaultDamageFluctuation = 10 ;
		m_nCriticalDamageRate	= 100;		//基础爆击伤害比例
		m_nToughEffCriticalDamage = 100;	//韧性对爆击伤害的影响参数

		m_nMinGoodBadValue		= 0;
		m_nMaxGoodBadValue		= 9999;
		m_nLevelNeeded			= 31;
		m_nMemberLevel			= 19;
		m_fGoodBadRadius		= 15.;
		m_nBonusPerMember		= 1;
		m_nMaxBonus				= 2;
		m_nPenaltyWhenMemberDie	= 10;

		m_nMinPaiScore			= 100;				
		m_nMinZiPaiScore		= 300;			
		m_nComMonsterDrop		= 0;			
		m_nSenMonsterDrop		= 0;			
		m_nBossDrop				= 0;
		m_nHorseCheckUpSpend	= 100;
		m_nHorseMattingSpend	= 20000;
		m_nRefreshAttrToWorldInterval = 300000;//5 minutes
		
        m_nDelateNum            = 3;
        m_nVoteNum              = 100;	 
        m_nVoteTime             = 240; 
	};
	~_CONFIG_INFO( )
	{
	};
};

//Machine
struct _MACHINE_DATA
{
	ID_t			m_MachineID ;

	_MACHINE_DATA( )
	{
		Init( ) ;
	};
	VOID Init( )
	{
		m_MachineID = INVALID_ID ;
	}
};

struct _MACHINE_INFO
{
	_MACHINE_DATA*	m_pMachine ;
	uint			m_MachineCount ;

	_MACHINE_INFO( )
	{
		m_pMachine = NULL ;
		m_MachineCount = 0 ;
	};
	~_MACHINE_INFO( )
	{
		SAFE_DELETE_ARRAY( m_pMachine ) ;
		m_MachineCount = 0 ;
	};
};

//proxy
typedef enum _ENUM_ISP
{
	INVALID_ISP = -1,
	ISP_CHINA_NET_COM = 0,
	ISP_CHINA_TELE_COM,
	ISP_CHINA_EDU,
	NUM_OF_ISP
} ENUM_ISP;
// IspID的顺序必须和_ENUM_ISP的顺序一致
extern CHAR g_szIspID[NUM_OF_ISP][16];

typedef struct _PROXY_DATA
{
	ID_t 	m_nIsp;
	CHAR	m_szIP[IP_SIZE];
	UINT	m_nPort;
	BOOL	m_bEnabled;
	_PROXY_DATA(VOID): m_nIsp(INVALID_ISP), m_nPort(0xFFFFFFFF), m_bEnabled(FALSE)
	{
		m_szIP[0]='\0';
	}
	VOID CleanUp(VOID)
	{
		m_nIsp = INVALID_ISP;
		m_szIP[0] ='\0';
		m_nPort = 0xFFFFFFFF;
		m_bEnabled = FALSE;
	}
} PROXY_DATA;

//Server
struct _SERVER_DATA
{
	ID_t			m_ServerID ;
	ID_t			m_MachineID ;
	CHAR			m_IP0[IP_SIZE] ;
	uint			m_Port0 ;
	CHAR			m_IP1[IP_SIZE] ;
	uint			m_Port1 ;
	INT				m_Type ;
	PROXY_DATA		m_aProxy[NUM_OF_ISP];

	SM_KEY			m_HumanSMKey;
	SM_KEY			m_PlayShopSMKey;
	SM_KEY			m_ItemSerialKey;
	SM_KEY			m_CommionShopSMKey;
	BOOL			m_EnableShareMem;


	_SERVER_DATA( )
	{
		Init( ) ;
	};
	VOID Init( )
	{
		m_ServerID = INVALID_ID ;
		m_MachineID = INVALID_ID ;
		memset( m_IP0, 0, IP_SIZE ) ;
		m_Port0 = 0 ;
		memset( m_IP1, 0, IP_SIZE ) ;
		m_Port1 = 0 ;
		m_Type = -1 ;
		for(INT i = ISP_CHINA_NET_COM; NUM_OF_ISP>i; ++i)
		{
			m_aProxy[i].CleanUp();
		}
		m_EnableShareMem = FALSE;
	}
};

struct _SERVER_WORLD
{
	CHAR			m_IP[IP_SIZE] ;
	uint			m_Port ;

	_SERVER_WORLD( )
	{
		Init( ) ;
	}
	VOID Init( )
	{
		memset( m_IP, 0, IP_SIZE ) ;
		m_Port = 0 ;
	}
};



#define OVER_MAX_SERVER 256
struct _SERVER_INFO
{
	_SERVER_DATA*	m_pServer ;	
	uint			m_ServerCount ;
	INT				m_HashServer[OVER_MAX_SERVER] ;
	_SERVER_WORLD	m_World ;

	_SERVER_INFO( )
	{
		m_pServer = NULL ;
		m_ServerCount = 0 ;
		for( INT i=0; i<OVER_MAX_SERVER; i++ )
		{
			m_HashServer[i] = -1 ;
		}
	}
	~_SERVER_INFO( )
	{
		SAFE_DELETE_ARRAY( m_pServer ) ;
		m_ServerCount = 0 ; 
	}
};


//Scene
struct _SCENE_DATA
{
	SceneID_t		m_SceneID ;					//场景ID
	INT				m_IsActive ;				//是不是可以使用的场景
	CHAR			m_szName[_MAX_PATH] ;		//场景名称
	CHAR			m_szFileName[_MAX_PATH] ;	//场景资源文件的文件名
	ID_t			m_ServerID ;				//运行此场景的Server端程序ID
	ID_t			m_Type ;					//当前场景属于某个副本
												//如果值为INVALID_ID则不属于副本
	ID_t			m_ThreadIndex ;				//驱动线程的索引

	_SCENE_DATA()
	{
		Init( ) ;
	};
	VOID Init( )
	{
		m_SceneID = INVALID_ID ;
		m_IsActive = 1 ;
		memset( m_szName, 0, _MAX_PATH ) ;
		memset( m_szFileName, 0, _MAX_PATH ) ;
		m_ServerID = INVALID_ID ;
		m_Type = INVALID_ID ;
		m_ThreadIndex = INVALID_INDEX ;
		m_ClientRes = INVALID_INDEX ;
	}

	VOID _SetClientRes( ID_t ClientRes )
	{
		m_ClientRes = ClientRes ;
	}
	ID_t _GetClientRes()
	{
		return m_ClientRes ;
	}

private:
	ID_t			m_ClientRes ;				//客户端资源索引

};

struct _SCENE_INFO
{
	_SCENE_DATA*	m_pScene ;
	UINT			m_SceneCount ;
	INT				m_HashScene[MAX_SCENE] ;

	_SCENE_INFO(){
		m_pScene = NULL ;
		m_SceneCount = 0 ;
		for( INT i=0; i<MAX_SCENE; i++ )
		{
			m_HashScene[i] = -1 ;
		}
	};
	~_SCENE_INFO(){
		SAFE_DELETE_ARRAY( m_pScene ) ;
		m_SceneCount = 0 ;
	};
};

class Config
{
public :
	Config( ) ;
	~Config( ) ;

	BOOL					Init( ) ;
	VOID					ReLoad( ) ;


	VOID					LoadConfigInfo( ) ;
	VOID					LoadConfigInfo_Only( ) ;
	VOID					LoadConfigInfo_ReLoad( ) ;

	VOID					LoadServerInfo( ) ;
	VOID					LoadServerInfo_Only( ) ;
	VOID					LoadServerInfo_ReLoad( ) ;
	
	VOID					LoadSceneInfo( ) ;
	VOID					LoadSceneInfo_Only( ) ;
	VOID					LoadSceneInfo_ReLoad( );


public :
	_CONFIG_INFO			m_ConfigInfo ;
	_SERVER_INFO			m_ServerInfo ;
	_SCENE_INFO				m_SceneInfo ;
};

extern Config g_Config ;

#endif
