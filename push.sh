#!/bin/bash

while getopts ":-:" o; do
    case "${OPTARG}" in
        reboot)
            REBOOT=1
            ;;
        use_remount)
            USE_REMOUNT=1
            ;;
    esac
done

adb wait-for-device root
adb wait-for-device shell "mount | grep -q ^tmpfs\ on\ /system && umount -fl /system/{bin,etc} 2>/dev/null"
if [[ "${USE_REMOUNT}" = "1" ]]; then
    adb wait-for-device shell "remount"
elif [[ "$(adb shell stat -f --format %a /system)" = "0" ]]; then
    echo "ERROR: /system has 0 available blocks, consider using --use_remount"
    exit -1
else
    adb wait-for-device shell "stat --format %m /system | xargs mount -o rw,remount"
fi
adb wait-for-device push 60-ih8sn.sh /system/addon.d/
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push ih8sn.rc /system/etc/init/

SERIALNO=$(adb shell getprop ro.boot.serialno)
PRODUCT=$(adb shell getprop ro.build.product)

if [[ -f "ih8sn.conf.${SERIALNO}" ]]; then
    adb wait-for-device push ih8sn.conf.${SERIALNO} /system/etc/ih8sn.conf
elif [[ -f "ih8sn.conf.${PRODUCT}" ]]; then
    adb wait-for-device push ih8sn.conf.${PRODUCT} /system/etc/ih8sn.conf
else
    adb wait-for-device push ih8sn.conf /system/etc/
fi

if [[ "${REBOOT}" = "1" ]]; then
    adb wait-for-device reboot
fi
