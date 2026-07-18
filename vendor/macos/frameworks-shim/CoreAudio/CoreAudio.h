/* SDK-less shim for <CoreAudio/CoreAudio.h> (issue #25 / #232).
 * The CoreAudio types + AudioObject/hardware API miniaudio (raylib's
 * raudio backend) uses. miniaudio runtime-links the actual functions
 * (dlopen), but uses these struct/type definitions directly, so the
 * layouts are the documented, ABI-stable CoreAudio ones. Functions that
 * are referenced directly bind at runtime via the CoreAudio .tbd stub. */
#ifndef _TIL_SHIM_COREAUDIO_H
#define _TIL_SHIM_COREAUDIO_H

#include <stdint.h>
#include <CoreFoundation/CoreFoundation.h>

typedef float  Float32;
typedef double Float64;
#ifndef _TIL_SHIM_OSSTATUS
#define _TIL_SHIM_OSSTATUS
typedef SInt32 OSStatus;
#endif
typedef uint64_t UInt64;
typedef int16_t  SInt16;

/* --- CoreAudioTypes --- */
typedef UInt32 AudioFormatID;
typedef UInt32 AudioFormatFlags;

typedef struct AudioStreamBasicDescription {
    Float64          mSampleRate;
    AudioFormatID    mFormatID;
    AudioFormatFlags mFormatFlags;
    UInt32           mBytesPerPacket;
    UInt32           mFramesPerPacket;
    UInt32           mBytesPerFrame;
    UInt32           mChannelsPerFrame;
    UInt32           mBitsPerChannel;
    UInt32           mReserved;
} AudioStreamBasicDescription;

typedef struct AudioValueRange {
    Float64 mMinimum;
    Float64 mMaximum;
} AudioValueRange;

typedef struct AudioStreamRangedDescription {
    AudioStreamBasicDescription mFormat;
    AudioValueRange             mSampleRateRange;
} AudioStreamRangedDescription;

typedef struct AudioBuffer {
    UInt32 mNumberChannels;
    UInt32 mDataByteSize;
    void  *mData;
} AudioBuffer;

typedef struct AudioBufferList {
    UInt32      mNumberBuffers;
    AudioBuffer mBuffers[1];
} AudioBufferList;

typedef struct SMPTETime {
    SInt16 mSubframes;
    SInt16 mSubframeDivisor;
    UInt32 mCounter;
    UInt32 mType;
    UInt32 mFlags;
    SInt16 mHours;
    SInt16 mMinutes;
    SInt16 mSeconds;
    SInt16 mFrames;
} SMPTETime;

typedef struct AudioTimeStamp {
    Float64   mSampleTime;
    UInt64    mHostTime;
    Float64   mRateScalar;
    UInt64    mWordClockTime;
    SMPTETime mSMPTETime;
    UInt32    mFlags;
    UInt32    mReserved;
} AudioTimeStamp;

typedef UInt32 AudioChannelLabel;
typedef UInt32 AudioChannelLayoutTag;
typedef UInt32 AudioChannelBitmap;
typedef UInt32 AudioChannelFlags;

typedef struct AudioChannelDescription {
    AudioChannelLabel mChannelLabel;
    AudioChannelFlags mChannelFlags;
    Float32           mCoordinates[3];
} AudioChannelDescription;

typedef struct AudioChannelLayout {
    AudioChannelLayoutTag   mChannelLayoutTag;
    AudioChannelBitmap      mChannelBitmap;
    UInt32                  mNumberChannelDescriptions;
    AudioChannelDescription mChannelDescriptions[1];
} AudioChannelLayout;

/* FourCharCode format constants (public, stable). */
#define kAudioFormatLinearPCM            0x6C70636D /* 'lpcm' */
enum {
    kAudioFormatFlagIsFloat          = (1u << 0),
    kAudioFormatFlagIsBigEndian      = (1u << 1),
    kAudioFormatFlagIsSignedInteger  = (1u << 2),
    kAudioFormatFlagIsPacked         = (1u << 3),
    kAudioFormatFlagIsAlignedHigh    = (1u << 4),
    kAudioFormatFlagIsNonInterleaved = (1u << 5),
    kAudioFormatFlagIsNonMixable     = (1u << 6)
};

/* --- AudioHardware / AudioObject --- */
typedef UInt32 AudioObjectID;
typedef UInt32 AudioDeviceID;
typedef UInt32 AudioObjectPropertySelector;
typedef UInt32 AudioObjectPropertyScope;
typedef UInt32 AudioObjectPropertyElement;

typedef struct AudioObjectPropertyAddress {
    AudioObjectPropertySelector mSelector;
    AudioObjectPropertyScope    mScope;
    AudioObjectPropertyElement  mElement;
} AudioObjectPropertyAddress;

typedef OSStatus (*AudioObjectPropertyListenerProc)(AudioObjectID inObjectID,
    UInt32 inNumberAddresses, const AudioObjectPropertyAddress *inAddresses, void *inClientData);

