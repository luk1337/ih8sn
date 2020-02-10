#!/bin/bash

adb wait-for-device root
adb wait-for-device remount
adb wait-for-device push 60-ih8sn.sh /system/addon.d/
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push ih8sn.rc /system/etc/init/

SERIALNO=$(adb shell getprop ro.boot.serialno)

if [[ -f "ih8sn.conf.${SERIALNO}" ]]; then
    adb wait-for-device push ih8sn.conf.${SERIALNO} /system/etc/ih8sn.conf
else
    adb wait-for-device push ih8sn.conf /system/etc/
fi
