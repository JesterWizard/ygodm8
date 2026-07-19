#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_59_state_02: map 59 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EFDAA0, map_59_state_02_08EFDAA0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_ODION)
  PLAY_MUSIC(MUSIC_EGYPT)
  SHOW_OBJECT(1, 61, 30, 0, 0, 0)
  WALK_OBJECT_Y(1, 48)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Master Marik will decipher the hieroglyphics.",
      "But he will need time.",
      "It is best if you continue your quest.",
      "I will wait for you here and inform you of his progress.",
      "Please visit us occasionally.",
      "I am sure that will please Master Marik.",
      "Please give my regards to Mistress Ishizu."
  )
  SET_FLAG(EVENT_FLAG_EXITED_MARIKS_HOME)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAAC, map_59_state_02_08EFDAAC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Since you arrived, Master Marik has been chanting",
      "devoutly.",
      "He is chanting to atone for his past sins."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAB8, map_59_state_02_08EFDAB8, 0x08EFDAC4, 0x08F0404C)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You dare enter my haven of traps?",
      "Fine! We shall duel!"
  )
  DUEL(DUELIST_ODION_157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EFDAC4, map_59_state_02_08EFDAC4, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_EGYPT)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Gah! Your fighting spirit is most impressive!")
  FALLTHROUGH()
END_EVENT_SCRIPT()
