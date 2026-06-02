#ifndef GUARD_M4A_HQ_MIXER_H
#define GUARD_M4A_HQ_MIXER_H

#include "global.h"

#define M4A_HQ_MIX_FRAME_SAMPLES 0x160
#define M4A_HQ_MIX_BUFFER_BYTES (M4A_HQ_MIX_FRAME_SAMPLES * 4)

extern u8 M4aHqMixerIwramStart[];
extern u8 M4aHqMixerIwramEnd[];
extern u8 gM4aHqMixBuffer[];
extern u8 MixerBuffer[];
extern const u32 MixerSize;

#define M4A_HQ_MIXER_ROM_SIZE ((u32)(M4aHqMixerIwramEnd - M4aHqMixerIwramStart))

#endif // GUARD_M4A_HQ_MIXER_H
