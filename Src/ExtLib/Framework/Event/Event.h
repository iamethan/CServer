#ifndef __EVENT_H__
#define __EVENT_H__

#include "Utility.h"
#include "Net.h"
#include <list>

// �¼�����
enum EVENT_TYPE
{
	EVENT_TYPE_STUB = 0,	// ����ڵ�����¼�
	EVENT_TYPE_SCENE,		// ��������¼�
	EVENT_TYPE_PLAYER,		// �������¼�
};

enum EVENT_ID
{
	EVENT_ID_ON_CONNECTED = 0,	// ��������
	EVENT_ID_ON_DISCONNECTED,	// �Ͽ�
	EVENT_ID_ON_ENTERSCENE,		// ���볡��
	EVENT_ID_ON_LEAVESCENE,		// �뿪����
	EVENT_ID_ON_READY,			// ���볡������ɳ�ʼ��
	EVENT_ID_ON_MOTION,			// �ƶ�
	EVENT_ID_ON_USESKILL,		// ʹ�ü���
	EVENT_ID_ON_BE_DAMAGE,		// �����ܵ��˺�
	EVENT_ID_ON_BE_KILLED,		// ������ɱ
	EVENT_ID_ON_DAMAGE,			// ��������������˺�
	EVENT_ID_ON_KILL,			// ��ɱ��������

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

// ���������¼�
class ConnectedEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_CONNECTED;	}

	VOID	SetStub( Stub* pStub )	{ m_pStub = pStub;		}
	Stub*	GetStub( )				{ return m_pStub;		}		

protected:
	Stub*	m_pStub;
};

// �Ͽ������¼�
class DisconnectedEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_DISCONNECTED;	}

	VOID	SetStub( Stub* pStub )	{ m_pStub = pStub;		}
	Stub*	GetStub( )				{ return m_pStub;		}

protected:
	Stub*	m_pStub;
};

// ���볡���¼�
class EnterSceneEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_ENTERSCENE;	}

	VOID	SceneID( UINT nSceneID )	{ m_nSceneID = nSceneID;	}
	UINT	SceneID( )					{ return m_nSceneID;		}

protected:
	UINT	m_nSceneID;
};

// �뿪�����¼�
class LeaveSceneEvent : public IEvent
{
public:
	virtual EVENT_ID ID( ) { return EVENT_ID_ON_LEAVESCENE;		}

	VOID	SceneID( UINT nSceneID )	{ m_nSceneID = nSceneID;	}
	UINT	SceneID( )					{ return m_nSceneID;		}

protected:
	UINT	m_nSceneID;
};

// ׼������¼�
class ReadyEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )	{ return EVENT_ID_ON_READY;		}
};

// �ƶ��¼�
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

// ʹ�ü����¼�
class UseSkillEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )		{ return EVENT_ID_ON_USESKILL;	}

protected:

};

// �ܵ��˺��¼�
class BeDamageEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )		{ return EVENT_ID_ON_BE_DAMAGE;	}

protected:
};

// ��ɱ���¼�
class BeKilledEvent : public IEvent
{
public:
	virtual EVENT_ID ID( )		{ return EVENT_ID_ON_BE_KILLED;	}

protected:
};

// ��������������˺��¼�
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
	UINT	m_nObjID;			// ����˺��Ķ���ID
	UINT	m_nDamageType;		// �˺�����
	UINT	m_nDamageValue;		// �˺���ֵ
};

// ɱ�����������¼�
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