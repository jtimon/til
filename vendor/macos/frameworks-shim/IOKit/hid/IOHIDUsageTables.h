/* SDK-less shim for <IOKit/hid/IOHIDUsageTables.h> (issue #25 / #232).
 *
 * These are the public USB HID Usage Table constants (HID Usage Tables
 * spec), which Apple's real header just mirrors. Only the pages/usages
 * that raylib's RGFW backend + minigamepad reference are defined here --
 * enough to COMPILE the mac gamepad code on Linux; the actual IOKit calls
 * bind at runtime on a real mac via the IOKit .tbd stub. Values are the
 * standard HID ones and are ABI-stable.
 */
#ifndef _TIL_SHIM_IOHIDUSAGETABLES_H
#define _TIL_SHIM_IOHIDUSAGETABLES_H

/* Usage pages */
#define kHIDPage_GenericDesktop         0x01
#define kHIDPage_Button                 0x09

/* Generic Desktop Page (0x01) usages */
#define kHIDUsage_GD_Joystick           0x04
#define kHIDUsage_GD_GamePad            0x05
#define kHIDUsage_GD_MultiAxisController 0x08
#define kHIDUsage_GD_X                  0x30
#define kHIDUsage_GD_Y                  0x31
#define kHIDUsage_GD_Z                  0x32
#define kHIDUsage_GD_Rx                 0x33
#define kHIDUsage_GD_Ry                 0x34
#define kHIDUsage_GD_Rz                 0x35
#define kHIDUsage_GD_Start              0x3D
#define kHIDUsage_GD_Select             0x3E
#define kHIDUsage_GD_SystemMainMenu     0x86
#define kHIDUsage_GD_DPadUp             0x90
#define kHIDUsage_GD_DPadDown           0x91
#define kHIDUsage_GD_DPadRight          0x92
#define kHIDUsage_GD_DPadLeft           0x93

/* Button Page (0x09) usages */
#define kHIDUsage_Button_1              0x01
#define kHIDUsage_Button_2              0x02
#define kHIDUsage_Button_3              0x03
#define kHIDUsage_Button_4              0x04
#define kHIDUsage_Button_5              0x05
#define kHIDUsage_Button_6              0x06
#define kHIDUsage_Button_7              0x07
#define kHIDUsage_Button_8              0x08
#define kHIDUsage_Button_9              0x09
#define kHIDUsage_Button_10             0x0A

#endif /* _TIL_SHIM_IOHIDUSAGETABLES_H */
