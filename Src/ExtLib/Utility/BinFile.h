#ifndef __BIN_FILE_H__
#define __BIN_FILE_H__

#include "File.h"
#include "GLog.h"

template < typename T >
class BinFile
{
public:
	BinFile( );
	BinFile( const CHAR* sFileName );

	~BinFile( );

	BOOL	Open( const CHAR* sFileName );

	VOID	Close( );

	UINT	GetCount( )		{ return m_nCount;								}
	T*		GetHeader( )	{ return (m_nCount>0) ? m_ppHeader[0] : NULL ;	}

private:
	T**		m_ppHeader;
	UINT	m_nCount;
	FILE*	m_pFile;
};

template< typename T >
BinFile< T >::BinFile( )
{
	m_ppHeader = NULL;
	m_nCount = 0;
	m_pFile = NULL;
}

template< typename T >
BinFile< T >::BinFile( const CHAR* sFileName )
{
	Open( sFileName );
}

template< typename T >
BinFile< T >::~BinFile( )
{
	Close( );
}

template< typename T >
BOOL BinFile< T >::Open( const CHAR* sFileName )
{
__ENTER_FUNCTION

	if( m_nCount > 0 )
	{
		Close( );
	}

	m_pFile = fopen( sFileName, "rb" );
	if( !m_pFile )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "open bin file<%s> failed!",
			sFileName );
		return FALSE;
	}

	USHORT nBlockSize = 0;
	USHORT nBlockCount = 0;
	UINT nReadLen = 0;

	// read block size
	nReadLen = fread( &nBlockSize, sizeof(nBlockSize), 1, m_pFile );
	if( nReadLen <= 0 )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "read bin file<%s> failed, when read block size!",
			sFileName );
		return FALSE;
	}

	// read block count
	nReadLen = fread( &nBlockCount, sizeof(nBlockCount), 1, m_pFile );
	if( nReadLen <= 0 )
	{
		g_Log.SaveLog( LOG_LV_ERROR, "read bin file<%s> failed, when read block count!",
			sFileName );
		return FALSE;
	}

	m_ppHeader = new T*[nBlockCount];
	m_nCount = 0;

	// read block content
	for( USHORT i=0; i<nBlockCount; ++i )
	{
		T* pT = new T;

		nReadLen = fread( pT, sizeof(T), 1, m_pFile );
		
		if( nReadLen <= 0 )
		{
			g_Log.SaveLog( LOG_LV_ERROR, "read bin file<%s> failed, when read block<%d> content",
				sFileName, i );
			SAFE_DELETE( pT );
			Close( );
			return FALSE;
		}

		m_ppHeader[i] = pT;
		++m_nCount;
	}

	fclose( m_pFile );
	m_pFile = NULL;

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

template< typename T >
VOID BinFile< T >::Close( )
{
__ENTER_FUNCTION

	if( m_pFile )
	{
		fclose( m_pFile );
		m_pFile = NULL;
	}

	for( UINT i=0; i<m_nCount; ++i )
	{
		T* pT = m_ppHeader[i];
		SAFE_DELETE( pT );
	}

	SAFE_DELETE_ARRAY( m_ppHeader );

	m_nCount = 0;

__LEAVE_FUNCTION
}

#endif // __BIN_FILE_H__