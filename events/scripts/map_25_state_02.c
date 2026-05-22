#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_02: map 25 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E995B8, map_25_state_02_08E995B8, 0x08E995C4, 0x08E995D0)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  CHECK_FLAG(EVENT_FLAG_SCARED_SHIP_DEALER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995C4, map_25_state_02_08E995C4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, no, please! I am not a\n"
      "duelist!\n\n"
      "There are duelists on the\n"
      "next floor!\n\n"
      "...Oh? You're not the Neo\n"
      "Ghouls?\n\n"
  )
  SET_FLAG(EVENT_FLAG_SCARED_SHIP_DEALER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995D0, map_25_state_02_08E995D0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "If only I were a duelist...\n\n"
      "Those Neo Ghouls wouldn't\n"
      "stand a chance!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995DC, map_25_state_02_08E995DC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Hahaha, sorry, but I am not\n"
      "a duelist.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995E8, map_25_state_02_08E995E8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "That dealer over there...\n\n"
      "All he did was hide from the\n"
      "Neo Ghouls.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995F4, map_25_state_02_08E995F4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, I'll pass.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
