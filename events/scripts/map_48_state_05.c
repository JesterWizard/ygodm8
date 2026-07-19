#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_48_state_05: map 48 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE980, map_48_state_05_08EDE980, 0x08EDE98C, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_YUGI)
  LOAD_SPRITE(2, SPRITE_PARA)
  LOAD_SPRITE(3, SPRITE_DOX)
  PLAY_MUSIC(MUSIC_400)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "That's why I can't waste any time.",
      "I won't be stopped!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
