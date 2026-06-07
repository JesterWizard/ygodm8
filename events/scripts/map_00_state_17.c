#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_17: map 0 state 17 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E34E20, map_00_state_17_08E34E20, 0x08E34E2C, 0x08E34E44)
  LOAD_SPRITE(1, SPRITE_ESPA)
  LOAD_SPRITE(2, SPRITE_ROBA_BROTHER_1)
  LOAD_SPRITE(3, SPRITE_ROBA_BROTHER_2)
  LOAD_SPRITE(4, SPRITE_ROBA_BROTHER_3)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_ESPA_ROBA2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E2C, map_00_state_17_08E34E2C, 0x08E34E38, 0x08F0404C)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
    "Pipipi...\n\n"
)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Who are you fighting?\n\n"
    "Actually, don't tell me.\n"
    "Duelists don't communicate\n\n"
    "with words. We communicate\n"
    "with cards!\n\n"
    "Don't underestimate my\n"
    "Psychic Power deck!\n\n"
)
  DUEL(DUELIST_ESPA_ROBA_084)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E38, map_00_state_17_08E34E38, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
    "Pipipi... You win.\n\n"
)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I don't know who you're\n"
    "fighting, but take my Jinzo\n\n"
    "with you.\n\n"
    "This card represents my\n"
    "spirit.\n\n"
    "Your fight is far from over,\n"
    "but... Pipipi...\n\n"
    "Yes. I sense you'll be fine.\n\n"
    "A duelist becomes more\n"
    "powerful when he has\n\n"
    "friends supporting him.\n\n"
    "So think of Jinzo as me.\n\n"
    "As long as you have my help,\n"
    "you're not fighting alone!\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Received Jinzo."
)
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  PAGE_BREAK()
  ADD_CARD(752)
  SET_FLAG(EVENT_FLAG_DEFEATED_ESPA_ROBA2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E44, map_00_state_17_08E34E44, 0x08E34E50, 0x08F0404C)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
    "If you think dueling me will\n"
    "help you improve...\n\n"
    "Then I'll be happy to duel\n"
    "you!\n\n"
)
  DUEL(DUELIST_ESPA_ROBA_146)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E50, map_00_state_17_08E34E50, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
    "A duelist's greatest\n"
    "strength is his potential.\n\n"
    "The hope we instill in our\n"
    "cards makes our decks\n\n"
    "powerful.\n\n"
    "Pipipi...\n\n"
    "I don't have to read the\n"
    "cosmic forces to know that\n\n"
    "you're a more skilled\n"
    "duelist than before!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
