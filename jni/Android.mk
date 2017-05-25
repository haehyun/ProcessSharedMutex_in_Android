LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

ANDROID_INCLUDE := $(LOCAL_PATH)/android/include
ANDROID_LIB := $(LOCAL_PATH)/android/lib

LOCAL_CFLAGS += -DHAVE_PTHREADS -DHAVE_SYS_UIO_H

LOCAL_C_INCLUDES += $(ANDROID_INCLUDE)/system/core/include
LOCAL_C_INCLUDES += $(ANDROID_INCLUDE)/frameworks/native/include

LOCAL_LDLIBS += -L$(ANDROID_LIB)
LOCAL_LDLIBS += -llog -lutils -lbinder

LOCAL_SRC_FILES:=        \
 Buffer.cpp      \
 Server.cpp \
 
LOCAL_MODULE := Server
include $(BUILD_EXECUTABLE)




include $(CLEAR_VARS)

ANDROID_INCLUDE := $(LOCAL_PATH)/android/include
ANDROID_LIB := $(LOCAL_PATH)/android/lib

LOCAL_CFLAGS += -DHAVE_PTHREADS -DHAVE_SYS_UIO_H

LOCAL_C_INCLUDES += $(ANDROID_INCLUDE)/system/core/include
LOCAL_C_INCLUDES += $(ANDROID_INCLUDE)/frameworks/native/include

LOCAL_LDLIBS += -L$(ANDROID_LIB)
LOCAL_LDLIBS += -llog -lutils -lbinder

LOCAL_SRC_FILES:=        \
 Buffer.cpp      \
 Client.cpp \

LOCAL_MODULE := Client
include $(BUILD_EXECUTABLE)
