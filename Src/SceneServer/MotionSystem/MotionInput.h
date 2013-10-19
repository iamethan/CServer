#ifndef __MOTION_INPUT_H__
#define __MOTION_INPUT_H__

#include "Utility.h"

class DynamicObj;

class MotionInput
{
public:
	// 移动到目标点
	static BOOL Motion( DynamicObj* pObj, WORLD_POS& tTarPos );

	// 瞬间传到目标点
	static BOOL MoveTo( DynamicObj* pObj, WORLD_POS& tTarPos );

	// 停止移动
	static BOOL Stop( DynamicObj* pObj );

	// 瞬移到起始点
	static BOOL GoStart( DynamicObj* pObj );
};

#endif // __MOTION_INPUT_H__