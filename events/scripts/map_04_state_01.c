#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_04_state_01: map 4 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E4D03C, map_04_state_01_08E4D03C, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_DUELIST_HATER)
  LOAD_SPRITE(2, SPRITE_TOURIST)
  TEXT
  (
      "You say you're a true\n"
      "duelist, but you're just an\n\n"
      "amateur that likes playing\n"
      "games.\n\n"
      "You're all talk!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D048, map_04_state_01_08E4D048, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No way, I don't duel.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D054, map_04_state_01_08E4D054, 0x08F04040, 0x08F04040)
  TEXT
  (
      "You're a duelist, aren't\n"
      "you?\n\n"
      "I can tell from your Duel\n"
      "Disk.\n\n"
      "Boy, there sure are a lot of\n"
      "duelists in the Town of\n\n"
      "Domino.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D060, map_04_state_01_08E4D060, 0x08E4D06C, 0x08E4D084)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_TOURIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D06C, map_04_state_01_08E4D06C, 0x08E4D078, 0x08F0404C)
  TEXT
  (
      "A street duel in the city\n"
      "where the Duel Disk was\n\n"
      "invented...\n\n"
      "This is exactly the duel\n"
      "I've been waiting for!\n\n"
      "Let's duel!\n\n"
  )
  DUEL(DUELIST_ID_007)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D078, map_04_state_01_08E4D078, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Are all the duelists in the\n"
      "Town of Domino this strong?\n\n"
      "I'm way out of my league.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_TOURIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4D084, map_04_state_01_08E4D084, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Nah, I know now that you're\n"
      "an expert..\n\n"
      "Why don't you look for other\n"
      "duelists?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
