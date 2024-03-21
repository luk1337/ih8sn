<div align="center">

# ih8sn

ih8sn is an after boot build.prop modification addon.

It allows you to modify your build.prop at runtime.

Your mileage may vary. Proceed at your own risk.

</div>

## Prerequisites

You'll need:

1. ADB installed and working with your device
2. A rom that allows root access from it's developer tools. Or another way to gain root access over ADB.

## Installation

### *Step 1: Download ih8sn*

ih8sn can be installed from any device you can ADB into your phone from.

Check the "Releases" section on the right.

Extract the zip file.

### *Step 2: \*Optional\* Configure ih8sn.conf*

You can optionally configure the ih8sn.conf with settings of your choosing that you want to replace for your build.prop. This may be required if the example does not work for your purposes.

You can look at your current build.prop file or that of a passing device for ideas of what you may need to tweak.

DEBUGGABLE=0 is recommended if not already in your build.prop.

### *Step 3: Push the files to your device*

Open the folder you extracted in Step 1 in a terminal window.
```
adb root
adb remount
```
Run the "push" script according to your system:
<details>
<summary>Windows</summary>

```
.\push.ps1
```
You may have to enable running of powershell commands first.
</details>

<details>
<summary>Linux</summary>

```
./push.sh
```
</details>

Alternatively run the commands below manually.
```
adb wait-for-device root
adb wait-for-device remount
adb wait-for-device push etc/60-ih8sn.sh /system/addon.d/
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push etc/ih8sn.rc /system/etc/init/
adb wait-for-device push etc/ih8sn.conf /system/etc/
```
Reboot your device
```
abd reboot
```

### *Step 4: Check your success*
See if the app your were trying to run works now.

Example:
Get a safetynet check app such as YASNAC from the Play Store.

Run the test and see the results.

If less than satisfactory modify the ih8sn.conf and push -> reboot -> check again.