#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_02: map 12 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E6EFA0, map_12_state_02_08E6EFA0, 0x08E6EFAC, 0x08E6EFB8)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My big brother isn't here.\n\n"
      "He's investigating the\n"
      "Millennium Items.\n\n"
  )
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFAC, map_12_state_02_08E6EFAC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "He said there's another\n"
      "group also looking for\n\n"
      "them.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFB8, map_12_state_02_08E6EFB8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "The other group searching\n"
      "for the Items call\n\n"
      "themselves the Neo Ghouls.\n\n"
      "You better watch out for\n"
      "them. They sound like\n\n"
      "trouble.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFC4, map_12_state_02_08E6EFC4, 0x08E6EFD0, 0x08E6EFE8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MOKUBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFD0, map_12_state_02_08E6EFD0, 0x08E6EFDC, 0x08F0404C)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Seto isn't here. But don't\n"
      "underestimate my skills, or\n\n"
      "you're gonna pay big time!\n\n"
  )
  DUEL(DUELIST_MOKUBA_013)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFDC, map_12_state_02_08E6EFDC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Argh! I can't believe I\n"
      "lost!\n\n"
      "But believe me, my big\n"
      "brother won't lose to no\n\n"
      "{PLAYER}!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_MOKUBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFE8, map_12_state_02_08E6EFE8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'm a busy guy. I don't have\n"
      "much free time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
