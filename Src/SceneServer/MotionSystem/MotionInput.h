#ifndef __MOTION_INPUT_H__
#define __MOTION_INPUT_H__

#include "Utility.h"

class DynamicObj;

class MotionInput
{
public:
	// �ƶ���Ŀ���
	static BOOL Motion( DynamicObj* pObj, WORLD_POS& tTarPos );

	// ˲�䴫��Ŀ���
	static BOOL MoveTo( DynamicObj* pObj, WORLD_POS& tTarPos );

	// ֹͣ�ƶ�
	static BOOL Stop( DynamicObj* pObj );

	// ˲�Ƶ���ʼ��
	static BOOL GoStart( DynamicObj* pObj );
};

#endif // __MOTION_INPUT_H__