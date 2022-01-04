LOCAL_PATH := $(call my-dir)

ifdef NDK_PROJECT_PATH

include $(CLEAR_VARS)
LOCAL_MODULE := ih8sn
LOCAL_C_INCLUDES := \
    aosp/bionic/libc \
    aosp/bionic/libc/async_safe/include \
    aosp/bionic/libc/system_properties/include \
    aosp/system/core/base/include \
    aosp/system/core/property_service/libpropertyinfoparser/include
LOCAL_SRC_FILES := \
    aosp/bionic/libc/bionic/system_property_api.cpp \
    aosp/bionic/libc/bionic/system_property_set.cpp \
    aosp/bionic/libc/system_properties/context_node.cpp \
    aosp/bionic/libc/system_properties/contexts_serialized.cpp \
    aosp/bionic/libc/system_properties/contexts_split.cpp \
    aosp/bionic/libc/system_properties/prop_area.cpp \
    aosp/bionic/libc/system_properties/prop_info.cpp \
    aosp/bionic/libc/system_properties/system_properties.cpp \
    aosp/system/core/base/strings.cpp \
    aosp/system/core/property_service/libpropertyinfoparser/property_info_parser.cpp \
    main.cpp
include $(BUILD_EXECUTABLE)

all: $(addprefix $(NDK_APP_LIBS_OUT)/$(TARGET_ARCH_ABI)/, 60-ih8sn.sh ih8sn.conf ih8sn.rc push.sh)

$(NDK_APP_LIBS_OUT)/$(TARGET_ARCH_ABI)/%: $(LOCAL_PATH)/%
	$(hide) cp $< $@

endif
