#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_03_state_04: map 3 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E4AA30, map_03_state_04_08E4AA30, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBA_FAN)
  LOAD_SPRITE(2, SPRITE_RED_HAIR)
  LOAD_SPRITE(3, SPRITE_REX)
  TEXT
  (
      "I was hoping that Kaiba\n"
      "would save us...\n\n"
      "But surprisingly, Rex Raptor\n"
      "came to our rescue.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA3C, map_03_state_04_08E4AA3C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "The Neo Ghouls are robbing\n"
      "everyone's rare cards.\n\n"
      "Somebody has to stop them!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA48, map_03_state_04_08E4AA48, 0x08E4AA6C, 0x08E4AA54)
  CHECK_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA6C, map_03_state_04_08E4AA6C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Leave it to me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA54, map_03_state_04_08E4AA54, 0x08E4AA60, 0x08E4AA6C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA60, map_03_state_04_08E4AA60, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Neo Ghouls are hiding\n"
      "out in the Town of Domino?\n\n"
      "I thought they were heading\n"
      "towards KaibaCorp.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA78, map_03_state_04_08E4AA78, 0x08E4AA84, 0x08F0404C)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You wanna duel me? You\n"
      "really want to become\n\n"
      "extinct?\n\n"
      "All right! Let's duel!\n\n"
  )
  DUEL(DUELIST_REX_054)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4AA84, map_03_state_04_08E4AA84, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Looks like your deck's\n"
      "coming together well.\n\n"
      "Keep it up and let's kick\n"
      "the Neo Ghouls outta town!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
