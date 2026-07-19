#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_21_state_06: map 21 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E863E4, map_21_state_06_08E863E4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_EGYPT_EXHIBITION_GUARD)
  TEXT(
      "It was chaotic before, but things have quieted down.",
      "The Egypt Exhibition is open for admission."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E863F0, map_21_state_06_08E863F0, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I'm sorry, but I'm not a duelist.",
      "May I suggest you find someone else to duel?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
