#ifndef __SCENE_H__
#define __SCENE_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include <map>
#include "Obj/Obj.h"

class Player;

// �뿪����ԭ��
enum LEAVE_SCENE_REASON
{
	LEAVE_SCENE_REASON_NORMAL = 0,	// �����뿪
	LEAVE_SCENE_REASON_DISCONNECT,	// ������뿪
};

class Scene
{
	typedef std::map< ObjID_t, Obj* >	ObjsMap;

public:
	Scene( );
	~Scene( );

	// ��ʼ������������Ϣ
	BOOL	Initialize( );
	BOOL	Finalize( );

	// ��������
	VOID		SceneID( SceneID_t nSceneID )	{ m_nSceneID = nSceneID;	}
	SceneID_t	SceneID( )						{ return m_nSceneID;		}

	// ��������
	BOOL		CheckEnterScene( Player* pPlayer );
	BOOL		CheckLeaveScene( Player* pPlayer );

	BOOL		EnterScene( Player* pPlayer );
	BOOL		LeaveScene( Player* pPlayer );

	// �������
	BOOL		AddObj( Obj* pObj );
	BOOL		DelObj( Obj* pObj );

	///////////////////////////////////////////////////////////////
	// ��Ϣ���
public:
	// �򵥸���ҷ�����Ϣ
	BOOL	SendPacket( BasePacket* pPacket, Player* pPlayer );

	// ��ĳ��������Χ�㲥��Ϣ
	BOOL	BroadCast( BasePacket* pPacket, Obj* pObj, BOOL bSendSelf = FALSE );

	// �򳡾���������ҹ㲥��Ϣ
	BOOL	BroadCast( BasePacket* pPacket );
		
	///////////////////////////////////////////////////////////////
	// �����¼�
public:
	VOID	OnSceneInit( );
	VOID	OnEnterScene( Obj* pObj );
	VOID	OnLeaveScene( Obj* pObj, LEAVE_SCENE_REASON eReason = LEAVE_SCENE_REASON_NORMAL );

private:
	SceneID_t	m_nSceneID;

	ObjsMap		m_mapObjs[OBJ_TYPE_COUNT];
};

#endif // __SCENE_H__