#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_09: map 26 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3D88, map_26_state_09_08EA3D88, 0x08EA3D94, 0x08EA3DA0)
  LOAD_SPRITE(1, SPRITE_MAI)
  LOAD_SPRITE(2, SPRITE_RICH_HUSBAND)
  LOAD_SPRITE(3, SPRITE_RICHE_WIFE)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D94, map_26_state_09_08EA3D94, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("{PLAYER}... You came here\nfor a reason, didn't you?\n\nWhatever it is, I'm here to\nhelp.\n\nChallenge me whenever you\nfeel ready.\n\nAs duelists, we understand\neach other the best when we\n\nduel.\n\nIt sounds weird, but it's\ntrue.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DA0, map_26_state_09_08EA3DA0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The people in the Town of\nDomino are happy now that\n\nthe Neo Ghouls are gone.\n\nBut don't you sense\nsomething strange?\n\nI don't know what it is, but\nit doesn't feel good.\n\nIt feels like the last turn\nof a duel that I'm about to\n\nlose.\n\nIt's just awful!\n\n{PLAYER}, this enemy that\nyou're facing...\n\nWho is it?\n\nWho can create so much\ntension in the air?\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DAC, map_26_state_09_08EA3DAC, 0x08EA3DB8, 0x08EA3DD0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DB8, map_26_state_09_08EA3DB8, 0x08EA3DC4, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Duelists get to know each\nother through dueling.\n\nOnce duelists battle, a bond\ndevelops that didn't exist\n\nbefore.\n\n{PLAYER}, I accept your\nduel!\n\n")
  DUEL(97)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DC4, map_26_state_09_08EA3DC4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("{PLAYER}...\n\nI can tell you're planning\nto face something huge and\n\nterrible...\n\nBut you'll be fine.\n\nThere's a bond between us!\n\nEven when we're far apart,\nour hearts beat as one.\n\nThis is Harpie Lady. It\nrepresents my spirit as a\n\nduelist.\n\nI'm not required to give it\nto you, but I want you to\n\nhave it.\n\n")
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Received Harpie Lady.")
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  PAGE_BREAK()
  ADD_CARD(62)
  SET_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DD0, map_26_state_09_08EA3DD0, 0x08EA3DDC, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("{PLAYER}, I don't know what\nyou're facing.\n\nBut I know it won't be easy.\n\nRemember that every duelist\nhas unlimited potential.\n\nIf you think it'll help,\nI'll duel you anytime!\n\n")
  DUEL(147)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DDC, map_26_state_09_08EA3DDC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Did this duel help you?\n\nDon't lose, {PLAYER}!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
