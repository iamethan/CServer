#ifndef __G_LOG_H__
#define __G_LOG_H__

#include "Type.h"
#include "File.h"
#include "TimeManager.h"

enum LOG_LV
{
	LOG_LV_NORMAL = 0 ,
	LOG_LV_WARNING ,
	LOG_LV_ERROR ,
	LOG_LV_DUMP ,

	LOG_LV_NUMBER ,
};

#define DEFAULT_LOG_CACHE_SIZE 1024*1024*4
#define LOG_BUFF_TEMP 4096
#define LOG_NAME_TEMP 128
#define LOG_FILE_NAME_MAX_SIZE	128

class GLog
{
public :
	GLog( const CHAR* fileName = "default" ) ;
	~GLog( ) ;

	BOOL			Init( INT cachesize=DEFAULT_LOG_CACHE_SIZE ) ;

	void			ChangeFileName( const CHAR* fileName );

	//����־����д����־��Ϣ
	VOID			SaveLog( LOG_LV lv, CHAR* msg, ... ) ;

	//����־�ڴ�����д���ļ�
	VOID			FlushLog( LOG_LV lv ) ;

	//ȡ����־��Ч���ݴ�С
	INT				GetLogSize( LOG_LV lv ){ return m_LogPos[lv] ; }

	//ȡ�ñ�����־���ļ�����
	VOID			GetLogName( LOG_LV lv, CHAR* szName ) ;

	//ˢ��ÿ����־�ļ�
	VOID			FlushLog_All( ) ;

	//ȡ����������
	UINT			GetDayTime( ){ return m_DayTime ; }
	//������������
	VOID			SetDayTime( UINT daytime ){ m_DayTime = daytime ; }

private :
	CHAR*			m_LogCache[LOG_LV_NUMBER] ;	//��־�ڴ���
	INT				m_LogPos[LOG_LV_NUMBER] ;		//��־��ǰ��Ч����λ��
	MyLock			m_LogLock[LOG_LV_NUMBER] ;	//��־��д��
	INT				m_CacheSize ;
	UINT			m_DayTime ;

	CHAR			m_LogName[LOG_FILE_NAME_MAX_SIZE];

	TimeManager		m_Time;
};

extern GLog g_Log;

#if defined __LINUX__
	#define SaveCodeLog()	(g_Log.SaveLog( LOG_LV_ERROR, "%s %d %s", __FILE__,__LINE__,__PRETTY_FUNCTION__ ))
#else
	#define SaveCodeLog()	(g_Log.SaveLog( LOG_LV_ERROR, "%s %d %s", __FILE__,__LINE__,__FUNCTION__ ))
#endif

#endif // __G_LOG_H__
