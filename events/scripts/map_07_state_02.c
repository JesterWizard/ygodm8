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

EVENT_SCRIPT_REPLACEMENT(0x08E5F8A0, map_07_state_02_08E5F8A0, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The whole city is infested\n"
    "with Neo Ghouls.\n\n"
    "I heard that Ishizu has been\n"
    "abducted, too...\n\n"
    "{PLAYER}, hurry, send the\n"
    "Neo Ghouls on a one-way\n\n"
    "ticket out of here!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8AC, map_07_state_02_08E5F8AC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The Neo Ghouls seem to have\n"
    "left town.\n\n"
    "But Ishizu is still missing.\n\n"
    "We have to find her, and\n"
    "fast!\n\n"
    "Don't give up, {PLAYER}.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
