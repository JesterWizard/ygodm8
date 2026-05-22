#include "event_macros.h"
#include "overworld.h"

/* map_15_state_03: map 15 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A5B4, map_15_state_03_08E7A5B4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  TEXT("I heard a most remarkable\nthing today.\n\nAn express train was\nchartered solely for\n\ndueling!\n\nSome people have the oddest\nideas, I daresay.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5C0, map_15_state_03_08E7A5C0, 0x08E7A5CC, 0x08E7A5E4)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBAS_BUTTLER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5CC, map_15_state_03_08E7A5CC, 0x08E7A5D8, 0x08F0404C)
  TEXT("A duel? With me?\n\nI do hope you don't under-\nestimate me as an amateur.\n\n")
  DUEL(22)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5D8, map_15_state_03_08E7A5D8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_231)
  TEXT("You're none too shabby.\n\nWe shall match wits again on\nthe train.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBAS_BUTTLER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5E4, map_15_state_03_08E7A5E4, 0x08F04040, 0x08F04040)
  TEXT("We shall match wits again on\nthe train.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
