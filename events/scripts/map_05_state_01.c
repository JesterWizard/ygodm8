#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_01: map 5 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E50EA8, map_05_state_01_08E50EA8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  TEXT
  (
      "I won't be riding the Duel\n"
      "Express...\n\n"
      "But that doesn't mean my\n"
      "duelist level is low!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EB4, map_05_state_01_08E50EB4, 0x08E50EC0, 0x08E50ED8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_STRINGER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EC0, map_05_state_01_08E50EC0, 0x08E50ECC, 0x08F0404C)
  TEXT
  (
      "I still have my pride as a\n"
      "duelist.\n\n"
      "I don't feel like dueling,\n"
      "but I'll still take you on\n\n"
      "fair and square.\n\n"
  )
  DUEL(8)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50ECC, map_05_state_01_08E50ECC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Instead of fair and square,\n"
      "maybe we should've played\n\n"
      "by my rules.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_STRINGER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50ED8, map_05_state_01_08E50ED8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Let me tell this to you\n"
      "straight. I'm not one of\n\n"
      "those gracious losers. I\n"
      "hate losing!\n\n"
      "It's no fun to lose to a\n"
      "tough duelist.\n\n"
      "So you can forget about\n"
      "dueling me ever again.\n\n"
      "Humph!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EE4, map_05_state_01_08E50EE4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Did you hear about the Duel\n"
      "Express?\n\n"
      "Any duelist can get on\n"
      "board.\n\n"
      "Maybe I should go, too.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EF0, map_05_state_01_08E50EF0, 0x08E50EFC, 0x08E50F14)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EFC, map_05_state_01_08E50EFC, 0x08E50F08, 0x08F0404C)
  TEXT
  (
      "Sure thing!\n\n"
      "A duel's a duel, no matter\n"
      "where it's played!\n\n"
  )
  DUEL(9)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F08, map_05_state_01_08E50F08, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Tsk... Lost that one.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F14, map_05_state_01_08E50F14, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Huh? You again? Are you\n"
      "picking on me, you bully!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