enum {
    kAudioObjectSystemObject                 = 1,
    kAudioObjectPropertyScopeGlobal          = 0x676C6F62, /* 'glob' */
    kAudioObjectPropertyScopeInput           = 0x696E7074, /* 'inpt' */
    kAudioObjectPropertyScopeOutput          = 0x6F757470, /* 'outp' */
    kAudioObjectPropertyElementMaster        = 0,
    kAudioObjectPropertyElementMain          = 0
};

OSStatus AudioObjectGetPropertyData(AudioObjectID inObjectID, const AudioObjectPropertyAddress *inAddress,
    UInt32 inQualifierDataSize, const void *inQualifierData, UInt32 *ioDataSize, void *outData);
OSStatus AudioObjectGetPropertyDataSize(AudioObjectID inObjectID, const AudioObjectPropertyAddress *inAddress,
    UInt32 inQualifierDataSize, const void *inQualifierData, UInt32 *outDataSize);
OSStatus AudioObjectSetPropertyData(AudioObjectID inObjectID, const AudioObjectPropertyAddress *inAddress,
    UInt32 inQualifierDataSize, const void *inQualifierData, UInt32 inDataSize, const void *inData);
OSStatus AudioObjectAddPropertyListener(AudioObjectID inObjectID, const AudioObjectPropertyAddress *inAddress,
    AudioObjectPropertyListenerProc inListener, void *inClientData);
OSStatus AudioObjectRemovePropertyListener(AudioObjectID inObjectID, const AudioObjectPropertyAddress *inAddress,
    AudioObjectPropertyListenerProc inListener, void *inClientData);

#ifndef noErr
#define noErr 0
#endif

/* FourCharCode helper (avoids implementation-defined multi-char literals). */
#define _TIL_FCC(a,b,c,d) ((UInt32)(((unsigned)(a)<<24)|((unsigned)(b)<<16)|((unsigned)(c)<<8)|(unsigned)(d)))

/* LinearPCM flag aliases (same bit values as the generic format flags). */
#define kLinearPCMFormatFlagIsFloat         kAudioFormatFlagIsFloat
#define kLinearPCMFormatFlagIsSignedInteger kAudioFormatFlagIsSignedInteger
#define kLinearPCMFormatFlagIsAlignedHigh   kAudioFormatFlagIsAlignedHigh

/* AudioHardware / AudioDevice property selectors + error codes. */
enum {
    kAudioHardwarePropertyDevices                    = _TIL_FCC('d','e','v','#'),
    kAudioHardwarePropertyDefaultInputDevice         = _TIL_FCC('d','I','n',' '),
    kAudioHardwarePropertyDefaultOutputDevice        = _TIL_FCC('d','O','u','t'),
    kAudioDevicePropertyDeviceUID                    = _TIL_FCC('u','i','d',' '),
    kAudioDevicePropertyDeviceNameCFString           = _TIL_FCC('l','n','a','m'),
    kAudioDevicePropertyNominalSampleRate            = _TIL_FCC('n','s','r','t'),
    kAudioDevicePropertyAvailableNominalSampleRates  = _TIL_FCC('n','s','r','#'),
    kAudioDevicePropertyStreamConfiguration          = _TIL_FCC('s','l','a','y'),
    kAudioDevicePropertyPreferredChannelLayout       = _TIL_FCC('s','r','n','d'),
    kAudioDevicePropertyBufferFrameSize              = _TIL_FCC('f','s','i','z'),
    kAudioDevicePropertyBufferFrameSizeRange         = _TIL_FCC('f','s','z','#'),
    kAudioStreamPropertyAvailableVirtualFormats      = _TIL_FCC('v','f','m','a')
};
enum {
    kAudioHardwareNoError                   = 0,
    kAudioHardwareNotRunningError           = _TIL_FCC('s','t','o','p'),
    kAudioHardwareUnspecifiedError          = _TIL_FCC('w','h','a','t'),
    kAudioHardwareUnknownPropertyError      = _TIL_FCC('w','h','o','?'),
    kAudioHardwareBadPropertySizeError      = _TIL_FCC('!','s','i','z'),
    kAudioHardwareIllegalOperationError     = _TIL_FCC('n','o','p','e'),
    kAudioHardwareBadObjectError            = _TIL_FCC('!','o','b','j'),
    kAudioHardwareBadDeviceError            = _TIL_FCC('!','d','e','v'),
    kAudioHardwareBadStreamError            = _TIL_FCC('!','s','t','r'),
    kAudioHardwareUnsupportedOperationError = _TIL_FCC('u','n','o','p'),
    kAudioDeviceUnsupportedFormatError      = _TIL_FCC('!','d','a','t'),
    kAudioDevicePermissionsError            = _TIL_FCC('!','h','o','g')
};

