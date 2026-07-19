#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_50_state_01: map 50 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EE04B8, map_50_state_01_08EE04B8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PARADOX)
  PLAY_MUSIC(MUSIC_410)
  DELAY(16)
  WALK_OBJECT_Y(0, 72)
  DELAY(4)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(1, 60, 52, 0, 1, 0)
  DELAY(64)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Excellent. You've done well to get this far.",
      "However, in order to proceed, you must conquer",
      "this labyrinth.",
      "It is full of paths that neither begin nor end.",
      "You need a light to navigate its neverending",
      "passageways.",
      "But it is no ordinary light that you need.",
      "You must have the light of the spirits."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Yes... You must light your way with spirit cards.",
      "The cards that embody the spirits of your fellow",
      "duelists.",
      "Hold them aloft at forks in the road and let them light",
      "your way.",
      "However, you must never ask for spirit cards.",
      "You must obtain them fairly.",
      "You must win them in duels. There is no other way."
  )
  SET_FLAG(EVENT_FLAG_PARADOX_SAID_TO_GET_SPIRIT_CARDS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04C4, map_50_state_01_08EE04C4, 0x08EE050C, 0x08EE04D0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE050C, map_50_state_01_08EE050C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Go seek out your dueling compatriots, and obtain a",
      "spirit card from each of them."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04D0, map_50_state_01_08EE04D0, 0x08EE050C, 0x08EE04DC)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_REX3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04DC, map_50_state_01_08EE04DC, 0x08EE050C, 0x08EE04E8)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04E8, map_50_state_01_08EE04E8, 0x08EE050C, 0x08EE04F4)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE04F4, map_50_state_01_08EE04F4, 0x08EE050C, 0x08EE0500)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_ESPA_ROBA2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE0500, map_50_state_01_08EE0500, 0x08EE050C, 0x08EE0518)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE0518, map_50_state_01_08EE0518, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "You have gathered the required spirit cards.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE0524, map_50_state_01_08EE0524, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Duelists do not communicate with words.",
      "Duels unite your spirits.",
      "With your hearts as one, your wishes will come true."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
