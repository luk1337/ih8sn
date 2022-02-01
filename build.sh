#!/bin/bash

set -e

export PATH=${PATH}:${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64/bin

CXX=${CXX:-aarch64-linux-android31-clang++}

${CXX} \
    -Iaosp/bionic/libc \
    -Iaosp/bionic/libc/async_safe/include \
    -Iaosp/bionic/libc/system_properties/include \
    -Iaosp/system/core/base/include \
    -Iaosp/system/core/property_service/libpropertyinfoparser/include \
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
    main.cpp \
    -static \
    -std=c++17 \
    -o ih8sn
