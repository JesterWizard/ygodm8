#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_48_state_04: map 48 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE8E4, map_48_state_04_08EDE8E4, 0x08EDE8F0, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_YUGI)
  LOAD_SPRITE(2, SPRITE_PARA_FLIPPING)
  LOAD_SPRITE(3, SPRITE_DOX_FLIPPING)
  PLAY_MUSIC(MUSIC_DUNGEON)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("I also have to get the\nspirit of the Puzzle back.\n\nThat's why I have to keep up\nwith your skills, {PLAYER}.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
