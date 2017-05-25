#include "IBuffer.h"
#include <binder/MemoryHeapBase.h>
#include <binder/IServiceManager.h>

namespace android {
static sp<IMemoryHeap> receiverMemBase;

unsigned int * getBufferMemPointer(void)
{
  static sp<IBuffer> Buffer = 0;

  /* Get the buffer service */
  if (Buffer == NULL)
  {
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
    binder = sm->getService(String16("sefcom.asu.Buffer"));
    if (binder != 0)
    {
      Buffer = IBuffer::asInterface(binder);
    }
  }
  if (Buffer == NULL)
  {
    printf("The Server is not published");
    return (unsigned int *)-1; /* return an errorcode... */
  }
  else
  {
    receiverMemBase = Buffer->getBuffer();
    return (unsigned int *) receiverMemBase->getBase();
  }
}

}

using namespace android;

int main(int argc, char** argv)
{
 // base could be on same address as Servers base but this
 // is purely by luck do NEVER rely on this. Linux memory
 // management may put it wherever it likes.
    unsigned int *base_data = getBufferMemPointer();
    int pshared = 0;
    int ret;
    pthread_mutex_t *mutex = (pthread_mutex_t *)(base_data +4);
    pthread_mutexattr_t *mattr = (pthread_mutexattr_t *)(base_data +8);

    if(base_data != (unsigned int *)-1)
    {
      printf("Client base=%p Data=0x%x\n",base_data, *base_data);
      ret = pthread_mutexattr_getpshared(mattr, &pshared);
      if(pshared==1){
        printf("mutex_attr = PTHREAD_PROCESS_SHARED\n");
      }
      else{
        printf("mutex_attr = PTHREAD_PROCESS_PRIVATE\n");
      }
      pthread_mutex_lock(mutex);
      *base_data = (*base_data)+1;
      printf("Client base=%p Data=0x%x CHANGED\n",base_data, *base_data);
      pthread_mutex_unlock(mutex);
      receiverMemBase = 0;
    }
    else
    {
     printf("Error shared memory not available\n");
    }
    return 0;
}
