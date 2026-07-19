#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_18_state_05: map 18 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E80B50, map_18_state_05_08E80B50, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  TEXT(
      "Sigh... I feel so empty...",
      "Oh, if only my rare cards were safe..."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80B5C, map_18_state_05_08E80B5C, EVENT_NOP, EVENT_NOP)
  TEXT("I can't duel without my cards.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
