#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_18_state_05: map 18 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E80B50, map_18_state_05_08E80B50, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  TEXT
  (
      "Sigh... I feel so empty...\n\n"
      "Oh, if only my rare cards\n"
      "were safe...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80B5C, map_18_state_05_08E80B5C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I can't duel without my\n"
      "cards.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
