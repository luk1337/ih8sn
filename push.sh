#!/bin/bash

adb wait-for-device root
adb wait-for-device remount
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push ih8sn.rc /system/etc/init/
adb wait-for-device shell chcon u:object_r:sysinit_exec:s0 /system/bin/ih8sn
