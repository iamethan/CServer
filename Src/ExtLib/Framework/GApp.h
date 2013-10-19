#ifndef __G_APP_H__
#define __G_APP_H__

#include "Utility.h"
#include "Net.h"
#include "GSystem.h"

#define GUTRUN_DEFAULT_RUNLOOP_RPS     30.0f	// 服务端默认帧数
#define GUTRUN_TIMER_CONTROL_INTERVAL  5.0f		// 打印当前帧数信息间隔

class GApp
{
public:
	GApp();
	virtual ~GApp();

	virtual BOOL Initialize( VOID );
	virtual BOOL Finalize( VOID );

	virtual VOID InitSystems( VOID ) = 0;
	virtual VOID InitPacketFactories( VOID ) = 0;

	BOOL    Quit( VOID )        { return m_bQuit;    }
	VOID    Quit( BOOL bQuit )  { m_bQuit = bQuit;   }

	// 开启服务
	virtual VOID Run( FLOAT fRPS=GUTRUN_DEFAULT_RUNLOOP_RPS );

	// 心跳函数
	virtual VOID HeartBeat( INT iSkip, FLOAT fTimePass ) {}

	// 输出RPS信息
	VOID	SetDumpRPSInterval( FLOAT fSeconds )  { m_Timer.Interval( fSeconds ); }
	VOID	DumpRPSInfo( BOOL bDump )             { m_bDumpRPSInfo = bDump; }
	BOOL	DumpRPSInfo( VOID )                   { return m_bDumpRPSInfo; };

	VOID	MaxRPS( FLOAT fRPS )    { m_fMaxRPS = fRPS; }
	FLOAT	MaxRPS( VOID ) const    { return m_fMaxRPS; }

	FLOAT	CurRPS( VOID ) const    { return m_fRPS; }
	FLOAT	CurAverageTimeUsedPerSec( VOID ) const       { return m_fAverageTimeUsedPerSec; }

	// 子系统
	BOOL	RegisterSystem( GSystem* pSys );

	// 获取系统指针
	StubManager*	GetStubManager( )		{ return &m_StubManager;	}

private:
	static VOID			__OnConnected( Stub* pStub );
	static VOID			__OnDisconnected( Stub* pStub );
	VOID				__Tick( INT iSkip, FLOAT fTimePass);

public:
	static GApp*	m_pApp;

protected:
	FLOAT			m_fMaxRPS; 
	FLOAT			m_fIntervalPerRun; 
	FLOAT			m_fRPS;                
	FLOAT			m_fAverageTimeUsedPerSec; 
	INT				m_iRuns;             
	INT				m_iTotalFrame;

	BOOL			m_bDumpRPSInfo;
	BOOL			m_bQuit;

	GTimer			m_Timer;

private:
	// sub systems
	SystemPtrMap	m_mapSystems;

	// stub manaer
	StubManager		m_StubManager;
};

extern GApp* GetApp();

#endif // __G_APP_H__