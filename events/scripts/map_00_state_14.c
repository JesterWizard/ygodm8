#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_14: map 0 state 14 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E34EC8, map_00_state_14_08E34EC8, 0x08E34ED4, 0x08E34EE0)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_ESPA)
  LOAD_SPRITE(3, SPRITE_ROBA_BROTHER_1)
  LOAD_SPRITE(4, SPRITE_ROBA_BROTHER_2)
  LOAD_SPRITE(5, SPRITE_ROBA_BROTHER_3)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_PARADOX_ABOUT_RA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34ED4, map_00_state_14_08E34ED4, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You must ask Paradox where\n"
    "Pegasus's castle is.\n\n"
    "Paradox is in China.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34EE0, map_00_state_14_08E34EE0, 0x08E34EEC, 0x08E34EF8)
  CHECK_FLAG(EVENT_FLAG_ISHIZU_SAID_TO_GO_SEE_MARIK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34EEC, map_00_state_14_08E34EEC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Did you meet Paradox?\n\n"
)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Well...\n\n"
)
  HIDE_PORTRAIT()
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I see...\n\n"
    "Only two men have deciphered\n"
    "the ancient hieroglyphics\n\n"
    "needed to awaken Ra..\n\n"
    "The first is Kaiba.\n"
    "But he is...\n\n"
)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "He went after Mokuba.\n\n"
)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Then we just hafta meet the\n"
    "other guy.\n\n"
)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The other... Is my brother\n"
    "Marik.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Ah... That makes sense.\n\n"
    "The Winged Dragon of Ra\n"
    "belonged to Marik.\n\n"
)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Marik is living a new life\n"
    "in Egypt.\n\n"
    "Please see him there.\n\n"
)
  SET_FLAG(EVENT_FLAG_ISHIZU_SAID_TO_GO_SEE_MARIK)
  SET_FLAG(EVENT_FLAG_UNLOCKED_EGYPT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34EF8, map_00_state_14_08E34EF8, 0x08E34F04, 0x08E34F10)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MARIK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34F04, map_00_state_14_08E34F04, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Has The Winged Dragon of Ra\n"
    "awoken?\n\n"
    "Please meet my brother Marik\n"
    "in Egypt.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34F10, map_00_state_14_08E34F10, 0x08E34F1C, 0x08E34F28)
  CHECK_FLAG(EVENT_FLAG_SAW_PARADOX_FLEE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34F1C, map_00_state_14_08E34F1C, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "It appears that Marik has\n"
    "awakened Ra.\n\n"
    "There is no time to waste.\n\n"
    "You must once again visit\n"
    "Paradox in China.\n\n"
    "He knows where Pegasus's\n"
    "castle is.\n\n"
    "Find the location of the\n"
    "castle and stop the Dark\n\n"
    "Being.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34F28, map_00_state_14_08E34F28, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You must once again visit\n"
    "Paradox in China.\n\n"
    "He knows the location of\n"
    "Pegasus's castle.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34DFC, map_00_state_14_08E34DFC, 0x08E34E08, 0x08E34E14)
  CHECK_FLAG(EVENT_FLAG_ESPA_ROBA_THANKED_YOU_FOR_SAVING_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E08, map_00_state_14_08E34E08, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
    "Pipipi... You managed to\n"
    "save Ishizu.\n\n"
)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "But you still have a huge\n"
    "challenge ahead of you.\n\n"
    "I don't need psychic powers\n"
    "to predict this.\n\n"
    "I can tell just by the\n"
    "looking into your eyes.\n\n"
    "You'll be fine.\n"
    "Don't give up!\n\n"
)
  SET_FLAG(EVENT_FLAG_ESPA_ROBA_THANKED_YOU_FOR_SAVING_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E14, map_00_state_14_08E34E14, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
    "Pipipi...\n\n"
    "You're fighting to save the\n"
    "world.\n\n"
)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You'll be fine as long as\n"
    "you don't give up!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34EB0, map_00_state_14_08E34EB0, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I'm exhausted.\n"
    "I need to rest.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E5C, map_00_state_14_08E34E5C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "My big brother dueled great\n"
      "against the Neo Ghouls.\n\n"
      "He really showed them who's\n"
      "boss!\n\n"
      "He's the coolest guy I know!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E68, map_00_state_14_08E34E68, 0x08F04040, 0x08F04040)
  TEXT
  (
      "My big brother always\n"
      "says...\n\n"
      "A duelist becomes more\n"
      "powerful when he has\n\n"
      "friends supporting him.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E74, map_00_state_14_08E34E74, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I really like Espa! He's the\n"
      "best!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
