#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_05_state_01: map 5 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E50EA8, map_05_state_01_08E50EA8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_STRINGER)
  LOAD_SPRITE(2, SPRITE_RED_MOHAWK)
  TEXT(
      "I won't be riding the Duel Express...",
      "But that doesn't mean my duelist level is low!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EB4, map_05_state_01_08E50EB4, 0x08E50EC0, 0x08E50ED8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_STRINGER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EC0, map_05_state_01_08E50EC0, 0x08E50ECC, 0x08F0404C)
  TEXT(
      "I still have my pride as a duelist.",
      "I don't feel like dueling, but I'll still take you on",
      "fair and square."
  )
  DUEL(DUELIST_ID_008)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50ECC, map_05_state_01_08E50ECC, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT(
      "Instead of fair and square, maybe we should've played",
      "by my rules."
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_STRINGER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50ED8, map_05_state_01_08E50ED8, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Let me tell this to you straight. I'm not one of",
      "those gracious losers. I hate losing!",
      "It's no fun to lose to a tough duelist.",
      "So you can forget about dueling me ever again.",
      "Humph!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EE4, map_05_state_01_08E50EE4, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Did you hear about the Duel Express?",
      "Any duelist can get on board.",
      "Maybe I should go, too."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EF0, map_05_state_01_08E50EF0, 0x08E50EFC, 0x08E50F14)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50EFC, map_05_state_01_08E50EFC, 0x08E50F08, 0x08F0404C)
  TEXT(
      "Sure thing!",
      "A duel's a duel, no matter where it's played!"
  )
  DUEL(DUELIST_ID_009)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F08, map_05_state_01_08E50F08, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT("Tsk... Lost that one.")
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_MOHAWK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E50F14, map_05_state_01_08E50F14, EVENT_NOP, EVENT_NOP)
  TEXT("Huh? You again? Are you picking on me, you bully!")
  FALLTHROUGH()
END_EVENT_SCRIPT()
