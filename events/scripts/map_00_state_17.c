#include "event_macros.h"
#include "overworld.h"

/* map_00_state_17: map 0 state 17 */

EVENT_SCRIPT_REPLACEMENT(0x08E34E20, map_00_state_17_08E34E20, 0x08E34E2C, 0x08E34E44)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_ESPA_ROBA2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E2C, map_00_state_17_08E34E2C, 0x08E34E38, 0x08F0404C)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO)
  TEXT("Pipipi...\n\n")
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Who are you fighting?\n\nActually, don't tell me.\nDuelists don't communicate\n\nwith words. We communicate\nwith cards!\n\nDon't underestimate my\nPsychic Power deck!\n\n")
  DUEL(84)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E38, map_00_state_17_08E34E38, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO)
  TEXT("Pipipi... You win.\n\n")
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("I don't know who you're\nfighting, but take my Jinzo\n\nwith you.\n\nThis card represents my\nspirit.\n\nYour fight is far from over,\nbut... Pipipi...\n\nYes. I sense you'll be fine.\n\nA duelist becomes more\npowerful when he has\n\nfriends supporting him.\n\nSo think of Jinzo as me.\n\nAs long as you have my help,\nyou're not fighting alone!\n\n")
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Received Jinzo.")
  PLAY_MUSIC(701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(4)
  PAGE_BREAK()
  ADD_CARD(752)
  SET_FLAG(EVENT_FLAG_DEFEATED_ESPA_ROBA2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E44, map_00_state_17_08E34E44, 0x08E34E50, 0x08F0404C)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO)
  TEXT("If you think dueling me will\nhelp you improve...\n\nThen I'll be happy to duel\nyou!\n\n")
  DUEL(146)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E50, map_00_state_17_08E34E50, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(4)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO)
  TEXT("A duelist's greatest\nstrength is his potential.\n\nThe hope we instill in our\ncards makes our decks\n\npowerful.\n\nPipipi...\n\nI don't have to read the\ncosmic forces to know that\n\nyou're a more skilled\nduelist than before!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
