#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_06: map 0 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E34B50, map_00_state_06_08E34B50, 0x08E34B5C, 0x08E34BB0)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_SETO)
  LOAD_SPRITE(3, SPRITE_MOKUBA)
  LOAD_SPRITE(4, SPRITE_TRISTAN)
  LOAD_SPRITE(5, SPRITE_SERENITY)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_EYE_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B5C, map_00_state_06_08E34B5C, 0x08E34B68, 0x08F04040)
  WALK_OBJECT_Y(0, 32)
  WALK_OBJECT_X(0, 48)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 42)
  WALK_OBJECT_X(13, 54)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 42)
  WALK_OBJECT_X(14, 42)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I could not foretell that\n"
      "Sol Chevalsky was actually\n\n"
      "Maximillion Pegasus...\n\n"
      "He has been missing since\n"
      "Duelist Kingdom...\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What could have happened to\n"
      "him during all this time?\n\n"
      "We cannot worry about this\n"
      "now. Let's resurrect an\n\n"
      "Egyptian God Card.\n\n"
      "With the powers of the\n"
      "Millennium Ring and\n\n"
      "Millennium Eye...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B68, map_00_state_06_08E34B68, 0x08E34B74, 0x08F04040)
  PLAY_MUSIC(MUSIC_290)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_OBELISK_REVIVAL)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B74, map_00_state_06_08E34B74, 0x08E34B80, 0x08E34B8C)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Obelisk the Tormentor\n"
      "has regained its power.\n\n"
      "However."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "Egyptian God\n"
      "Cards choose their bearers.\n\n"
      "It appears that Obelisk will\n"
      "not accept you.\n\n"
      "It seems you are not yet\n"
      "ready to control its\n\n"
      "immense powers.\n\n"
      "The card has chosen as its\n"
      "bearer...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  WALK_OBJECT_X(2, 48)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_X(3, 40)
  MOVE_OBJECT(3, DIRECTION_UP, 0, 0)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Enough of this bogus mystic\n"
      "talk!\n\n"
      "It's obvious who deserves to\n"
      "control Obelisk!\n\n"
      "Who else but me!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Don't bet on it!\n"
      "I guess so...{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B80, map_00_state_06_08E34B80, 0x08E34B98, 0x08F04040)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, OBJECT_3)
  DELAY(8)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't bet on it? Don't talk\n"
      "to my brother that way!\n\n"
      "If it wasn't for my\n"
      "brother...\n\n"
      "You wouldn't have won the\n"
      "tag duel!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B98, map_00_state_06_08E34B98, 0x08E34BA4, 0x08F04040)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 40)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(0, DIRECTION_LEFT, 8, 0)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  WALK_OBJECT_Y(2, 32)
  DELAY(43)
  PLAY_MUSIC(MUSIC_285)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I don't care what you\n"
      "amateurs think...\n\n"
      "If you have a problem, come\n"
      "out and say it!\n\n"
      "Try to defeat me and take\n"
      "Obelisk!\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Though I don't know how a\n"
      "bunch of incompetent fools\n\n"
      "are ever going to beat me!\n\n"
      "Wahahahahahaha!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 64)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_X(2, 128)
  WALK_OBJECT_Y(3, 64)
  WALK_OBJECT_X(3, 128)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You cannot deny destiny...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You must wait until it is\n"
      "your time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BA4, map_00_state_06_08E34BA4, 0x08F04040, 0x08F04040)
  WALK_OBJECT_Y(4, 64)
  WALK_OBJECT_X(4, 48)
  WALK_OBJECT_Y(4, 52)
  DELAY(16)
  PLAY_MUSIC(MUSIC_HAPPY_CUTSCENE)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hey, {PLAYER}!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hey, what's up, Tristan?\n"
      "What are you doing here?\n\n"
      "Nothin' betta have happened\n"
      "to Serenity!\n\n"
  )
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Uh... Well, actually,\n"
      "yeah... That's...what I'm\n\n"
      "here about.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Say what?! What happened to\n"
      "my sister!\n\n"
  )
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Well...\n\n"
      "She really wants to see the\n"
      "Kaibaman show.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Kaibaman show? What the\n"
      "heck is that?\n\n"
  )
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You haven't heard of it?\n\n"
      "It's the biggest thing right\n"
      "now! Kids love it! Get with\n\n"
      "the times, man!\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Well, I don't like anything\n"
      "with the name Kaiba in\n\n"
      "it...\n\n"
      "But if Serenity wants to go,\n"
      "I guess I'll take her.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh, but I can't just abandon\n"
      "my duties without\n\n"
      "permission.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, can I take some\n"
      "time off?\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hahaha...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'm sorry for laughing.\n\n"
      "A little time off will help\n"
      "you relax and rekindle your\n\n"
      "spirits.\n\n"
      "Perhaps you can all go see\n"
      "the show.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah! You know what's up,\n"
      "Ishizu!\n\n"
      "All right. I'd better find\n"
      "Serenity and...\n\n"
  )
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I thought you'd say that, so\n"
      "I already brought her.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Serenity, come on in.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(5, 64)
  WALK_OBJECT_X(5, 40)
  WALK_OBJECT_Y(5, 52)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Joey, can I really go?\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "No doubt!\n\n"
  )
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Thank you, Joey!\n\n"
      "I'll go ahead and save us a\n"
      "spot.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(5, 64)
  WALK_OBJECT_X(5, 128)
  MOVE_OBJECT(4, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_TRISTAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Kaibaman show is being\n"
      "shown in front of\n\n"
      "KaibaCorp.\n\n"
      "Now you shouldn't keep a\n"
      "lady waiting, especially\n\n"
      "Serenity.\n\n"
      "I'm outta here.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(4, 64)
  WALK_OBJECT_X(4, 60)
  WALK_OBJECT_Y(4, 96)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We should go too.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(0, 48)
  WALK_OBJECT_Y(0, 52)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_EYE_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B8C, map_00_state_06_08E34B8C, 0x08E34B98, 0x08F04040)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Heh. You finally realize\n"
      "you're not in my league.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34BB0, map_00_state_06_08E34BB0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Serenity is waiting for you.\n\n"
      "She should be at Kaiba\n"
      "Corporation.\n\n"
      "Weren't you going to see the\n"
      "Kaibaman show?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
