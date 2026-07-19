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
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO, "Pipipi...")
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Who are you fighting?",
      "Actually, don't tell me. Duelists don't communicate",
      "with words. We communicate with cards!",
      "Don't underestimate my Psychic Power deck!"
  )
  DUEL(DUELIST_ESPA_ROBA_084)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E38, map_00_state_17_08E34E38, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO, "Pipipi... You win.")
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I don't know who you're fighting, but take my Jinzo",
      "with you.",
      "This card represents my spirit.",
      "Your fight is far from over, but... Pipipi...",
      "Yes. I sense you'll be fine.",
      "A duelist becomes more powerful when he has",
      "friends supporting him.",
      "So think of Jinzo as me.",
      "As long as you have my help, you're not fighting alone!"
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
      "If you think dueling me will help you improve...",
      "Then I'll be happy to duel you!"
  )
  DUEL(DUELIST_ESPA_ROBA_146)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E50, map_00_state_17_08E34E50, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TALK(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_EYES_CLOSED, PORTRAIT_POSITION_AUTO,
      "A duelist's greatest strength is his potential.",
      "The hope we instill in our cards makes our decks",
      "powerful.",
      "Pipipi...",
      "I don't have to read the cosmic forces to know that",
      "you're a more skilled duelist than before!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
