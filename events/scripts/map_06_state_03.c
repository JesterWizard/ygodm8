#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_03: map 6 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CC78, map_06_state_03_08E5CC78, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_TRISTAN)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_LUCKY)
  LOAD_SPRITE(4, SPRITE_YUGI)
  LOAD_SPRITE(5, SPRITE_SERENITY)
  PLAY_MUSIC(MUSIC_HAPPY_CUTSCENE)
  DELAY(32)
  MOVE_OBJECT(5, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh,"
  )
  DELAY(16)
  TEXT
  (
      " big brother!\n\n"
      "Is your work for Ishizu\n"
      "going smoothly?\n\n"
  )
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_14)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Joey,\n"
  )
  DELAY(16)
  TEXT
  (
      "what's wrong?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(14, 48)
  WALK_OBJECT_X(14, 64)
  WALK_OBJECT_X(0, 72)
  WALK_OBJECT_X(13, 72)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Serenity, "
  )
  DELAY(16)
  TEXT
  (
      "uh...\n"
  )
  DELAY(16)
  TEXT
  (
      "Er, um...\n\n"
  )
  DELAY(16)
  TEXT
  (
      "Tell me da truth. Is there\n"
  )
  DELAY(16)
  TEXT
  (
      "anybody that you like?\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah.\n\n"
  )
  DELAY(16)
  TEXT
  (
      "There sure is.\n\n"
  )
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_14)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "S-"
  )
  DELAY(16)
  TEXT
  (
      "Serenity! "
  )
  DELAY(16)
  TEXT
  (
      "Are you serious?\n"
      "Do I know this guy?\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yup. "
  )
  DELAY(16)
  TEXT
  (
      "Tristan...\n\n"
  )
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_14)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_X(14, 52)
  DELAY(8)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What? "
  )
  DELAY(16)
  TEXT
  (
      "No! Anybody but him!\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What's wrong, Joey?\n\n"
      "There's Tristan... and\n"
      "Duke...\n\n"
      "And Yugi and {PLAYER}...\n\n"
      "I also like Tea and Mai.\n\n"
      "But I like you the best, big\n"
      "brother.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  WALK_OBJECT_X(1, 80)
  WALK_OBJECT_X(2, 80)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "B-"
  )
  DELAY(16)
  TEXT
  (
      "but...\n\n"
  )
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But "
  )
  DELAY(16)
  TEXT
  (
      "you said you liked\n"
      "strong duelists...\n\n"
  )
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_5)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Did I really say that?\n\n"
      "Well... come to think of\n"
      "it...\n\n"
      "I think it's coincidence\n"
      "that the people I like just\n\n"
      "happen to be good duelists.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Awwwww, man...\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 4, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Alright, ya idiots! Get\n"
      "outta here!\n\n"
      "Get back to work at the\n"
      "shop!\n\n"
  )
  SET_FLAG(EVENT_FLAG_UNLOCKED_MONKEY_ROBOT_SIDEQUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CC90, map_06_state_03_08E5CC90, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, "
  )
  DELAY(16)
  TEXT
  (
      "I know you can\n"
      "win.\n\n"
      "You have to fight for me,\n"
      "too!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CC9C, map_06_state_03_08E5CC9C, 0x08E5CCA8, 0x08F0404C)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I don't really feel like it,\n"
      "but I'll do anything for\n\n"
      "you, buddy!\n\n"
  )
  DUEL(DUELIST_TRISTAN_125)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CCA8, map_06_state_03_08E5CCA8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_GAME_SHOP)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Did that even count as\n"
      "practice?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CCB4, map_06_state_03_08E5CCB4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, "
  )
  DELAY(16)
  TEXT
  (
      "leave it to me!\n\n"
      "I'll keep an eye on Tristan.\n\n"
      "...Especially to make sure\n"
      "that he doesn't hit on\n\n"
      "Serenity!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CC6C, map_06_state_03_08E5CC6C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_4)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CC84, map_06_state_03_08E5CC84, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wouldn't it be great if we\n"
      "could stay friends forever?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
