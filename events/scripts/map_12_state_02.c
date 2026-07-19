#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_02: map 12 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E6EFA0, map_12_state_02_08E6EFA0, 0x08E6EFAC, 0x08E6EFB8)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "My big brother isn't here.",
      "He's investigating the Millennium Items."
  )
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFAC, map_12_state_02_08E6EFAC, EVENT_NOP, EVENT_NOP)
  TEXT(
      "He said there's another group also looking for",
      "them."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFB8, map_12_state_02_08E6EFB8, EVENT_NOP, EVENT_NOP)
  TEXT(
      "The other group searching for the Items call",
      "themselves the Neo Ghouls.",
      "You better watch out for them. They sound like",
      "trouble."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFC4, map_12_state_02_08E6EFC4, 0x08E6EFD0, 0x08E6EFE8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MOKUBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFD0, map_12_state_02_08E6EFD0, 0x08E6EFDC, 0x08F0404C)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Seto isn't here. But don't underestimate my skills, or",
      "you're gonna pay big time!"
  )
  DUEL(DUELIST_MOKUBA_013)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFDC, map_12_state_02_08E6EFDC, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO,
      "Argh! I can't believe I lost!",
      "But believe me, my big brother won't lose to no",
      "{PLAYER}!"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_MOKUBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6EFE8, map_12_state_02_08E6EFE8, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I'm a busy guy. I don't have much free time.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
