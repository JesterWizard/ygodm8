#include "event_macros.h"
#include "overworld.h"

/* map_37_state_05: map 37 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD844, map_37_state_05_08ECD844, 0x08ECD850, 0x08ECD85C)
  LOAD_SPRITE(1, SPRITE_MAKO)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD850, map_37_state_05_08ECD850, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Do you sense it?\nThe tortured waves,\n\nthe crashing sea...\n\nSomething's wrong.\nSomething's different.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD85C, map_37_state_05_08ECD85C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("I've passed you my spirit.\n\nJust as the world's oceans\nare connected, our souls\n\nare united.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD868, map_37_state_05_08ECD868, 0x08ECD874, 0x08ECD88C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD874, map_37_state_05_08ECD874, 0x08ECD880, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("{PLAYER}, you feel it, too?\n\nThe sea... It's afraid.\n\nThe ocean is terrified!\n\n{PLAYER}, you are intending\nto fight something that can\n\nparalyze the waters to its\nbriny deep!\n\nDo not deny it. I can tell.\n\nIn that case, take my spirit\nto battle with you!\n\n")
  DUEL(103)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD880, map_37_state_05_08ECD880, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(249)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("I've passed you my spirit.\n\nJust as the world's oceans\nare connected, our souls\n\nare united.\n\nWait, take my spirit card.\n\nIt's The Legendary\nFisherman.\n\nThe sea will drown you if\nyou show fear.\n\nIt's the same with dueling.\n\nKeep fighting without fear!\n\n")
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Received The Legendary\nFisherman.")
  PLAY_MUSIC(701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(249)
  PAGE_BREAK()
  ADD_CARD(257)
  SET_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD88C, map_37_state_05_08ECD88C, 0x08ECD898, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("No matter how tough the\nenemy, there's nothing to\n\nfear!\n\nAttack your foe with all\nyour might!\n\nI'm going to give my all in\nthis duel!\n\n")
  DUEL(150)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD898, map_37_state_05_08ECD898, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(249)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Did you learn anything from\nthis duel?\n\nAll oceans may look the same\nto you, but I can tell the\n\ndifference.\n\nYou just need to develop a\ndiscerning eye.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
