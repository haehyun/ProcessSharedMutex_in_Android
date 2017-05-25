#include <utils/Log.h>
#include <stdint.h>
#include <sys/types.h>
#include <binder/MemoryHeapBase.h>
#include "IBuffer.h"

namespace android {

enum {
    GET_BUFFER = IBinder::FIRST_CALL_TRANSACTION
};

class BpBuffer: public BpInterface<IBuffer>
{
public:
  BpBuffer(const sp<IBinder>& impl) : BpInterface<IBuffer>(impl)
    {
    }

  sp<IMemoryHeap> getBuffer()
  {
    Parcel data, reply;
    sp<IMemoryHeap> memHeap = NULL;
    data.writeInterfaceToken(IBuffer::getInterfaceDescriptor());
    remote()->transact(GET_BUFFER, data, &reply);
    memHeap = interface_cast<IMemoryHeap> (reply.readStrongBinder());
    return memHeap;
  }
};

IMPLEMENT_META_INTERFACE(Buffer, "android.vendor.IBuffer");


status_t BnBuffer::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
  switch (code)
  {
    case GET_BUFFER:
    {
      CHECK_INTERFACE(IBuffer, data, reply);
      sp<IMemoryHeap> Data = getBuffer();
      if (Data != NULL)
      {
        reply->writeStrongBinder(Data->asBinder());
      }
      return NO_ERROR;
      break;
    }
    default:
      return BBinder::onTransact(code, data, reply, flags);
  }
}

}; 