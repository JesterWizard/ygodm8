#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_07_state_02: map 7 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E5F894, map_07_state_02_08E5F894, 0x08E5F8A0, 0x08E5F8AC)
  LOAD_SPRITE(1, SPRITE_TEA)
  LOAD_SPRITE(2, SPRITE_GRANDPA_MUTO)
  LOAD_SPRITE(3, SPRITE_YUGI)
  LOAD_SPRITE(4, SPRITE_JOEY)
  LOAD_SPRITE(5, SPRITE_INVISIBLE)
  LOAD_SPRITE(6, SPRITE_INVISIBLE)
  CHECK_FLAG(EVENT_FLAG_FOUND_ALL_ALLIES)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8A0, map_07_state_02_08E5F8A0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The whole city is infested with Neo Ghouls.",
      "I heard that Ishizu has been abducted, too...",
      "{PLAYER}, hurry, send the Neo Ghouls on a one-way",
      "ticket out of here!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8AC, map_07_state_02_08E5F8AC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Neo Ghouls seem to have left town.",
      "But Ishizu is still missing.",
      "We have to find her, and fast!",
      "Don't give up, {PLAYER}."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
