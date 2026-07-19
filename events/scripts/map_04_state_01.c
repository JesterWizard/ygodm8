#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_04_state_01: map 4 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D03C, map_04_state_01_08E4D03C, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_DUELIST_HATER)
  LOAD_SPRITE(2, SPRITE_TOURIST)
  TEXT(
      "You say you're a true duelist, but you're just an",
      "amateur that likes playing games.",
      "You're all talk!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D048, map_04_state_01_08E4D048, EVENT_NOP, EVENT_NOP)
  TEXT("No way, I don't duel.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D054, map_04_state_01_08E4D054, EVENT_NOP, EVENT_NOP)
  TEXT(
      "You're a duelist, aren't you?",
      "I can tell from your Duel Disk.",
      "Boy, there sure are a lot of duelists in the Town of",
      "Domino."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D060, map_04_state_01_08E4D060, 0x08E4D06C, 0x08E4D084)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_TOURIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D06C, map_04_state_01_08E4D06C, 0x08E4D078, 0x08F0404C)
  TEXT(
      "A street duel in the city where the Duel Disk was",
      "invented...",
      "This is exactly the duel I've been waiting for!",
      "Let's duel!"
  )
  DUEL(DUELIST_ID_007)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D078, map_04_state_01_08E4D078, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT(
      "Are all the duelists in the Town of Domino this strong?",
      "I'm way out of my league."
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_TOURIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D084, map_04_state_01_08E4D084, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Nah, I know now that you're an expert..",
      "Why don't you look for other duelists?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
