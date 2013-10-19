#ifndef __ENCODER_XOR_H__
#define __ENCODER_XOR_H__

#include "Encoder.h"

namespace Encode_Decode
{
	class EncoderXOR_T : public Encoder_T
	{
		public:
			EncoderXOR_T(VOID) {};
			~EncoderXOR_T(VOID) {};
			VOID Reset(VOID) {};
			virtual BOOL Encode(Encoder_T::Parameters_T& rParams) const;
			virtual BOOL Decode(Encoder_T::Parameters_T& rParams) const;
			virtual BOOL Skip(Parameters_T& rParams, INT nSize) const;
			virtual INT GetID(VOID) const {return ID;};
			enum
			{
				ID = Encoder_T::ENCODER_XOR,
			};
		protected:
		private:
			
			
	};
};
#endif //__ENCODER_XOR_H__
