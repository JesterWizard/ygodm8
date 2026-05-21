#include "event_macros.h"
#include "overworld.h"

/* map_26_state_08: map 26 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3DE8, map_26_state_08_08EA3DE8, 0x08F04040, 0x08F04040)
  TEXT("Roulette, poker, slot\nmachines...\n\nThere are many kinds of\ngames I enjoy.\n\nBut the best of all is Duel\nMonsters.\n\nThe game has become the love\nof my life!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DF4, map_26_state_08_08EA3DF4, 0x08EA3E00, 0x08EA3E18)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RICH_HUSBAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E00, map_26_state_08_08EA3E00, 0x08EA3E0C, 0x08F0404C)
  TEXT("Okay!\n\nDon't expect any mercy,\nladdie!\n\n")
  DUEL(98)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E0C, map_26_state_08_08EA3E0C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(15)
  TEXT("Oh no!\n\nI was beaten by a mere\nchild!\n\nBut unpredictability is one\nof the reasons this game is\n\nso fun!\n\nI also like fixing my deck\nafter a loss.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_RICH_HUSBAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E18, map_26_state_08_08EA3E18, 0x08F04040, 0x08F04040)
  TEXT("Sorry, laddie! You'll have\nto wait.\n\nI'm making adjustments to my\ndeck.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E24, map_26_state_08_08EA3E24, 0x08F04040, 0x08F04040)
  TEXT("My husband is engrossed in\ndueling.\n\nIt's funny, he wasn't\ninterested at all before.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E30, map_26_state_08_08EA3E30, 0x08EA3E3C, 0x08EA3E54)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RICH_WIFE2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E3C, map_26_state_08_08EA3E3C, 0x08EA3E48, 0x08F0404C)
  TEXT("Why certainly.\n\n")
  DUEL(99)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E48, map_26_state_08_08EA3E48, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(15)
  TEXT("I must construct my deck\nwisely.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_RICH_WIFE2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3E54, map_26_state_08_08EA3E54, 0x08F04040, 0x08F04040)
  TEXT("Another time, dear.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
