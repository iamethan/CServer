#include "Obj.h"
#include <math.h>

////////////////////////////////////////////////////////////////////
// DynamicObj

VOID DynamicObj::TarPos( WORLD_POS& tPos )
{
	if( m_tPos == tPos ) //equel, do not need move
	{
		return;
	}

	m_tTarPos = tPos;

	// update the direction
	m_fDir = MyAngle( &m_tPos, &m_tTarPos );

	g_Log.SaveLog( LOG_LV_NORMAL, "target:%0.2f, %0.2f\tdir:%0.2f", m_tTarPos.m_fX, m_tTarPos.m_fZ, m_fDir );

	// update move state
	MoveState( MOVE_STATE_MOTION );
}

VOID DynamicObj::TarPos( FLOAT fX, FLOAT fZ )
{
	TarPos( WORLD_POS(fX, fZ) );
}

VOID DynamicObj::HeartBeat( INT iSkip, FLOAT fTimePass)
{
	switch( m_eMoveState )
	{
	case MOVE_STATE_STATIC:
		break;
	case MOVE_STATE_MOTION:
	case MOVE_STATE_JUMP:
		{
			FLOAT fDistance = m_fSpeed * fTimePass;

			if( MyLengthSq(&m_tPos, &m_tTarPos) <= fDistance*fDistance )
			{
				m_tPos = m_tTarPos;
				g_Log.SaveLog( LOG_LV_NORMAL, "enter static" );
				MoveState( MOVE_STATE_STATIC );
				break;
			}

			m_tPos.m_fX = ::cos(fDistance) * fDistance;
			m_tPos.m_fZ = ::sin(fDistance) * fDistance;

			g_Log.SaveLog( LOG_LV_NORMAL, "moving:%0.2f, %0.2f", m_tPos.m_fX, m_tPos.m_fZ );
		}
		break;
	}
}