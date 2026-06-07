#include "global.h"
#include "configs/runtime.h"
#include "constants/custom_voices_generated.h"

void m4aSongNumStart(u16);

void PlayCustomVoiceClip(u8 songIndex) {
  if (songIndex >= CUSTOM_VOICE_SONG_COUNT)
    return;

  m4aSongNumStart((u16)(CUSTOM_VOICE_SONG_ID_MIN + songIndex));
}
