#include "event_macros.h"
#include "overworld.h"

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
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The whole city is infested\nwith Neo Ghouls.\n\nI heard that Ishizu has been\nabducted, too...\n\n{PLAYER}, hurry, send the\nNeo Ghouls on a one-way\n\nticket out of here!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8AC, map_07_state_02_08E5F8AC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The Neo Ghouls seem to have\nleft town.\n\nBut Ishizu is still missing.\n\nWe have to find her, and\nfast!\n\nDon't give up, {PLAYER}.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
