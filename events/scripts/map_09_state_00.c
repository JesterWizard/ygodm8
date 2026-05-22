#include "event_macros.h"
#include "overworld.h"

/* map_09_state_00: map 9 state 0 */

EVENT_SCRIPT_REPLACEMENT(0x08E621E4, map_09_state_00_08E621E4, 0x08E621F0, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_INVISIBLE)
  PLAY_MUSIC(MUSIC_365)
  SPECIAL(0)
  RESTORE_LIFE_POINTS()
  TEXT("Your Life Points {BYTE_8169}LP{BYTE_816A} have\nbeen restored.\n\nWould you like to save?\n\n{CARD_1}Yes\nNo{CARD_2}\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621F0, map_09_state_00_08E621F0, 0x08F04040, 0x08F04040)
  SAVE()
  TEXT("Your progress has been\nsaved.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
