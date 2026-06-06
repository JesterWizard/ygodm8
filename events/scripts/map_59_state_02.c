#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_59_state_02: map 59 state 2 */

LOAD_SPRITE(1, SPRITE_ODION)
PLAY_MUSIC(MUSIC_EGYPT)
SHOW_OBJECT(1, 61, 30, 0, 0, 0)
WALK_OBJECT_Y(1, 48)
MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
DELAY(16)
PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Master Marik will decipher\n"
    "the hieroglyphics.\n\n"
    "But he will need time.\n\n"
    "It is best if you continue\n"
    "your quest.\n\n"
    "I will wait for you here and\n"
    "inform you of his progress.\n\n"
    "Please visit us\n"
    "occasionally.\n\n"
    "I am sure that will please\n"
    "Master Marik.\n\n"
    "Please give my regards to\n"
    "Mistress Ishizu.\n\n"
)
SET_FLAG(EVENT_FLAG_EXITED_MARIKS_HOME)

EVENT_SCRIPT_REPLACEMENT(0x08EFDAAC, map_59_state_02_08EFDAAC, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Since you arrived, Master\n"
      "Marik has been chanting\n\n"
      "devoutly.\n\n"
      "He is chanting to atone for\n"
      "his past sins.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAB8, map_59_state_02_08EFDAB8, 0x08EFDAC4, 0x08F0404C)
PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You dare enter my haven of\n"
      "traps?\n\n"
      "Fine! We shall duel!\n\n"
  )
  DUEL(DUELIST_ODION_157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAC4, map_59_state_02_08EFDAC4, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_EGYPT)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Gah! Your fighting spirit is\n"
      "most impressive!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
