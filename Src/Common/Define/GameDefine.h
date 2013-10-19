
#ifndef __GAMEDEFINE_H__
#define __GAMEDEFINE_H__

//
#define INVALID_COUNTRY		-1
#define INVALID_JOB			-1
#define INVALID_SEX			-1
#define INVALID_GUILD_ID  	-1
#define INVALID_RESOURCE    -1
#define INVALID_RULERID		-1
#define INVALID_PRICE		 0
#define INVALID_ITEM_ID		 0
#define INVALID_ITEM_POS	-1
#define INVALID_TIME		 0xFFFFFFFF
#define INVALID_PAI_TYPE	 0
#define INVALID_SOUL_TYPE	 0
#define BASE_BAG_POS		 185

//是否执行更严格的策划数据校验
#define CHECK_DATA_TABLE 1
/////////////////////////////////////////////////////////////////////////////////
//游戏基本信息宏定义
/////////////////////////////////////////////////////////////////////////////////
//世界号最大值
#define MAX_WORLD 255

#define MAX_WORLD_USER	3000

//用户角色名字可以输入的最大值
#define MAX_CHARACTER_INPUTNAME 24
//玩家称号长度
#define MAX_CHARACTER_TITLE 34

//玩家账号长度
#define MAX_ACCOUNT_LENGTH	50

//GamePlayer管理器的上限
#define MAX_PLAYER 1024

//玩家池上限
//#define MAX_POOL_SIZE 1280
//玩家池上限
#define MAX_POOL_SIZE (2048)
#define MAX_DUMMY_POOL_SIZE 64
//登陆服务器玩家池
#define MAX_LOGIN_POOL_SIZE 1024*3

//用户角色名字结构 |CharacterName|@|WorldID|00|
//					角色名字      1  3      2个零
//注意：角色名字后面的后缀：“@WorldID”是在用户创建角色时候自动添加进的；
//		服务器端处理时候都是使用完整名字；
//		客户端显示的时候，如果当前角色是本世界创建，则需去掉后面的后缀；
//用户角色名称的最大值
#define MAX_CHARACTER_NAME 30

//玩家自定义组名字最大值
#define MAX_GROUP_NAME		12

//玩家称号长度
#define MAX_CHARACTER_TITLE 34

#define MAX_TITLE_COMBINATION 10

//NPC（或怪物）名称长度
#define NPC_NAME_LEN 32

//角色的昵称
#define MAX_NICK_NAME 34

//最多能创建角色的数量
#define MAX_CREATE_PLAYER_NUM 3

// 角色接受的最大路径点数量
#define MAX_CHAR_PATH_NODE_NUMBER	(16)

/////////////////////////////////////////////////////////////////////////////////
// 场景相关
/////////////////////////////////////////////////////////////////////////////////
//场景管理模块可以管理的最大场景数量
#define MAX_SCENE 1024

// 一个 zone 里面可以加入的最大 Area 数量
#define MAX_AREA_IN_ZONE		10

//
#define ZONE_SIZE	10

//
#define MAX_SEND_TIME 1

//搜索Zone格子的范围,0=1格(仅仅包含自己在的那个格子)，1=9格;2=25格;3=49格;
#define MAX_RADIUS 2

/////////////////////////////////////////////////////////////////////////////////
//游戏基本数据操作宏
/////////////////////////////////////////////////////////////////////////////////

//从GUID_t中取得世界号
#define GETWORLD(u) ((u)/10000000)
//从GUID_t中取得用户部分序列号
#define GETUSER(u) ((u)%10000000)
//判断当前是否是测试世界
#define ISTESTWORLD(w) ((w)>200?1:0)
//判断世界号是否合法
#define ISVALIDWORLD(w) (((w)>0)?(((w)<MAX_WORLD)?1:0):(0))


#define ABS(m) ((m)>0?(m):(m)*(-1))

#define LENGTH(x0,z0,x1,z1)  (ABS((x0)-(x1))+ABS((z0)-(z1)))

#define MAX_FILE_PATH  260

#define MAKE_COLOR(r,g,b,a)		(((r&0xFF)<<24)|((g&0xFF)<<16)|((b&0xFF)<<8)|(a&0xFF))
#define COLOR_R(color)			((color>>24)&0x000000FF)
#define COLOR_G(color)			((color>>16)&0x000000FF)
#define COLOR_B(color)			((color>>8)&0x000000FF)
#define COLOR_A(color)			((color)&0x000000FF)

#define	MIN_LIMIT_VALUE(__test_value_, __min_value_)	\
	(__test_value_ < __min_value_ ? __min_value_ : __test_value_)
#define	MINLV0(__test_value_)	MIN_LIMIT_VALUE(__test_value_, 0)

#define	MAX_LIMIT_VALUE(__test_value_, __max_value_)	\
	(__test_value_ > __max_value_ ? __max_value_, __test_value_)

////////////////////////////////////////////////////
#include "GameDefine_Attr.h"
#include "GameDefine_Result.h"

#endif
