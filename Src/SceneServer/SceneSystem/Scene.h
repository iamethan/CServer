#ifndef __SCENE_H__
#define __SCENE_H__

#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include <map>
#include "Obj/Obj.h"

class Player;

// 离开场景原因
enum LEAVE_SCENE_REASON
{
	LEAVE_SCENE_REASON_NORMAL = 0,	// 正常离开
	LEAVE_SCENE_REASON_DISCONNECT,	// 因断线离开
};

class Scene
{
	typedef std::map< ObjID_t, Obj* >	ObjsMap;

public:
	Scene( );
	~Scene( );

	// 初始化场景数据信息
	BOOL	Initialize( );
	BOOL	Finalize( );

	// 场景属性
	VOID		SceneID( SceneID_t nSceneID )	{ m_nSceneID = nSceneID;	}
	SceneID_t	SceneID( )						{ return m_nSceneID;		}

	// 场景操作
	BOOL		CheckEnterScene( Player* pPlayer );
	BOOL		CheckLeaveScene( Player* pPlayer );

	BOOL		EnterScene( Player* pPlayer );
	BOOL		LeaveScene( Player* pPlayer );

	// 对象管理
	BOOL		AddObj( Obj* pObj );
	BOOL		DelObj( Obj* pObj );

	///////////////////////////////////////////////////////////////
	// 消息相关
public:
	// 向单个玩家发送消息
	BOOL	SendPacket( BasePacket* pPacket, Player* pPlayer );

	// 向某个对象周围广播消息
	BOOL	BroadCast( BasePacket* pPacket, Obj* pObj, BOOL bSendSelf = FALSE );

	// 向场景内所有玩家广播消息
	BOOL	BroadCast( BasePacket* pPacket );
		
	///////////////////////////////////////////////////////////////
	// 场景事件
public:
	VOID	OnSceneInit( );
	VOID	OnEnterScene( Obj* pObj );
	VOID	OnLeaveScene( Obj* pObj, LEAVE_SCENE_REASON eReason = LEAVE_SCENE_REASON_NORMAL );

private:
	SceneID_t	m_nSceneID;

	ObjsMap		m_mapObjs[OBJ_TYPE_COUNT];
};

#endif // __SCENE_H__