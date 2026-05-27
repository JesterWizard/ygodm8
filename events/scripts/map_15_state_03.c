#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_03: map 15 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A5B4, map_15_state_03_08E7A5B4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  TEXT
  (
      "I heard a most remarkable\n"
      "thing today.\n\n"
      "An express train was\n"
      "chartered solely for\n\n"
      "dueling!\n\n"
      "Some people have the oddest\n"
      "ideas, I daresay.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5C0, map_15_state_03_08E7A5C0, 0x08E7A5CC, 0x08E7A5E4)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBAS_BUTTLER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5CC, map_15_state_03_08E7A5CC, 0x08E7A5D8, 0x08F0404C)
  TEXT
  (
      "A duel? With me?\n\n"
      "I do hope you don't under-\n"
      "estimate me as an amateur.\n\n"
  )
  DUEL(DUELIST_ID_022)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5D8, map_15_state_03_08E7A5D8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "You're none too shabby.\n\n"
      "We shall match wits again on\n"
      "the train.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBAS_BUTTLER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5E4, map_15_state_03_08E7A5E4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "We shall match wits again on\n"
      "the train.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
