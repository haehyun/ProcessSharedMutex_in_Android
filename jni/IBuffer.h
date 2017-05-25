#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <utils/Timers.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

namespace android {

	class IBuffer: public IInterface
	{
		public:
			DECLARE_META_INTERFACE(Buffer);
			virtual sp<IMemoryHeap> getBuffer() = 0;
	};

	class BnBuffer: public BnInterface<IBuffer>
	{
		public:
			virtual status_t onTransact( uint32_t code,
	                                  const Parcel& data,
	                                  Parcel* reply,
	                                  uint32_t flags = 0);
	;

}; 
