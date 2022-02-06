#!/usr/bin/env pwsh

param(
    [switch]$use_remount = $false
)

adb wait-for-device root
adb wait-for-device shell "mount | grep -q ^tmpfs\ on\ /system && umount -fl /system/{bin,etc} 2>/dev/null"
if ($use_remount) {
    adb wait-for-device shell "remount"
} else {
    adb wait-for-device shell "stat --format %m /system | xargs mount -o rw,remount"
}
adb wait-for-device push 60-ih8sn.sh /system/addon.d/
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push ih8sn.rc /system/etc/init/

$serialno = adb shell getprop ro.boot.serialno
$product = adb shell getprop ro.build.product

if (Test-Path "ih8sn.conf.${serialno}" -PathType leaf) {
    adb wait-for-device push ih8sn.conf.${serialno} /system/etc/ih8sn.conf
} elseif (Test-Path "ih8sn.conf.${product}" -PathType leaf) {
    adb wait-for-device push ih8sn.conf.${product} /system/etc/ih8sn.conf
} else {
    adb wait-for-device push ih8sn.conf /system/etc/
}
