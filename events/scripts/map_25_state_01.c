#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_25_state_01: map 25 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E99588, map_25_state_01_08E99588, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SHIP_DEALER)
  LOAD_SPRITE(2, SPRITE_CASINO_PLAYER)
  TEXT
  (
      "Welcome! I hope you enjoy\n"
      "yourselves!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E99594, map_25_state_01_08E99594, 0x08F04040, 0x08F04040)
  TEXT
  (
      "We have a duel specialist on\n"
      "board.\n\n"
      "The specialist is on the\n"
      "floor in the next section.\n\n"
      "Please challenge her.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995A0, map_25_state_01_08E995A0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "That dealer... I think he's\n"
      "cheating.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995AC, map_25_state_01_08E995AC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "A duel? What's that? Can I\n"
      "win money?\n\n"
      "There's no money involved?\n"
      "Then what's the point?\n\n"
      "How can you be into a game\n"
      "when there's no cash at\n\n"
      "stake?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
