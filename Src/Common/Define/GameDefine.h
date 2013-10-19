
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

//�Ƿ�ִ�и��ϸ�Ĳ߻�����У��
#define CHECK_DATA_TABLE 1
/////////////////////////////////////////////////////////////////////////////////
//��Ϸ������Ϣ�궨��
/////////////////////////////////////////////////////////////////////////////////
//��������ֵ
#define MAX_WORLD 255

#define MAX_WORLD_USER	3000

//�û���ɫ���ֿ�����������ֵ
#define MAX_CHARACTER_INPUTNAME 24
//��ҳƺų���
#define MAX_CHARACTER_TITLE 34

//����˺ų���
#define MAX_ACCOUNT_LENGTH	50

//GamePlayer������������
#define MAX_PLAYER 1024

//��ҳ�����
//#define MAX_POOL_SIZE 1280
//��ҳ�����
#define MAX_POOL_SIZE (2048)
#define MAX_DUMMY_POOL_SIZE 64
//��½��������ҳ�
#define MAX_LOGIN_POOL_SIZE 1024*3

//�û���ɫ���ֽṹ |CharacterName|@|WorldID|00|
//					��ɫ����      1  3      2����
//ע�⣺��ɫ���ֺ���ĺ�׺����@WorldID�������û�������ɫʱ���Զ���ӽ��ģ�
//		�������˴���ʱ����ʹ���������֣�
//		�ͻ�����ʾ��ʱ�������ǰ��ɫ�Ǳ����紴��������ȥ������ĺ�׺��
//�û���ɫ���Ƶ����ֵ
#define MAX_CHARACTER_NAME 30

//����Զ������������ֵ
#define MAX_GROUP_NAME		12

//��ҳƺų���
#define MAX_CHARACTER_TITLE 34

#define MAX_TITLE_COMBINATION 10

//NPC���������Ƴ���
#define NPC_NAME_LEN 32

//��ɫ���ǳ�
#define MAX_NICK_NAME 34

//����ܴ�����ɫ������
#define MAX_CREATE_PLAYER_NUM 3

// ��ɫ���ܵ����·��������
#define MAX_CHAR_PATH_NODE_NUMBER	(16)

/////////////////////////////////////////////////////////////////////////////////
// �������
/////////////////////////////////////////////////////////////////////////////////
//��������ģ����Թ������󳡾�����
#define MAX_SCENE 1024

// һ�� zone ������Լ������� Area ����
#define MAX_AREA_IN_ZONE		10

//
#define ZONE_SIZE	10

//
#define MAX_SEND_TIME 1

//����Zone���ӵķ�Χ,0=1��(���������Լ��ڵ��Ǹ�����)��1=9��;2=25��;3=49��;
#define MAX_RADIUS 2

/////////////////////////////////////////////////////////////////////////////////
//��Ϸ�������ݲ�����
/////////////////////////////////////////////////////////////////////////////////

//��GUID_t��ȡ�������
#define GETWORLD(u) ((u)/10000000)
//��GUID_t��ȡ���û��������к�
#define GETUSER(u) ((u)%10000000)
//�жϵ�ǰ�Ƿ��ǲ�������
#define ISTESTWORLD(w) ((w)>200?1:0)
//�ж�������Ƿ�Ϸ�
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
