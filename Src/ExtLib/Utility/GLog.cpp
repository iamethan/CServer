#include "GLog.h"
#include <stdarg.h>
#include "GameUtil.h"

GLog g_Log;

GLog::GLog( const CHAR* fileName )
{
__ENTER_FUNCTION

	if( strlen(fileName) > LOG_FILE_NAME_MAX_SIZE )
	{
		Assert( false );
	}

	memset( m_LogName, 0, LOG_FILE_NAME_MAX_SIZE );
	strncpy( m_LogName, fileName, LOG_FILE_NAME_MAX_SIZE );

	for( INT i=0; i<LOG_LV_NUMBER; i++ )
	{
		m_LogCache[i] = NULL ;
		m_LogPos[i] = 0 ;
	}
	m_CacheSize = 0 ;
	m_DayTime= 0 ;

	Init();

__LEAVE_FUNCTION
}

GLog::~GLog( )
{
__ENTER_FUNCTION

	for( INT i=0; i<LOG_LV_NUMBER; i++ )
	{
		SAFE_DELETE_ARRAY(m_LogCache[i])  ;
	}
	m_CacheSize = 0 ;

__LEAVE_FUNCTION
}

BOOL GLog::Init( INT cachesize )
{
__ENTER_FUNCTION

	// 先清理旧数据
	if( m_CacheSize > 0 )
	{
		FlushLog_All();
		for( INT i=0; i<LOG_LV_NUMBER; i++ )
		{
			SAFE_DELETE_ARRAY(m_LogCache[i])  ;
		}
	}

	m_CacheSize = cachesize ;
	for( INT i=0; i<LOG_LV_NUMBER; i++ )
	{
		m_LogCache[i] = new CHAR[m_CacheSize] ;
		if( m_LogCache[i] == NULL )
		{
			return FALSE ;
		}
		m_LogPos[i] = 0 ;
	}

	m_DayTime = m_Time.GetDayTime();

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

void GLog::ChangeFileName( const CHAR* fileName )
{
__ENTER_FUNCTION

	FlushLog_All();

	if( strlen(fileName) > LOG_FILE_NAME_MAX_SIZE )
	{
		Assert( false );
	}

	memset( m_LogName, 0, LOG_FILE_NAME_MAX_SIZE );
	strncpy( m_LogName, fileName, LOG_FILE_NAME_MAX_SIZE );

__LEAVE_FUNCTION
}

VOID GLog::SaveLog( LOG_LV lv, CHAR* msg, ... )
{
__ENTER_FUNCTION

	if( lv<0 || lv >=LOG_LV_NUMBER )
		return ;

	// content
	CHAR buffer[2048];
	va_list argptr;

	try
	{
		va_start(argptr, msg);
		vsprintf(buffer,msg,argptr);
		va_end(argptr);

		strcat(buffer, "\r\n");
	}
	catch(...)
	{
		Assert(FALSE) ;
		return ;
	}

	INT iLen = (INT)strlen(buffer) ;
	if( iLen<=0 )
		return ;

	// time head
	CHAR szTime[128]={0} ;

	m_Time.SetTime();
	sprintf( szTime, "[%04d-%02d-%02d %02d:%02d:%02d] ", 
		m_Time.GetYear(),
		m_Time.GetMonth(),
		m_Time.GetDay(),
		m_Time.GetHour(),
		m_Time.GetMinute(),
		m_Time.GetSecond() ) ;

	INT iTimeLen = (INT)strlen(szTime);
	if( iTimeLen <=0 )
		return;

	//m_LogLock[lv].Lock() ;
	try
	{
		// copy head
		memcpy( m_LogCache[lv]+m_LogPos[lv], szTime, iTimeLen );

		// copy buffer
		memcpy( m_LogCache[lv]+m_LogPos[lv]+iTimeLen, buffer, iLen ) ;

		printf( "%s%s", szTime, buffer ) ;
	}
	catch(...)
	{
	}

	m_LogPos[lv] += (iLen + iTimeLen) ;
	//m_LogLock[lv].Unlock() ;

	//if( m_LogPos[lv] > (DEFAULT_LOG_CACHE_SIZE*2)/3 )
	{
		FlushLog( lv ) ;
	}
	return ;

__LEAVE_FUNCTION

	return ;
}

VOID GLog::FlushLog( LOG_LV lv )
{
__ENTER_FUNCTION

	CHAR szName[_MAX_PATH] ;
	GetLogName( lv, szName ) ;

	//m_LogLock[lv].Lock() ;
	try
	{
		FILE* f = fopen( szName, "ab" ) ;
		fwrite( m_LogCache[lv], 1, m_LogPos[lv], f ) ;
		fclose(f) ;
		m_LogPos[lv] = 0 ;
	}
	catch(...)
	{
	}
	//m_LogLock[lv].Unlock() ;
	return ;

__LEAVE_FUNCTION
}

VOID GLog::FlushLog_All( )
{
__ENTER_FUNCTION

	for( INT lv=0; lv<(INT)LOG_LV_NUMBER; ++lv )
	{
		FlushLog( (LOG_LV)lv ) ;
	}

__LEAVE_FUNCTION
}


VOID GLog::GetLogName( LOG_LV lv, CHAR* szName )
{
__ENTER_FUNCTION

	CHAR lvName[16];
	memset( lvName, 0, sizeof(lvName) );

	switch( lv )
	{
	case LOG_LV_NORMAL:
		strcpy(lvName, "normal");
		break;
	case LOG_LV_WARNING:
		strcpy(lvName, "warning");
	case LOG_LV_ERROR:
		strcpy(lvName, "error");
	case LOG_LV_DUMP:
		strcpy(lvName, "dump");
	};

	sprintf( szName, "%s_%s_%d_%d_%d.log", 
		m_LogName, lvName,
		m_Time.GetYear(),
		m_Time.GetMonth(),
		m_Time.GetDay()) ;

__LEAVE_FUNCTION
}