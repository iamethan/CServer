#include "GApp.h"
#include "Event/Event.h"
#include "Event/EventManager.h"

GApp* GApp::m_pApp = NULL;

GApp* GetApp()
{
	return GApp::m_pApp;
}

GApp::GApp()
	: m_bQuit(FALSE)
	, m_fMaxRPS(GUTRUN_DEFAULT_RUNLOOP_RPS)
	, m_fIntervalPerRun(1.0f/GUTRUN_DEFAULT_RUNLOOP_RPS)
	, m_iRuns(0)
	, m_fRPS(0.0f)
	, m_iTotalFrame(0)
	, m_bDumpRPSInfo(TRUE)
{
__ENTER_FUNCTION

	m_pApp = this;

__LEAVE_FUNCTION
}

GApp::~GApp()
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

BOOL GApp::Initialize( VOID )
{
__ENTER_FUNCTION

	InitPacketFactories();
	g_Log.SaveLog( LOG_LV_NORMAL, "Initialized Packet Factories, total num<%d>",
		g_PacketFactoryManager.GetCount() );

	m_mapSystems.clear();
	InitSystems();
	g_Log.SaveLog( LOG_LV_NORMAL, "Initialized Systems, total num<%d>",
		m_mapSystems.size() );

	m_StubManager.SetConnectedPtr( GApp::__OnConnected );
	m_StubManager.SetDisconnectedPtr( GApp::__OnDisconnected );

	if( !m_StubManager.Init( 1231 ) )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "StubManager Init<%d> failed!", 1231 );
	}
	else
	{
		g_Log.SaveLog( LOG_LV_NORMAL, "StubManager Init Successed!" );
	}

	SystemPtrMap::iterator itEnd = m_mapSystems.end();
	for( SystemPtrMap::iterator it = m_mapSystems.begin(); it != itEnd; ++it )
	{
		g_Log.SaveLog( LOG_LV_NORMAL, "Initialize System<%s> ....", it->second->SystemName() );
		if( !it->second->__Initialize() )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "Initialize System<%s> failed!", it->second->SystemName() );
			continue;
		}
		
		g_Log.SaveLog( LOG_LV_NORMAL, "Initialize System<%s> successed!", it->second->SystemName() );
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL GApp::Finalize( VOID )
{
__ENTER_FUNCTION

	SystemPtrMap::iterator itEnd = m_mapSystems.end();
	for( SystemPtrMap::iterator it = m_mapSystems.begin(); it != itEnd; ++it )
	{
		g_Log.SaveLog( LOG_LV_NORMAL, "Finalize System<%s> ....", it->second->SystemName() );
		if( !it->second->__Finalize() )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "Finalize System<%s> failed!", it->second->SystemName() );
			continue;
		}
		
		g_Log.SaveLog( LOG_LV_NORMAL, "Finalize System<%s> successed!", it->second->SystemName() );
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID GApp::Run( FLOAT fRPS/*=GUTRUN_DEFAULT_RUNLOOP_RPS*/ )
{
__ENTER_FUNCTION

	m_fMaxRPS = fRPS;

	if( m_fMaxRPS <= 0.0f ) m_fIntervalPerRun = 0.0f;
	else m_fIntervalPerRun = 1.0f / m_fMaxRPS;

	g_TimeManager.Init();
	g_TimeManager.SetTime();

	m_Timer.Interval( GUTRUN_TIMER_CONTROL_INTERVAL );

	// Do block run and control runs per second
	FLOAT    fTimeStamp      = m_fIntervalPerRun;
	FLOAT    fTimeSlept      = 0.0f;
	FLOAT    fTimeToSleepS   = 0.0f;
	INT      iRuns           = 0;
	INT      iSkip           = 1;
	// Estimate process usage data
	FLOAT    fTimeSleep      = 0.0f;
	// log burst frame
	FLOAT    fMaxExceedTime  = 999.0f;
	INT		iBurstFrame     = 0;

	m_Timer.Reset();

	// tick timer
	GTimer	tickTimer;
	tickTimer.Reset();

	while( m_bQuit == FALSE ) 
	{
		// Calculate how long time can sleep
		fTimeToSleepS = fTimeStamp - m_Timer.Seconds();

		// log maximun exceed time
		if( fTimeToSleepS < fMaxExceedTime ) 
		{
			fMaxExceedTime = fTimeToSleepS;
			iBurstFrame    = iRuns;
		}

		// Do Sleep & Count sleep rate 
		iSkip = 1;
		if( fTimeToSleepS > 0.001f ) 
		{
			MySleep( (UINT)(fTimeToSleepS * 1000) );
			fTimeSleep  += fTimeToSleepS;
		}
		else 
		{
			iSkip += (INT)( -fTimeToSleepS / m_fIntervalPerRun );
		}

		// Calculate next time stamp
		fTimeStamp  += m_fIntervalPerRun * iSkip;

		// Tick
		__Tick( iSkip, tickTimer.Seconds() );
		tickTimer.Reset( );

		// Increase run times
		++iRuns;

		// Calculate RPS
		const FLOAT fTimePeriod = m_Timer.Seconds();
		if( fTimePeriod > 0.1f )
		{
			m_fRPS = ((FLOAT)iRuns) / fTimePeriod;
		}

		// Reset timer if on time
		if( fTimePeriod >= m_Timer.Interval() ) 
		{        
			// Calculate Time Used
			m_fAverageTimeUsedPerSec = 1.0f - fTimeSlept / fTimePeriod;

			if( DumpRPSInfo() )
			{
				FLOAT fAvgSleep = 0.0f;
				if( fTimeSleep && fTimeStamp ) fAvgSleep = fTimeSleep / fTimeStamp;

				// Show system time & RPS
				g_Log.SaveLog( LOG_LV_NORMAL, "AppRun Info:  RPS<%.2f>", 
					m_fRPS );
			}

			// Reset timer & data
			m_Timer.Reset();
			fTimeStamp = m_fIntervalPerRun;
			iRuns      = 0;

			// Reset sleep ratio data
			fTimeSleep = 0.0f;
			fTimeSlept = 0.0f;

			fMaxExceedTime = 999.0f;
			iBurstFrame    = 0;
		}
	}

__LEAVE_FUNCTION
}

