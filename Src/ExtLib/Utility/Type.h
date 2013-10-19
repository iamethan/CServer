#ifndef __TYPE_H__
#define __TYPE_H__


#include <vector>
#include "BaseType.h"


///////////////////////////////////////////////////////////////////////
//基本数据类型定义
///////////////////////////////////////////////////////////////////////


typedef SHORT	ID_t;
typedef UINT	ObjID_t;			//场景中固定的所有OBJ拥有不同的ObjID_t
									//
// stub
typedef ID_t			StubInnerID_t;		// stub内部使用号，有pool统一管理
typedef UINT			StubID_t;			
typedef ID_t			StubType_t;

typedef INT				Time_t; //时间类型

typedef	UINT			ObjID_t;	// 对象ID

// player
typedef	UINT			PlayerID_t;	// 玩家ID

// scene
typedef	ID_t			SceneID_t;

typedef struct _Int64
{
	LONG				a;
	ULONG				b;
}Int64;

//用来定义在世界的浮点位置
struct WORLD_POS
{
	FLOAT	 m_fX ;
	FLOAT	 m_fZ ;

	WORLD_POS(VOID)					: m_fX(0.0f), m_fZ(0.0f)	{}
	WORLD_POS(FLOAT fX, FLOAT fZ)	: m_fX(fX)	, m_fZ(fZ)		{}
	VOID	CleanUp( ){
		m_fX = 0.0f ;
		m_fZ = 0.0f ;
	};
	WORLD_POS& operator=(WORLD_POS const& rhs)
	{
		m_fX = rhs.m_fX;
		m_fZ = rhs.m_fZ;
		return *this;
	}
	BOOL	operator==(WORLD_POS& Ref)
	{
		return (fabs(m_fX-Ref.m_fX)+fabs(m_fZ-Ref.m_fZ))<0.0001f;

	}
	BOOL	operator==(const WORLD_POS& Ref)
	{
		return (fabs(m_fX-Ref.m_fX)+fabs(m_fZ-Ref.m_fZ))<0.0001f;

	}
};

typedef UINT			GUID_t;	//32位唯一编号。
								//如果用于表示用户唯一ID号，用户部分为9位
								//前三位为世界号,世界号0～200为正式数据，
								//					   201～MAX_WORLD-1为测试数据
								//世界号不能超过或等于 MAX_WORLD
								//通过 GETWORLD 宏可以从GUID_t中取得世界号

#define INVALID_GUID			((GUID_t)(-1))
#define INVALID_INDEX			(-1)
#define INVALID_ID_EX			-2

#if defined(__LINUX__) || defined(__WIN_CONSOLE__)
	typedef UCHAR  BYTE;
	typedef USHORT WORD;
	typedef	ULONG  DWORD;
#endif


#if defined(__WINDOWS__)
	typedef DWORD		TID ;
	//用来定义玩家各个子模型是否可见 
	typedef unsigned __int64 MODEL_PART;
#elif defined(__LINUX__)
	typedef pthread_t	TID ;
	typedef unsigned long long MODEL_PART;
	typedef const char* LPCSTR;
#endif

#if defined(__LINUX__)
	typedef		INT		SMHandle;
#elif defined(__WINDOWS__)
	typedef		VOID*	SMHandle;
#endif

typedef		VOID*	DBHandle;




//判断某位是否被置
//15.14....3.2.1.0 
#define ISSET0(x) ((x)&0x1)
#define ISSET1(x) ((x)&0x2)
#define ISSET2(x) ((x)&0x4)
#define ISSET3(x) ((x)&0x8)
#define ISSET4(x) ((x)&0x10)
#define ISSET5(x) ((x)&0x20)
#define ISSET6(x) ((x)&0x40)
#define ISSET7(x) ((x)&0x80)
#define ISSET8(x) ((x)&0x100)
#define ISSET9(x) ((x)&0x200)
#define ISSET10(x) ((x)&0x400)
#define ISSET11(x) ((x)&0x800)
#define ISSET12(x) ((x)&0x1000)
#define ISSET13(x) ((x)&0x2000)
#define ISSET14(x) ((x)&0x4000)
#define ISSET15(x) ((x)&0x8000)

///////////////////////////////////////////////////////////////////////
//基本头文件引用
///////////////////////////////////////////////////////////////////////
#include "Assertx.h"
#include "GameUtil.h"

#if defined(GAME_CLIENT)
	#define __ENTER_FUNCTION 
	#define __LEAVE_FUNCTION
#elif 1

#if defined(__WINDOWS__)
	#if defined(NDEBUG)
		#define __ENTER_FUNCTION {try{
		#define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__FUNCTION__);}}
	#else
		#define __ENTER_FUNCTION {try{
		#define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__FUNCTION__);}}
	#endif
#else	//linux
	#define __ENTER_FUNCTION {try{
	#define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__PRETTY_FUNCTION__);}}
#endif 
#endif

///////////////////////////////////////////////////////////////////////
//去除Warning提示
///////////////////////////////////////////////////////////////////////
#pragma warning (disable:4996)

#endif
