#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_59_state_02: map 59 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EFDAA0, map_59_state_02_08EFDAA0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ODION)
  PLAY_MUSIC(MUSIC_EGYPT)
  SHOW_OBJECT(1, 61, 30, 0, 0, 0)
  WALK_OBJECT_Y(1, 48)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Master Marik will decipher\nthe hieroglyphics.\n\nBut he will need time.\n\nIt is best if you continue\nyour quest.\n\nI will wait for you here and\ninform you of his progress.\n\nPlease visit us\noccasionally.\n\nI am sure that will please\nMaster Marik.\n\nPlease give my regards to\nMistress Ishizu.\n\n")
  SET_FLAG(EVENT_FLAG_EXITED_MARIKS_HOME)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAAC, map_59_state_02_08EFDAAC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Since you arrived, Master\nMarik has been chanting\n\ndevoutly.\n\nHe is chanting to atone for\nhis past sins.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAB8, map_59_state_02_08EFDAB8, 0x08EFDAC4, 0x08F0404C)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("You dare enter my haven of\ntraps?\n\nFine! We shall duel!\n\n")
  DUEL(157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAC4, map_59_state_02_08EFDAC4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_EGYPT)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Gah! Your fighting spirit is\nmost impressive!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