VOID GApp::__Tick( INT iSkip, FLOAT fTimePass )
{
__ENTER_FUNCTION

	// stub manager tick
	m_StubManager.Tick( iSkip, fTimePass );

	// app heart beat
	HeartBeat( iSkip, fTimePass );
	
	// sub systems tick
	SystemPtrMap::iterator itEnd = m_mapSystems.end();
	for( SystemPtrMap::iterator it = m_mapSystems.begin(); it != m_mapSystems.end(); ++it )
	{
		it->second->HeartBeat( iSkip, fTimePass );
	}

__LEAVE_FUNCTION
}

BOOL GApp::RegisterSystem( GSystem* pSys )
{
__ENTER_FUNCTION

	SystemPtrMap::iterator it = m_mapSystems.find( pSys->SystemID() );
	if( it != m_mapSystems.end() )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "GApp::RegisterSystem<%d, %s> Error, duplicated id",
			pSys->SystemID(), pSys->SystemName() );
		return FALSE;
	}

	if( !m_mapSystems.insert( SystemPtrMap::value_type( pSys->SystemID(), pSys ) ).second )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "GApp::RegisterSystem<%d, %s> Error when insert into map",
			pSys->SystemID(), pSys->SystemName() );
		return FALSE;
	}

	g_Log.SaveLog( LOG_LV_NORMAL, "Register System<%s> Successed!", pSys->SystemName() );

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID GApp::__OnConnected( Stub* pStub )
{
__ENTER_FUNCTION

	SendConnectedEvent( pStub );

__LEAVE_FUNCTION
}

VOID GApp::__OnDisconnected( Stub* pStub )
{
__ENTER_FUNCTION

	SendDisconnectedEvent( pStub );

__LEAVE_FUNCTION
}