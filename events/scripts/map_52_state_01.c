#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_52_state_01: map 52 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EE62A0, map_52_state_01_08EE62A0, 0x08EE62AC, 0x08EE62D0)
  LOAD_SPRITE(1, SPRITE_INVISIBLE)
  LOAD_SPRITE(2, SPRITE_SHADI)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_SHADIS_PORTRAIT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62AC, map_52_state_01_08EE62AC, 0x08EE62B8, 0x08EE62C4)
  SET_FLAG(EVENT_FLAG_TALKED_TO_SHADIS_PORTRAIT)
  PLAY_MUSIC(MUSIC_406)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(0, 44)
  WALK_OBJECT_X(0, 72)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(2, 60, 44, 0, 1, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(32)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You have traveled far...\n"
      "There is but a little more\n\n"
      "to go.\n\n"
      "I implore that you save\n"
      "Pegasus...\n\n"
      "Or Sol Chevalsky, as he now\n"
      "calls himself.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My tale is long. Will you\n"
      "hear me out?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62B8, map_52_state_01_08EE62B8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "To learn the truth takes\n"
      "courage...\n\n"
      "Hear my tale of the tragedy\n"
      "of Pegasus.\n\n"
      "Time passed since Duelist\n"
      "Kingdom...\n\n"
      "Pegasus awoke from his long\n"
      "dream...\n\n"
      "He wandered the globe, drawn\n"
      "by an unseen power.\n\n"
      "He visited many ancient\n"
      "ruins until his journey led\n\n"
      "him to Egypt.\n\n"
      "By chance, he found a stone\n"
      "tablet.\n\n"
      "Sealed within it was Reshef\n"
      "the Dark Being.\n\n"
      "And thus began Pegasus's\n"
      "tragedy.\n\n"
      "He slowly deciphered the\n"
      "stone tablet...\n\n"
      "And realized the calamity it\n"
      "could unleash.\n\n"
      "It could bring eternal\n"
      "darkness to the world...\n\n"
      "So Pegasus was determined to\n"
      "prevent Reshef's escape.\n\n"
      "As he further studied the\n"
      "stone tablet...\n\n"
      "He was unaware that he was\n"
      "falling under Reshef's\n\n"
      "spell...\n\n"
      "The Egyptian God Cards are\n"
      "needed to seal the stone\n\n"
      "tablet...\n\n"
      "But they can also be used to\n"
      "resurrect Reshef.\n\n"
      "Pegasus sought the Egyptian\n"
      "God Cards to seal Reshef\n\n"
      "forever...\n\n"
      "But, under Reshef's spell,\n"
      "he did the exact opposite.\n\n"
      "He used the Egyptian God\n"
      "Cards in a resurrection\n\n"
      "ritual...\n\n"
      "Which freed Reshef and\n"
      "turned the Egyptian God\n\n"
      "Cards to stone.\n\n"
      "The Millennium Items were\n"
      "also scattered across the\n\n"
      "globe.\n\n"
      "Pegasus is now fully under\n"
      "Reshef's control.\n\n"
      "{PLAYER}, you must not hate\n"
      "Pegasus.\n\n"
      "Hatred makes your spirit as\n"
      "tainted as Reshef's.\n\n"
      "You must enter the final\n"
      "battle with a pure spirit.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_TELEPORT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62C4, map_52_state_01_08EE62C4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I understand you are in a\n"
      "hurry. So be it.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_TELEPORT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62D0, map_52_state_01_08EE62D0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Shadi no longer appears...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
