/* SDK-less shim for <AudioToolbox/AudioToolbox.h> (issue #25 / #232).
 * The AudioComponent + AudioUnit surface miniaudio (raylib's raudio
 * backend) uses. miniaudio runtime-links the functions; the types are the
 * documented, ABI-stable definitions. Referenced functions bind at runtime
 * via the AudioToolbox/AudioUnit .tbd stub. */
#ifndef _TIL_SHIM_AUDIOTOOLBOX_H
#define _TIL_SHIM_AUDIOTOOLBOX_H

#include <stdint.h>
#include <CoreAudio/CoreAudio.h>

/* --- AudioComponent --- */
typedef struct AudioComponentDescription {
    UInt32 componentType;
    UInt32 componentSubType;
    UInt32 componentManufacturer;
    UInt32 componentFlags;
    UInt32 componentFlagsMask;
} AudioComponentDescription;

typedef struct OpaqueAudioComponent         *AudioComponent;
typedef struct OpaqueAudioComponentInstance *AudioComponentInstance;

AudioComponent AudioComponentFindNext(AudioComponent inComponent, const AudioComponentDescription *inDesc);
OSStatus       AudioComponentInstanceNew(AudioComponent inComponent, AudioComponentInstance *outInstance);
OSStatus       AudioComponentInstanceDispose(AudioComponentInstance inInstance);

/* --- AudioUnit --- */
typedef AudioComponentInstance AudioUnit;
typedef UInt32 AudioUnitPropertyID;
typedef UInt32 AudioUnitScope;
typedef UInt32 AudioUnitElement;
typedef UInt32 AudioUnitRenderActionFlags;

typedef OSStatus (*AURenderCallback)(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags,
    const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);

typedef struct AURenderCallbackStruct {
    AURenderCallback inputProc;
    void            *inputProcRefCon;
} AURenderCallbackStruct;

typedef void (*AudioUnitPropertyListenerProc)(void *inRefCon, AudioUnit inUnit,
    AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement);

OSStatus AudioUnitInitialize(AudioUnit inUnit);
OSStatus AudioUnitUninitialize(AudioUnit inUnit);
OSStatus AudioUnitRender(AudioUnit inUnit, AudioUnitRenderActionFlags *ioActionFlags,
    const AudioTimeStamp *inTimeStamp, UInt32 inOutputBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);
OSStatus AudioUnitGetProperty(AudioUnit inUnit, AudioUnitPropertyID inID, AudioUnitScope inScope,
    AudioUnitElement inElement, void *outData, UInt32 *ioDataSize);
OSStatus AudioUnitGetPropertyInfo(AudioUnit inUnit, AudioUnitPropertyID inID, AudioUnitScope inScope,
    AudioUnitElement inElement, UInt32 *outDataSize, Boolean *outWritable);
OSStatus AudioUnitSetProperty(AudioUnit inUnit, AudioUnitPropertyID inID, AudioUnitScope inScope,
    AudioUnitElement inElement, const void *inData, UInt32 inDataSize);
OSStatus AudioUnitAddPropertyListener(AudioUnit inUnit, AudioUnitPropertyID inID,
    AudioUnitPropertyListenerProc inProc, void *inProcUserData);
OSStatus AudioOutputUnitStart(AudioUnit ci);
OSStatus AudioOutputUnitStop(AudioUnit ci);

/* AudioUnit scopes / property IDs / output-unit property IDs. */
enum { kAudioUnitScope_Global = 0, kAudioUnitScope_Input = 1, kAudioUnitScope_Output = 2 };
enum {
    kAudioUnitProperty_StreamFormat         = 8,
    kAudioUnitProperty_MaximumFramesPerSlice = 14,
    kAudioUnitProperty_AudioChannelLayout   = 19,
    kAudioUnitProperty_SetRenderCallback    = 23
};
enum {
    kAudioOutputUnitProperty_CurrentDevice   = 2000,
    kAudioOutputUnitProperty_IsRunning       = 2001,
    kAudioOutputUnitProperty_EnableIO        = 2003,
    kAudioOutputUnitProperty_SetInputCallback = 2005
};

/* Component type/subtype/manufacturer FourCharCodes for the default output. */
#define kAudioUnitType_Output          _TIL_FCC('a','u','o','u')
#define kAudioUnitSubType_HALOutput    _TIL_FCC('a','h','a','l')
#define kAudioUnitSubType_DefaultOutput _TIL_FCC('d','e','f',' ')
#define kAudioUnitManufacturer_Apple   _TIL_FCC('a','p','p','l')

#endif /* _TIL_SHIM_AUDIOTOOLBOX_H */
