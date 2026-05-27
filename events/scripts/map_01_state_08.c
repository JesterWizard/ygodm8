#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_01_state_08: map 1 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E428B0, map_01_state_08_08E428B0, 0x08E428BC, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_TEA)
  LOAD_SPRITE(2, SPRITE_JOHNNY_STEPS)
  LOAD_SPRITE(3, SPRITE_NIGHTMARE_PENGUIN)
  LOAD_SPRITE(4, SPRITE_RED_HAT)
  LOAD_SPRITE(5, SPRITE_STYLISH_HAIR)
  WALK_OBJECT_X(0, 26)
  WALK_OBJECT_Y(0, 48)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  WALK_OBJECT_X(13, 16)
  WALK_OBJECT_Y(13, 54)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  WALK_OBJECT_X(14, 16)
  WALK_OBJECT_Y(14, 42)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "Sigh...\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "What's wrong, Tea? Why the\n"
      "big sigh?\n\n"
  )
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Well...\n\n"
      "I had a famous fortuneteller\n"
      "do my reading.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "You had your fortune told?\n\n"
  )
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "Sigh...\n\n"
      "Yes, and... well...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  SET_OBJECT_POSITION(2, 36, 96, 0)
  WALK_OBJECT_Y(2, 60)
  DELAY(8)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(6)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
  DELAY(16)
  PLAY_MUSIC(MUSIC_JEAN_CLAUDE_MAGNUM)
  TEXT
  (
      "Hey good-lookin'! Why don't\n"
      "you mosey on over here to\n\n"
      "my arm?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "...\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Ooh, she looks feisty, but\n"
      "she's a shy one. Just the\n\n"
      "way I like it!\n\n"
  )
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "{PLAYER}... You'll get rid\n"
      "of this jerk for me, right?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E428BC, map_01_state_08_08E428BC, 0x08E428D4, 0x08E428C8)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E428D4, map_01_state_08_08E428D4, 0x08E428E0, 0x08F0404C)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  TEXT
  (
      "What do you want?\n\n"
      "You think you can beat me in\n"
      "a duel?\n\n"
      "Hah, that's hilarious!\n\n"
      "Okay baby, you'll be mine\n"
      "after I dance all over this\n\n"
      "joker!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 26)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  DUEL(DUELIST_TEA_132)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E428E0, map_01_state_08_08E428E0, 0x08E428EC, 0x08F04040)
  PLAY_MUSIC(MUSIC_JEAN_CLAUDE_MAGNUM)
  TEXT
  (
      "I wish you could have seen\n"
      "my dance steps!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 72)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(6)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(6)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  WALK_OBJECT_Y(2, 96)
  DELAY(32)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What was up with dat guy?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E428EC, map_01_state_08_08E428EC, 0x08E428F8, 0x08F0404C)
  HIDE_PORTRAIT()
  DELAY(16)
  SET_OBJECT_POSITION(3, 36, 0, 0)
  WALK_OBJECT_Y(3, 32)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  PLAY_MUSIC(MUSIC_BIG_FIVE)
  PORTRAIT(PORTRAIT_NIGHTMARE_PENGUIN, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "A-ha! I've found you at\n"
      "last, Tea Gardner!!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_NIGHTMARE_PENGUIN, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "The fortuneteller said\n"
      "you'll bring me luck, so I\n\n"
      "want you working for me!!\n\n"
  )
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I don't think so! Take you\n"
      "and your tux somewhere\n\n"
      "else!\n\n"
  )
  PORTRAIT(PORTRAIT_NIGHTMARE_PENGUIN, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "On the contrary!\n\n"
      "You're my last chance to\n"
      "rekindle my dream...\n\n"
      "My dream of making Penguin\n"
      "Land!\n\n"
      "And you're going to help me!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, OBJECT_1)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Forget it, creep!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, can you get rid of\n"
      "this guy, too?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_3)
  DELAY(16)
  PORTRAIT(PORTRAIT_NIGHTMARE_PENGUIN, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "A duel? Fine! A duel it is!\n\n"
      "My calculations state that\n"
      "the odds of you winning are\n\n"
      "a billion to one!\n\n"
      "And then Tea will be working\n"
      "for me!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(3, 26)
  MOVE_OBJECT(3, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DUEL(DUELIST_NIGHTMARE_PENGUIN_133)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E428F8, map_01_state_08_08E428F8, 0x08E42904, 0x08F04040)
  PLAY_MUSIC(MUSIC_BIG_FIVE)
  PORTRAIT(PORTRAIT_NIGHTMARE_PENGUIN, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "You should learn to respect\n"
      "your elders, even if\n\n"
      "they're penguins!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(3, 36)
  MOVE_OBJECT(3, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_NIGHTMARE_PENGUIN, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "And believe me, Tea! My\n"
      "feathered friends are cuter\n\n"
      "than you!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(3, 0)
  SET_OBJECT_POSITION(3, 128, 96, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_1 | OBJECT_13 | OBJECT_14)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42904, map_01_state_08_08E42904, 0x08F04040, 0x08F04040)
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wh-what's going on? This\n"
      "world is full of\n\n"
      "weirdoes...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "It's just what the\n"
      "fortuneteller predicted.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_13)
  DELAY(16)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Oh, yeah, you were saying\n"
      "something about your\n\n"
      "fortune before those guys\n"
      "showed up.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "The fortuneteller predicted\n"
      "that I would have the worst\n\n"
      "luck with men today.\n\n"
      "And he was right on the\n"
      "money.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_RIGHT)
  TEXT
  (
      "Yeah, men don't get any\n"
      "worse than them.\n\n"
  )
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "I'm going to lay low for the\n"
      "rest of the day. I don't\n\n"
      "want to run into any more\n"
      "psychos.\n\n"
      "I'll be back at Yugi's\n"
      "grandpa's shop...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 64)
  WALK_OBJECT_X(1, 0)
  SET_OBJECT_POSITION(1, 128, 96, 0)
  SET_FLAG(EVENT_FLAG_TEA_WENT_BACK_TO_THE_SHOP)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E428C8, map_01_state_08_08E428C8, 0x08E428BC, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "...Just my luck...\n\n"
      "I get hit on by a weirdo,\n"
      "and {PLAYER} won't help\n\n"
      "me...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "{PLAYER}, we should help\n"
      "her.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_RIGHT)
  TEXT
  (
      "{PLAYER}, I'm tellin' ya,\n"
      "think of the consequences.\n\n"
      "Tea is the toughest girl I\n"
      "know, and she's not gonna\n\n"
      "let the fact that you didn't\n"
      "help her slide by.\n\n"
      "Between me and you, I'd say\n"
      "you should help Tea.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()
