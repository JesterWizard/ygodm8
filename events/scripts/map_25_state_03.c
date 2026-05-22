#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_03: map 25 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E99600, map_25_state_03_08E99600, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  TEXT
  (
      "I bet you're duelists.\n\n"
      "No, I'm not psychic. It's\n"
      "obvious because you're\n\n"
      "wearing Duel Disks.\n\n"
      "Unfortunately, I don't duel.\n\n"
      "You should go to the next\n"
      "floor.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9960C, map_25_state_03_08E9960C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I hear that dealer dislikes\n"
      "duelists.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E99618, map_25_state_03_08E99618, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No thanks. I don't duel.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
