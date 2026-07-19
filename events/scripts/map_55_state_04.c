#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_55_state_04: map 55 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EF0588, map_55_state_04_08EF0588, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PEGASUS)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The path you are on is neverending!",
      "I have taken the miserable spirits of the duelists you",
      "defeated...",
      "And crystallized them into these dark duelists!",
      "They are invincible! Enjoy!"
  )
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_POSITION_AUTO, "Ahahahahaha!")
  SET_FLAG(EVENT_FLAG_ENTERED_PEGASUS_CASTLE)
  FADE_SCREEN(8)
  WARP(LOCATION_PEGASUS_CASTLE_HALLWAY, 1, 2, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
