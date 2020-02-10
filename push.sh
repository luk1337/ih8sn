#!/bin/bash

adb wait-for-device root
adb wait-for-device remount
adb wait-for-device push 60-ih8sn.sh /system/addon.d/
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push ih8sn.conf /system/etc/
adb wait-for-device push ih8sn.rc /system/etc/init/
