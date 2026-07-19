#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_03: map 15 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A5B4, map_15_state_03_08E7A5B4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  TEXT(
      "I heard a most remarkable thing today.",
      "An express train was chartered solely for",
      "dueling!",
      "Some people have the oddest ideas, I daresay."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5C0, map_15_state_03_08E7A5C0, 0x08E7A5CC, 0x08E7A5E4)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBAS_BUTTLER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5CC, map_15_state_03_08E7A5CC, 0x08E7A5D8, 0x08F0404C)
  TEXT(
      "A duel? With me?",
      "I do hope you don't under- estimate me as an amateur."
  )
  DUEL(DUELIST_ID_022)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5D8, map_15_state_03_08E7A5D8, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_231)
  TEXT(
      "You're none too shabby.",
      "We shall match wits again on the train."
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBAS_BUTTLER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5E4, map_15_state_03_08E7A5E4, EVENT_NOP, EVENT_NOP)
  TEXT("We shall match wits again on the train.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
