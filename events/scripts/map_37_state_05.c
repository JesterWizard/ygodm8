#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_37_state_05: map 37 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD844, map_37_state_05_08ECD844, 0x08ECD850, 0x08ECD85C)
  LOAD_SPRITE(1, SPRITE_MAKO)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD850, map_37_state_05_08ECD850, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Do you sense it?\n"
      "The tortured waves,\n\n"
      "the crashing sea...\n\n"
      "Something's wrong.\n"
      "Something's different.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD85C, map_37_state_05_08ECD85C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I've passed you my spirit.\n\n"
      "Just as the world's oceans\n"
      "are connected, our souls\n\n"
      "are united.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD868, map_37_state_05_08ECD868, 0x08ECD874, 0x08ECD88C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD874, map_37_state_05_08ECD874, 0x08ECD880, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, you feel it, too?\n\n"
      "The sea... It's afraid.\n\n"
      "The ocean is terrified!\n\n"
      "{PLAYER}, you are intending\n"
      "to fight something that can\n\n"
      "paralyze the waters to its\n"
      "briny deep!\n\n"
      "Do not deny it. I can tell.\n\n"
      "In that case, take my spirit\n"
      "to battle with you!\n\n"
  )
  DUEL(103)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD880, map_37_state_05_08ECD880, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_249)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I've passed you my spirit.\n\n"
      "Just as the world's oceans\n"
      "are connected, our souls\n\n"
      "are united.\n\n"
      "Wait, take my spirit card.\n\n"
      "It's The Legendary\n"
      "Fisherman.\n\n"
      "The sea will drown you if\n"
      "you show fear.\n\n"
      "It's the same with dueling.\n\n"
      "Keep fighting without fear!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Received The Legendary\n"
      "Fisherman."
  )
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_249)
  PAGE_BREAK()
  ADD_CARD(257)
  SET_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD88C, map_37_state_05_08ECD88C, 0x08ECD898, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "No matter how tough the\n"
      "enemy, there's nothing to\n\n"
      "fear!\n\n"
      "Attack your foe with all\n"
      "your might!\n\n"
      "I'm going to give my all in\n"
      "this duel!\n\n"
  )
  DUEL(150)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD898, map_37_state_05_08ECD898, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_249)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Did you learn anything from\n"
      "this duel?\n\n"
      "All oceans may look the same\n"
      "to you, but I can tell the\n\n"
      "difference.\n\n"
      "You just need to develop a\n"
      "discerning eye.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
