#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_21_state_06: map 21 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E863E4, map_21_state_06_08E863E4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_EGYPT_EXHIBITION_GUARD)
  TEXT
  (
      "It was chaotic before, but\n"
      "things have quieted down.\n\n"
      "The Egypt Exhibition is open\n"
      "for admission.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E863F0, map_21_state_06_08E863F0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm sorry, but I'm not a\n"
      "duelist.\n\n"
      "May I suggest you find\n"
      "someone else to duel?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
