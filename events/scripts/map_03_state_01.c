#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_03_state_01: map 3 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E4A8A4, map_03_state_01_08E4A8A4, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBA_FAN)
  LOAD_SPRITE(2, SPRITE_RED_HAIR)
  TEXT
  (
      "I'm a huge fan of Mr. Seto\n"
      "Kaiba.\n\n"
      "I wonder if Kaiba\n"
      "Corporation would hire me?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8B0, map_03_state_01_08E4A8B0, 0x08E4A8BC, 0x08E4A8D4)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_FAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8BC, map_03_state_01_08E4A8BC, 0x08E4A8C8, 0x08F0404C)
  TEXT
  (
      "I'll duel in a way that\n"
      "would make Mr. Kaiba proud!\n\n"
  )
  DUEL(DUELIST_ID_005)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8C8, map_03_state_01_08E4A8C8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "KaibaCorp won't hire me if I\n"
      "can't win...\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_FAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8D4, map_03_state_01_08E4A8D4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I wish I could meet Mr.\n"
      "Kaiba...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8E0, map_03_state_01_08E4A8E0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Dueling is only fun if you\n"
      "don't cheat.\n\n"
      "You should always choose\n"
      "ante cards before dueling.\n\n"
      "That way, there won't be any\n"
      "arguments later.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8EC, map_03_state_01_08E4A8EC, 0x08E4A8F8, 0x08E4A910)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_HAIR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A8F8, map_03_state_01_08E4A8F8, 0x08E4A904, 0x08F0404C)
  TEXT
  (
      "We'll duel fair and square!\n\n"
  )
  DUEL(DUELIST_ID_006)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A904, map_03_state_01_08E4A904, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "I'm so disappointed...\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_HAIR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4A910, map_03_state_01_08E4A910, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Hold on, I'm fixing my deck\n"
      "right now.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
