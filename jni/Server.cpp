#include "IBuffer.h"
#include <binder/MemoryHeapBase.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

namespace android {

#define MEMORY_SIZE 10*1024  

class BufferService : public BnBuffer {
public:
  static void instantiate();
  BufferService();
  virtual ~BufferService();
  virtual sp<IMemoryHeap> getBuffer();
private:
  sp<MemoryHeapBase> mMemHeap;
};

sp<IMemoryHeap> BufferService::getBuffer()
{
  return mMemHeap;
}

void BufferService::instantiate()
{
  status_t status;
  status = defaultServiceManager()->addService(String16("msec.ssu.Buffer"), new BufferService());
}

BufferService::BufferService()
{
  mMemHeap = new MemoryHeapBase(MEMORY_SIZE);
  unsigned int *base = (unsigned int *) mMemHeap->getBase();
  *base=0x00000000; 
}

BufferService::~BufferService()
{
  mMemHeap = 0;
}


static sp<IMemoryHeap> receiverMemBase;

unsigned int * getBufferMemPointer(void)
{
  static sp<IBuffer> eneaBuffer;

  /* Get the buffer service */
  if (eneaBuffer == NULL)
  {
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
    binder = sm->getService(String16("msec.ssu.Buffer"));
    if (binder != 0)
    {
      eneaBuffer = IBuffer::asInterface(binder);
    }
  }
  if (eneaBuffer == NULL)
  {
    printf("The buffer service is not published");
    return (unsigned int *)-1; 
  }
  else
  {
    receiverMemBase = eneaBuffer->getBuffer();
    return (unsigned int *) receiverMemBase->getBase();
  }
}


}

using namespace android;

int main(int argc, char** argv)
{
    unsigned int *base_data;

    BufferService::instantiate();

    ProcessState::self()->startThreadPool();
    printf("Server is up and running");

    base_data = getBufferMemPointer();

    pthread_mutex_t *mutex = (pthread_mutex_t *)(base_data +4);
    pthread_mutexattr_t *mattr = (pthread_mutexattr_t *)(base_data +8);
    pthread_mutexattr_init(mattr);
    pthread_mutexattr_setpshared(mattr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init (mutex, mattr);

    for(;;)
    {
     printf("Server base=%p Data=0x%x \n", base_data,*base_data);
     sleep(3);
    }

    //IPCThreadState::self()->joinThreadPool();
    return 0;
}