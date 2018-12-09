LOCAL_PATH := $(call my-dir)



include $(CLEAR_VARS)

# calc
LOCAL_MODULE := calclient
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := Calclient.cpp

LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := libbinder libutils liblog

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

# calc
LOCAL_MODULE := testwfd
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := TestWfdService.cpp

LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := libbinder libutils liblog

include $(BUILD_EXECUTABLE)
