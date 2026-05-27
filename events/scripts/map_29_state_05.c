#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_29_state_05: map 29 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08EAC8D0, map_29_state_05_08EAC8D0, 0x08EAC8DC, 0x08F0404C)
  LOAD_SPRITE(1, SPRITE_BONZ)
  LOAD_SPRITE(2, SPRITE_NEO_GHOUL)
  PLAY_MUSIC(MUSIC_NEO_GHOULS)
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "You're defying Master\n"
      "Keith's orders?\n\n"
      "After he was willing to let\n"
      "you join him, just like old\n\n"
      "times!\n\n"
  )
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "He never treated me with\n"
      "respect!\n\n"
      "I don't trust him!\n\n"
  )
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "You fool! Pledge your\n"
      "allegiance to Bandit Keith!\n\n"
      "If you do, he's willing to\n"
      "let you use all the rare\n\n"
      "cards you want.\n\n"
  )
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I'm not afraid of him\n"
      "anymore!\n\n"
  )
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
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Tsk, the cavalry arrives!\n\n"
      "I'll take care of them\n"
      "first!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 66)
  DELAY(16)
  DUEL(DUELIST_NEO_GHOUL_065)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC8DC, map_29_state_05_08EAC8DC, 0x08EAC8E8, 0x08F04040)
  PLAY_MUSIC(MUSIC_241)
  PORTRAIT(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Grah! You'll regret this!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 57)
  WALK_OBJECT_X(2, 248)
  WALK_OBJECT_Y(1, 54)
  MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Th-thanks for saving me!\n\n"
      "Honestly, I was a little\n"
      "scared.\n\n"
      "But you guys... Why are you\n"
      "here?\n\n"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC8E8, map_29_state_05_08EAC8E8, 0x08EAC8F4, 0x08EAC900)
  PLAY_MUSIC(SOUND_NONE)
  PLAY_MUSIC(MUSIC_702)
  PORTRAIT(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I didn't know that was going\n"
      "on in town!\n\n"
      "The Neo Ghouls don't scare\n"
      "me anymore.\n\n"
      "I'm a much better duelist!\n"
      "I'll help you, too.\n\n"
      "I'll go to the Town of\n"
      "Domino! The Neo Ghouls\n\n"
      "don't stand a ghost of a\n"
      "chance!\n\n"
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

EVENT_SCRIPT_REPLACEMENT(0x08EAC8F4, map_29_state_05_08EAC8F4, 0x08F04040, 0x08F04040)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Let's go find another ally!\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC900, map_29_state_05_08EAC900, 0x08F04040, 0x08F04040)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Okay! Let's also get back to\n"
      "the Town of Domino!\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_FOUND_ALL_ALLIES)
  FALLTHROUGH()
END_EVENT_SCRIPT()
