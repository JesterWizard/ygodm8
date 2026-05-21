#include "event_macros.h"
#include "overworld.h"

/* map_14_state_08: map 14 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E77594, map_14_state_08_08E77594, 0x08E775A0, 0x08E775AC)
  PLAY_MUSIC(230)
  HIDE_PORTRAIT()
  DELAY(64)
  MOVE_OBJECT(2, 3, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, 1)
  LANGUAGE_TEXT(0, "What took ya so long,\n{PLAYER}!\n\nIf you're having trouble\nagainst these guys...\n\nWell, I'd hate to think\nwhat'd happen against some\n\nreal competition.\n\nHurry and catch up to my\nlevel!\n\n")
  END_LANGUAGE_TEXT()
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, 1, 0, 0)
  DELAY(16)
  PLAY_MUSIC(274)
  REACTION(REACTION_SWEATDROP, 1)
  DELAY(64)
  COMMAND_7C_ARG(2, 4)
  FADE_SCREEN(4)
  CLEAR_FLAG(243)
  CHECK_FLAG(EVENT_FLAG_CHOSE_TO_FIGHT_THE_MIMIC_OF_DOOM2)
  FALLTHROUGH()
END_EVENT_SCRIPT()
