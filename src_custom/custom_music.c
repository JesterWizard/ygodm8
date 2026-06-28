#include "global.h"
#include "constants/custom_music_generated.h"

void PlayMusic(int);

#if CUSTOM_MUSIC_SONG_COUNT > 0
void PlayCustomMusic(u8 songIndex) {
  if (songIndex >= CUSTOM_MUSIC_SONG_COUNT)
    return;

  PlayMusic((int)(CUSTOM_MUSIC_SONG_ID_MIN + songIndex));
}

void PlayCustomMusicById(u16 songId) {
  if (songId < CUSTOM_MUSIC_SONG_ID_MIN || songId > CUSTOM_MUSIC_SONG_ID_MAX)
    return;

  PlayMusic((int)songId);
}

#else

void PlayCustomMusic(u8 songIndex) {
  (void)songIndex;
}

void PlayCustomMusicById(u16 songId) {
  (void)songId;
}

#endif
