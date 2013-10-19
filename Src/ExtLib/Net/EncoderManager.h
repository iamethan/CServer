#ifndef __ENCODERMANAGER_H__
#define __ENCODERMANAGER_H__

#include "Encoder.h"
#include "Encoder_XOR.h"
#include "Utility.h"

using namespace Encode_Decode;
typedef InstanceManager_T<Encoder_T, Encoder_T::MAX_ID+1> EncoderManager_T;

template<>
	inline bool InstanceManager_T<Encoder_T, Encoder_T::MAX_ID+1>::Init(VOID)
{
	REGISTER_INSTANCE(EncoderXOR_T);
	return TRUE;
}
Encoder_T const* Encoder_GetInstanceByID(INT nID);


#endif // __ENCODERMANAGER_H__
