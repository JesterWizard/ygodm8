#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_33_state_01: map 33 state 1 */


END()
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
      "Those drawn by the Millennium Item...",
      "Prove your worth at this fortress of the ancients!"
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
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Impressive. Take this item.")
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
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY,
      "Oh! This is unbelievable!",
      "Who is it? Who's tapping into my memory?"
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, "W-what? It's Sol Chevalsky!")
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED,
      "There's something wrong!",
      "Pegasus is the one with the Millennium Eye...",
      "{PLAYER}, could this be..."
  )
  TALK(PORTRAIT_NONE, "{CARD_1}It's Pegasus!\nIt's Sol Chevalsky!{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEAFC, map_33_state_01_08EBEAFC, 0x08EBEB14, EVENT_NOP)
  TALK(PORTRAIT_SOL_CHEVELSKY,
      "Pegasus... That name brings back memories.",
      "But my name is now Sol Chevalsky.",
      "I have been, shall we say, reborn."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB14, map_33_state_01_08EBEB14, 0x08F04250, EVENT_NOP)
  TEXT(
      "I see that you are making excellent progress through",
      "my game.",
      "I suggest you keep playing... as if you had a",
      "choice!",
      "I know you still have questions of my",
      "intentions...",
      "Maybe they will be answered when you reach me.",
      "Hahahaha..."
  )
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_TELEPORT)
  DELAY(64)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED,
      "Sol Chevalsky is Pegasus...",
      "Let's get back to Ishizu."
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB08, map_33_state_01_08EBEB08, 0x08EBEB14, EVENT_NOP)
  TALK(PORTRAIT_SOL_CHEVELSKY,
      "Ah, you are very insightful, my boy.",
      "You are exactly right. I am Sol Chevalsky.",
      "The name Pegasus is in the past. It no longer has",
      "anything to do with me."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB20, map_33_state_01_08EBEB20, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Millennium Items are believed to attract each",
      "other.",
      "The Millennium Eye will lead you to the next one."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEAD8, map_33_state_01_08EBEAD8, 0x08EBEAE4, 0x08EBEB2C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEB2C, map_33_state_01_08EBEB2C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You are only allowed to duel me once.",
      "Did you not have to leave immediately?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
