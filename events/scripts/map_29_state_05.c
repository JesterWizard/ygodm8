#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_29_state_05: map 29 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08EAC8D0, map_29_state_05_08EAC8D0, 0x08EAC8DC, 0x08F0404C)
  LOAD_SPRITE(1, SPRITE_BONZ)
  LOAD_SPRITE(2, SPRITE_NEO_GHOUL)
  PLAY_MUSIC(MUSIC_NEO_GHOULS)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "You're defying Master Keith's orders?",
      "After he was willing to let you join him, just like old",
      "times!"
  )
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "He never treated me with respect!",
      "I don't trust him!"
  )
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "You fool! Pledge your allegiance to Bandit Keith!",
      "If you do, he's willing to let you use all the rare",
      "cards you want."
  )
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "I'm not afraid of him anymore!")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(0, 56)
  WALK_OBJECT_X(13, 46)
  WALK_OBJECT_X(14, 46)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2)
  DELAY(8)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Tsk, the cavalry arrives!",
      "I'll take care of them first!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 66)
  DELAY(16)
  DUEL(DUELIST_NEO_GHOUL_065)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC8DC, map_29_state_05_08EAC8DC, 0x08EAC8E8, EVENT_NOP)
  PLAY_MUSIC(MUSIC_241)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Grah! You'll regret this!")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 57)
  WALK_OBJECT_X(2, 248)
  WALK_OBJECT_Y(1, 54)
  MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Th-thanks for saving me!",
      "Honestly, I was a little scared.",
      "But you guys... Why are you here?"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC8E8, map_29_state_05_08EAC8E8, 0x08EAC8F4, 0x08EAC900)
  PLAY_MUSIC(SOUND_NONE)
  PLAY_MUSIC(MUSIC_702)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "I didn't know that was going on in town!",
      "The Neo Ghouls don't scare me anymore.",
      "I'm a much better duelist! I'll help you, too.",
      "I'll go to the Town of Domino! The Neo Ghouls",
      "don't stand a ghost of a chance!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 51)
  WALK_OBJECT_X(1, 248)
  DELAY(16)
  SET_FLAG(EVENT_FLAG_DEFEATED_BONZ_GHOUL)
  CONDITION_CHECK(0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC8F4, map_29_state_05_08EAC8F4, EVENT_NOP, EVENT_NOP)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Let's go find another ally!")
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC900, map_29_state_05_08EAC900, EVENT_NOP, EVENT_NOP)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Okay! Let's also get back to the Town of Domino!")
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_FOUND_ALL_ALLIES)
  FALLTHROUGH()
END_EVENT_SCRIPT()
