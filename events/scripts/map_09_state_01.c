#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_09_state_01: map 9 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E62160, map_09_state_01_08E62160, 0x08E6216C, 0x08E62178)
  LOAD_SPRITE(1, SPRITE_INVISIBLE)
  LOAD_SPRITE(2, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(3, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(4, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(5, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(6, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(7, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(8, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(9, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(10, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(11, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(12, SPRITE_YUGI_UNUSED)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  SET_FLAG(EVENT_FLAG_SAW_INTRO_CUTSCENE)
  DELAY(32)
  LOAD_SPRITE(13, SPRITE_YUGI)
  LOAD_SPRITE(14, SPRITE_JOEY)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Now I put dis Monsta Card in\n"
      "here, like so...\n\n"
      "And voila!\n"
      "I'm good to go!\n\n"
  )
  HIDE_PORTRAIT()
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER}, how's adjustin'\n"
      "your deck comin' along?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Perfect\n"
      "Lousy{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6216C, map_09_state_01_08E6216C, 0x08E62184, 0x08F04040)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "You sure about dat?\n"
      "Let the expert, the\n\n"
      "one-and-only Joey Wheeler,\n"
      "check it out!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_LEFT)
  TEXT
  (
      "Uh... It's cool to be\n"
      "confident about your\n\n"
      "skills.\n\n"
      "But you still have lots of\n"
      "work to do on this Deck\n\n"
      "before it's any good.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Hey,\n"
      "don't feel bad. I know you\n\n"
      "can construct an awesome\n"
      "deck, {PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E62184, map_09_state_01_08E62184, 0x08E62190, 0x08E6219C)
  TEXT
  (
      "Alright guys, I'm gonna\n"
      "totally rock with this\n\n"
      "deck today!\n\n"
      "Man, I can't wait for the\n"
      "Duel Express train to come!\n\n"
      "It's been too long since\n"
      "I've dueled in a\n\n"
      "tournament!\n\n"
      "{PLAYER} and Yugi and I are\n"
      "gonna own this tourney!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}By the way...\n"
      "Let's go for it!{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E62190, map_09_state_01_08E62190, 0x08E621A8, 0x08F04040)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Huh, what's wrong? Oh yeah!\n"
      "Where the heck's Yugi?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621A8, map_09_state_01_08E621A8, 0x08E621B4, 0x08E621C0)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_LEFT, 32, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 32, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Oh man, this stinks!\n"
      "Look at the time already!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, OBJECT_14)
  DELAY(8)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_LEFT)
  TEXT
  (
      "He's late!\n\n"
      "C'mon Yugi...\n"
      "How can ya even think\n\n"
      "about being late on a day\n"
      "like this!\n\n"
      "If he doesn't get here\n"
      "soon, we'll miss the Duel\n\n"
      "Express!\n\n"
      "And he was the one who\n"
      "promised dat the three of\n\n"
      "us were gonna take the\n"
      "train together!\n\n"
      "Man, dat Yugi!\n"
      "Arrrrgh!\n\n"
      "If he doesn't get here, he\n"
      "can give me all his rare\n\n"
      "cards and I still won't\n"
      "forgive him!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_212)
  SHOW_OBJECT(13, 50, 74, 0, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 2, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_RIGHT)
  PLAY_MUSIC(MUSIC_400)
  TEXT
  (
      "{PLAYER}, everything's\n"
      "horrible!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  WALK_OBJECT_Y(13, 62)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 8, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_RIGHT)
  TEXT
  (
      "My other self...\n"
      "The Millennium Puzzle...\n\n"
      "My Puzzle is gone, along\n"
      "with the spirit inside!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_14)
  DELAY(8)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SAD, PORTRAIT_RIGHT)
  TEXT
  (
      "When I woke up this morning,\n"
      "it was gone...\n\n"
      "I... I... What am I\n"
      "supposed to do?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(64)
  WALK_OBJECT_Y(14, 56)
  WALK_OBJECT_X(14, 58)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Hey, we can't waste time\n"
      "standin' here and talkin'!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER}, whattaya think\n"
      "we should do?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Let's go look for it!\n"
      "Leave it to me!{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621B4, map_09_state_01_08E621B4, 0x08E621CC, 0x08F04040)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Okay! Then that's what\n"
      "we're gonna do! You got\n\n"
      "it, Yugi?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621CC, map_09_state_01_08E621CC, 0x08E621D8, 0x08F04040)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I won't stop until I find my\n"
      "dearest friend...\n\n"
      "I promise!\n\n"
      "I'm counting on you,\n"
      "{PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621D8, map_09_state_01_08E621D8, 0x08F04040, 0x08F04040)
  FADE_MUSIC(4)
  FADE_SCREEN(4)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTH, 1, 4, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621C0, map_09_state_01_08E621C0, 0x08E621CC, 0x08F04040)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Yeah! That's the spirit,\n"
      "{PLAYER}!\n\n"
      "Yugi, let's go with\n"
      "{PLAYER}!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6219C, map_09_state_01_08E6219C, 0x08E621A8, 0x08F04040)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Yeah! But don't think I'm\n"
      "gonna let you win\n\n"
      "{PLAYER}. And that goes\n"
      "double for Yugi.\n\n"
      "Speaking of who...\n"
      "Why isn't Yugi here yet?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E62178, map_09_state_01_08E62178, 0x08E62184, 0x08F04040)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER}, I guess ya still\n"
      "have lots of work to do.\n\n"
      "But you can learn from the\n"
      "expert, the one-and-only\n\n"
      "Joey Wheeler, on making\n"
      "great decks.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E62154, map_09_state_01_08E62154, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(SOUND_NONE)
  CUTSCENE(8)
  WARP(LOCATION_PLAYER_HOUSE_INSIDE, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
