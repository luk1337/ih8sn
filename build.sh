#!/bin/bash

set -e

${ANDROID_NDK_HOME}/ndk-build \
    NDK_PROJECT_PATH=. \
    NDK_APPLICATION_MK=Application.mk \
    NDK_APP_OUT=out/obj \
    NDK_LIBS_OUT=out/target
