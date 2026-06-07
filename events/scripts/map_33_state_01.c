#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_33_state_01: map 33 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EBEACC, map_33_state_01_08EBEACC, 0x08EBEAE4, 0x08EBEB20)
  LOAD_SPRITE(1, SPRITE_MILLENNIUM_GUARDIAN)
  LOAD_SPRITE(2, SPRITE_PEGASUS)
  LOAD_SPRITE(3, SPRITE_MILLENNIUM_EYE)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEAE4, map_33_state_01_08EBEAE4, 0x08EBEAF0, 0x08F0404C)
  PLAY_MUSIC(MUSIC_402)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Those drawn by the\n"
    "Millennium Item...\n\n"
    "Prove your worth at this\n"
    "fortress of the ancients!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(0, 64)
  WALK_OBJECT_X(0, 60)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 74)
  WALK_OBJECT_X(13, 66)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 74)
  WALK_OBJECT_X(14, 54)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  DUEL(DUELIST_MILLENNIUM_GUARDIAN_042)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEAF0, map_33_state_01_08EBEAF0, 0x08EBEAFC, 0x08EBEB08)
  PLAY_MUSIC(MUSIC_402)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Impressive. Take this item.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_316)
  SHOW_OBJECT(3, 60, 40, 0, 0, 0)
  DELAY(48)
  PLAY_MUSIC(MUSIC_278)
  SLIDE_OBJECT(3, 0, 18)
  DELAY(8)
  PLAY_MUSIC(MUSIC_279)
  SHOW_OBJECT(3, 128, 96, 0, 0, 0)
  DELAY(48)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(2, 60, 54, 0, 1, 0)
  DELAY(16)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_LEFT,
    "Oh! This is unbelievable!\n\n"
    "Who is it? Who's tapping\n"
    "into my memory?\n\n"
)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_LEFT,
    "W-what? It's Sol Chevalsky!\n\n"
)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_LEFT,
    "There's something wrong!\n\n"
    "Pegasus is the one with the\n"
    "Millennium Eye...\n\n"
    "{PLAYER}, could this be...\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "{CARD_1}It's Pegasus!\n"
    "It's Sol Chevalsky!{CARD_2}\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEAFC, map_33_state_01_08EBEAFC, 0x08EBEB14, 0x08F04040)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Pegasus... That name brings\n"
    "back memories.\n\n"
    "But my name is now Sol\n"
    "Chevalsky.\n\n"
    "I have been, shall we say,\n"
    "reborn.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB14, map_33_state_01_08EBEB14, 0x08F04250, 0x08F04040)
  TEXT
  (
      "I see that you are making\n"
      "excellent progress through\n\n"
      "my game.\n\n"
      "I suggest you keep\n"
      "playing... as if you had a\n\n"
      "choice!\n\n"
      "I know you still have\n"
      "questions of my\n\n"
      "intentions...\n\n"
      "Maybe they will be answered\n"
      "when you reach me.\n\n"
      "Hahahaha...\n\n"
  )
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_TELEPORT)
  DELAY(64)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_LEFT,
    "Sol Chevalsky is Pegasus...\n\n"
    "Let's get back to Ishizu.\n\n"
)
  SET_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB08, map_33_state_01_08EBEB08, 0x08EBEB14, 0x08F04040)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Ah, you are very insightful,\n"
    "my boy.\n\n"
    "You are exactly right. I am\n"
    "Sol Chevalsky.\n\n"
    "The name Pegasus is in the\n"
    "past. It no longer has\n\n"
    "anything to do with me.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB20, map_33_state_01_08EBEB20, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Millennium Items are\n"
    "believed to attract each\n\n"
    "other.\n\n"
    "The Millennium Eye will lead\n"
    "you to the next one.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEAD8, map_33_state_01_08EBEAD8, 0x08EBEAE4, 0x08EBEB2C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB2C, map_33_state_01_08EBEB2C, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You are only allowed to duel\n"
    "me once.\n\n"
    "Did you not have to leave\n"
    "immediately?\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