/* AudioChannelLabel (standard CoreAudio values). */
enum {
    kAudioChannelLabel_Unknown = 0xFFFFFFFF, kAudioChannelLabel_Unused = 0,
    kAudioChannelLabel_UseCoordinates = 100,
    kAudioChannelLabel_Left = 1, kAudioChannelLabel_Right = 2, kAudioChannelLabel_Center = 3,
    kAudioChannelLabel_LFEScreen = 4, kAudioChannelLabel_LeftSurround = 5, kAudioChannelLabel_RightSurround = 6,
    kAudioChannelLabel_LeftCenter = 7, kAudioChannelLabel_RightCenter = 8, kAudioChannelLabel_CenterSurround = 9,
    kAudioChannelLabel_LeftSurroundDirect = 10, kAudioChannelLabel_RightSurroundDirect = 11,
    kAudioChannelLabel_TopCenterSurround = 12, kAudioChannelLabel_VerticalHeightLeft = 13,
    kAudioChannelLabel_VerticalHeightCenter = 14, kAudioChannelLabel_VerticalHeightRight = 15,
    kAudioChannelLabel_TopBackLeft = 16, kAudioChannelLabel_TopBackCenter = 17, kAudioChannelLabel_TopBackRight = 18,
    kAudioChannelLabel_RearSurroundLeft = 33, kAudioChannelLabel_RearSurroundRight = 34,
    kAudioChannelLabel_LeftWide = 35, kAudioChannelLabel_RightWide = 36, kAudioChannelLabel_LFE2 = 37,
    kAudioChannelLabel_LeftTotal = 38, kAudioChannelLabel_RightTotal = 39, kAudioChannelLabel_HearingImpaired = 40,
    kAudioChannelLabel_Narration = 41, kAudioChannelLabel_Mono = 42, kAudioChannelLabel_DialogCentricMix = 43,
    kAudioChannelLabel_CenterSurroundDirect = 44, kAudioChannelLabel_Haptic = 45,
    kAudioChannelLabel_Ambisonic_W = 200, kAudioChannelLabel_Ambisonic_X = 201,
    kAudioChannelLabel_Ambisonic_Y = 202, kAudioChannelLabel_Ambisonic_Z = 203,
    kAudioChannelLabel_MS_Mid = 204, kAudioChannelLabel_MS_Side = 205,
    kAudioChannelLabel_XY_X = 206, kAudioChannelLabel_XY_Y = 207,
    kAudioChannelLabel_HeadphonesLeft = 301, kAudioChannelLabel_HeadphonesRight = 302,
    kAudioChannelLabel_ClickTrack = 304, kAudioChannelLabel_ForeignLanguage = 305,
    kAudioChannelLabel_Discrete = 400,
    kAudioChannelLabel_Discrete_0 = (1u<<16)|0, kAudioChannelLabel_Discrete_1 = (1u<<16)|1,
    kAudioChannelLabel_Discrete_2 = (1u<<16)|2, kAudioChannelLabel_Discrete_3 = (1u<<16)|3,
    kAudioChannelLabel_Discrete_4 = (1u<<16)|4, kAudioChannelLabel_Discrete_5 = (1u<<16)|5,
    kAudioChannelLabel_Discrete_6 = (1u<<16)|6, kAudioChannelLabel_Discrete_7 = (1u<<16)|7,
    kAudioChannelLabel_Discrete_8 = (1u<<16)|8, kAudioChannelLabel_Discrete_9 = (1u<<16)|9,
    kAudioChannelLabel_Discrete_10 = (1u<<16)|10, kAudioChannelLabel_Discrete_11 = (1u<<16)|11,
    kAudioChannelLabel_Discrete_12 = (1u<<16)|12, kAudioChannelLabel_Discrete_13 = (1u<<16)|13,
    kAudioChannelLabel_Discrete_14 = (1u<<16)|14, kAudioChannelLabel_Discrete_15 = (1u<<16)|15,
    kAudioChannelLabel_Discrete_65535 = (1u<<16)|65535
};

/* AudioChannelLayoutTag: high 16 bits = tag id, low 16 = channel count. */
enum {
    kAudioChannelLayoutTag_UseChannelDescriptions = (0u<<16)|0,
    kAudioChannelLayoutTag_UseChannelBitmap       = (1u<<16)|0,
    kAudioChannelLayoutTag_Mono            = (100u<<16)|1,
    kAudioChannelLayoutTag_Stereo          = (101u<<16)|2,
    kAudioChannelLayoutTag_StereoHeadphones= (102u<<16)|2,
    kAudioChannelLayoutTag_MatrixStereo    = (103u<<16)|2,
    kAudioChannelLayoutTag_MidSide         = (104u<<16)|2,
    kAudioChannelLayoutTag_XY              = (105u<<16)|2,
    kAudioChannelLayoutTag_Binaural        = (106u<<16)|2,
    kAudioChannelLayoutTag_Ambisonic_B_Format = (107u<<16)|4,
    kAudioChannelLayoutTag_Quadraphonic    = (108u<<16)|4,
    kAudioChannelLayoutTag_Pentagonal      = (109u<<16)|5,
    kAudioChannelLayoutTag_Hexagonal       = (110u<<16)|6,
    kAudioChannelLayoutTag_Octagonal       = (111u<<16)|8
};

/* Extract the channel count from a layout tag (inline in the real header). */
#define AudioChannelLayoutTag_GetNumberOfChannels(layoutTag) ((UInt32)((layoutTag) & 0x0000FFFF))

#endif /* _TIL_SHIM_COREAUDIO_H */
