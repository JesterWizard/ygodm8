#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_48_state_04: map 48 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE8E4, map_48_state_04_08EDE8E4, 0x08EDE8F0, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_YUGI)
  LOAD_SPRITE(2, SPRITE_PARA_FLIPPING)
  LOAD_SPRITE(3, SPRITE_DOX_FLIPPING)
  PLAY_MUSIC(MUSIC_DUNGEON)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I also have to get the spirit of the Puzzle back.",
      "That's why I have to keep up with your skills, {PLAYER}."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
