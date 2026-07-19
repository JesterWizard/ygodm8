#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_09_state_00: map 9 state 0 */

EVENT_SCRIPT_REPLACEMENT(0x08E621E4, map_09_state_00_08E621E4, 0x08E621F0, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_INVISIBLE)
  PLAY_MUSIC(MUSIC_365)
  SPECIAL(0)
  RESTORE_LIFE_POINTS()
  TEXT(
      "Your Life Points {BYTE_8169}LP{BYTE_816A} have been restored.",
      "Would you like to save?",
      "{CARD_1}Yes\nNo{CARD_2}"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621F0, map_09_state_00_08E621F0, EVENT_NOP, EVENT_NOP)
  SAVE()
  TEXT("Your progress has been saved.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
