#include "event_macros.h"
#include "overworld.h"

/* map_55_state_04: map 55 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EF0588, map_55_state_04_08EF0588, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "The path you are on is\nneverending!\n\nI have taken the miserable\nspirits of the duelists you\n\ndefeated...\n\nAnd crystallized them into\nthese dark duelists!\n\nThey are invincible! Enjoy!\n\n")
  END_LANGUAGE_TEXT()
  PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, 8)
  LANGUAGE_TEXT(0, "Ahahahahaha!\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(EVENT_FLAG_ENTERED_PEGASUS_CASTLE)
  FADE_SCREEN(8)
  WARP(51, 1, 2, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
