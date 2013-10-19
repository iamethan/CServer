#ifndef __EVENT_H__
#define __EVENT_H__

#include "Utility.h"
#include "Net.h"
#include <list>

// 事件类型
enum EVENT_TYPE
{
	EVENT_TYPE_STUB = 0,	// 网络节点相关事件
	EVENT_TYPE_SCENE,		// 场景相关事件
	EVENT_TYPE_PLAYER,		// 玩家相关事件
};

enum EVENT_ID
{
	EVENT_ID_ON_CONNECTED = 0,	// 建立连接
	EVENT_ID_ON_DISCONNECTED,	// 断开
	EVENT_ID_ON_ENTERSCENE,		// 进入场景
	EVENT_ID_ON_LEAVESCENE,		// 离开场景
	EVENT_ID_ON_READY,			// 进入场景后完成初始化
	EVENT_ID_ON_MOTION,			// 移动
	EVENT_ID_ON_USESKILL,		// 使用技能
	EVENT_ID_ON_BE_DAMAGE,		// 自身受到伤害
	EVENT_ID_ON_BE_KILLED,		// 自身被击杀
	EVENT_ID_ON_DAMAGE,			// 对其他对象造成伤害
	EVENT_ID_ON_KILL,			// 击杀其他对象

	EVENT_ID_COUNT,
};

#define EVENT_TYPEID(type, id)	(type<<24) | id
#define GET_EVENT_TYPE(typeid)	typeid >> 24
#define GET_EVENT_ID(typeid)	typeid & 0x00FFFFFF

class GSystem;

class IEvent
{
public:
	typedef int		FuncAddr;

private:
	friend class EventManager;

	struct Handle
	{
		GSystem*		m_pListener;
		FuncAddr		m_pFuncHandle;
	};
	typedef std::list<Handle*> HandleList;

public:
	IEvent( );
	virtual ~IEvent();

	virtual EVENT_ID	ID( ) = 0;

	VOID		Type( EVENT_TYPE eType )	{ m_eType = eType;		}
	EVENT_TYPE	Type( )						{ return m_eType;		}

	VOID		Sender( UINT nSender )		{ m_nSender = nSender;	}
	UINT		Sender( )					{ return m_nSender;		}

	BOOL		RegisterHandle( GSystem* pListener, FuncAddr pFuncHandle );

protected:
	EVENT_TYPE	m_eType;
	UINT		m_nSender;

	HandleList	m_lstHandles;
};

// 建立连接事件
class ConnectedEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_CONNECTED;	}

	VOID	SetStub( Stub* pStub )	{ m_pStub = pStub;		}
	Stub*	GetStub( )				{ return m_pStub;		}		

protected:
	Stub*	m_pStub;
};

// 断开连接事件
class DisconnectedEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_DISCONNECTED;	}

	VOID	SetStub( Stub* pStub )	{ m_pStub = pStub;		}
	Stub*	GetStub( )				{ return m_pStub;		}

protected:
	Stub*	m_pStub;
};

// 进入场景事件
class EnterSceneEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_ENTERSCENE;	}

	VOID	SceneID( UINT nSceneID )	{ m_nSceneID = nSceneID;	}
	UINT	SceneID( )					{ return m_nSceneID;		}

protected:
	UINT	m_nSceneID;
};

// 离开场景事件
class LeaveSceneEvent : public IEvent
{
public:
	virtual EVENT_ID ID( ) { return EVENT_ID_ON_LEAVESCENE;		}

	VOID	SceneID( UINT nSceneID )	{ m_nSceneID = nSceneID;	}
	UINT	SceneID( )					{ return m_nSceneID;		}

protected:
	UINT	m_nSceneID;
};

// 准备完成事件
class ReadyEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_READY;		}
};

// 移动事件
class MotionEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_MOTION;	}

	VOID		POS( WORLD_POS& tPos )	{ m_tPos = tPos;	}
	WORLD_POS&	POS( )					{ return m_tPos;	}

	VOID		Orient( FLOAT o )		{ m_fOrient = o;	}
	FLOAT		Orient( )				{ return m_fOrient;	}

protected:
	WORLD_POS	m_tPos;
	FLOAT		m_fOrient;
};

// 使用技能事件
class UseSkillEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )		{ return EVENT_ID_ON_USESKILL;	}

protected:

};

// 受到伤害事件
class BeDamageEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )		{ return EVENT_ID_ON_BE_DAMAGE;	}

protected:
};

// 被杀死事件
class BeKilledEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )		{ return EVENT_ID_ON_BE_KILLED;	}

protected:
};

// 对其他对象造成伤害事件
class DamageEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )				{ return EVENT_ID_ON_DAMAGE;	}

	VOID	ObjID( UINT nObjID )		{ m_nObjID = nObjID;			}
	UINT	ObjID( )					{ return m_nObjID;				}

	VOID	DamageType( UINT nType )	{ m_nDamageType = nType;		}
	UINT	DamageType( )				{ return m_nDamageType;			}

	VOID	DamageValue( UINT nValue )	{ m_nDamageValue = nValue;		}
	UINT	DamageValue( )				{ return m_nDamageValue;		}

protected:
	UINT	m_nObjID;			// 造成伤害的对象ID
	UINT	m_nDamageType;		// 伤害类型
	UINT	m_nDamageValue;		// 伤害数值
};

// 杀死其他对象事件
class KillEvenet : public IEvent
{
public:
	virtual EVENT_ID ID( )			{ return EVENT_ID_ON_KILL;	}

	VOID	ObjID( UINT nObjID )	{ m_nObjID = nObjID;		}
	UINT	ObjID( )				{ return m_nObjID;			}

protected:
	UINT	m_nObjID;
};

#endif // __EVENT_H__