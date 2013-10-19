#ifndef  __ID_GENERATOR_H__
#define  __ID_GENERATOR_H__

#include "GLog.h"
#include "Assertx.h"
#include <set>

template <class T> 
class IDGenerator {
public:
	//will generate ID from [tStart, tEnd]
	IDGenerator(   const T tStart, 
		const T tEnd, 
		const T tNotAvailible);
	~IDGenerator();

	T GetUnusedID();
	T GetMaxUsedID() { 
		if( m_tStart == m_tNextAvailibleID) {
			return m_tNotAvailible;
		}
		else {
			return m_tNextAvailibleID-1;
		}
	}

	BOOL  IsIDUsed( const T tID );
	BOOL  RecycleID( const T tParam1 );
	BOOL  UseID( const T tParam1 );

protected:   
	std::set<T, std::less<T> >   m_setUnusedID;
	typedef typename std::set<T, std::less<T> >::iterator  _Set_It;
	typedef typename std::set<T, std::less<T> >::const_iterator  _Set_Con_It;

	T   m_tNextAvailibleID;
	T   m_tStart;
	T   m_tEnd;
	T   m_tNotAvailible;
};

template <class T>
IDGenerator<T>::IDGenerator( const T tStart, 
	const T tEnd, 
	const T tNotAvalilble)
	:  m_tNextAvailibleID( tStart ),
	m_tStart( tStart ),
	m_tEnd( tEnd ),
	m_tNotAvailible( tNotAvalilble )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

template<class T>
IDGenerator<T>::~IDGenerator()
{
__ENTER_FUNCTION

	_Set_It iter = m_setUnusedID.begin();
	_Set_It iterEnd = m_setUnusedID.end();
	_Set_It iterTmp;
	while( iter != iterEnd ) {
		iterTmp = iter++;
		m_setUnusedID.erase(iterTmp);      
	}

__LEAVE_FUNCTION
}

template <class T> 
BOOL IDGenerator<T>::IsIDUsed( const T t )
{
__ENTER_FUNCTION

	if( t >= m_tNextAvailibleID ) {
		return FALSE;
	}
	else {
		//check for unused ID
		if( m_setUnusedID.find( t ) == m_setUnusedID.end() ) {
			return FALSE;
		}
		else {
			return TRUE;
		}
	}

	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

//use a ID
template <class T> 
BOOL IDGenerator<T>::UseID( const T tParam1 )
{
__ENTER_FUNCTION

	if( tParam1 > m_tEnd || tParam1 < m_tStart || tParam1 == m_tNotAvailible || tParam1 > m_tEnd ) {
		g_Log.SaveLog( LOG_LV_ERROR, "IDGenerator<T>::UseID() fail!" );
		return FALSE;
	}

	if( tParam1 == m_tNextAvailibleID ) {
		m_tNextAvailibleID++;
		return TRUE;
	}
	else if( tParam1 > m_tNextAvailibleID ) {
		Assert( m_setUnusedID.find( tParam1 ) == m_setUnusedID.end() );
		T i;
		for( i=m_tNextAvailibleID; i<tParam1;i++ ) {
			m_setUnusedID.insert(i);
		}
		Assert( tParam1 < m_tEnd );
		m_tNextAvailibleID = tParam1+1;
		return TRUE;
	}
	else {
		_Set_It it;
		//find the id in unused id set
		if( (it = m_setUnusedID.find( tParam1 )) != m_setUnusedID.end() ) {
			m_setUnusedID.erase( it );
			return TRUE;
		}
		else {
			return FALSE;  
		}
	}

__LEAVE_FUNCTION

	return FALSE;
}

template <class T>
T IDGenerator<T>::GetUnusedID()
{
__ENTER_FUNCTION

	//is next id used up?
	if( m_tNextAvailibleID > m_tEnd ) {
		if( m_setUnusedID.empty() ) {
			g_Log.SaveLog( LOG_LV_ERROR, "IDGenerator::GetUnusedID() All ID has been used up" );
			return m_tNotAvailible;
		}
		else { //use recycled id
			_Set_It iter = m_setUnusedID.begin();
			T tReturn = *iter;
			m_setUnusedID.erase(iter);
			return tReturn;
		}
	}

	//no, we get next availible id
	T tReturn = m_tNextAvailibleID;
	m_tNextAvailibleID++;
	return tReturn;

__LEAVE_FUNCTION

	return m_tNotAvailible;
}

template <class T>
BOOL IDGenerator<T>::RecycleID( const T tParam1 )
{
__ENTER_FUNCTION

	m_setUnusedID.insert( tParam1 );
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

#endif // __ID_GENERATOR_H__


