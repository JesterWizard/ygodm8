#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_08: map 22 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E8CBB8, map_22_state_08_08E8CBB8, 0x08E8CBC4, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SETO)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  LOAD_SPRITE(3, SPRITE_PARA)
  LOAD_SPRITE(4, SPRITE_DOX_FLIPPING)
  LOAD_SPRITE(5, SPRITE_ISHIZU)
  LOAD_SPRITE(6, SPRITE_MILLENNIUM_GUARDIAN)
  PLAY_MUSIC(MUSIC_405)
  DELAY(32)
  WALK_OBJECT_X(2, 52)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Big brother!\n\n"
      "Most of the Neo Ghouls have\n"
      "left the Town of Domino.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Good.\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "I protected KaibaCorp, just\n"
      "like you told me.\n\n"
      "So you don't have to worry\n"
      "about a thing.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Good work, Mokuba.\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Heheh, thanks. You know I'll\n"
      "do anything for you.\n\n"
      "So, anything new with your\n"
      "Egyptian God Card?\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Somehow, it's back to\n"
      "normal.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(32)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "I don't know what they did,\n"
      "but...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBC4, map_22_state_08_08E8CBC4, 0x08E8CBD0, 0x08F04040)
  PLAY_MUSIC(MUSIC_404)
  WALK_OBJECT_X(4, 48)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SURPRISED, PORTRAIT_LEFT)
  TEXT
  (
      "Urk! S-Seto...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  SET_OBJECT_POSITION(2, 128, 96, 0)
  PLAY_MUSIC(MUSIC_314)
  LOAD_SPRITE(4, SPRITE_DOX_WITH_MOKUBA)
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, 6, PORTRAIT_RIGHT)
  TEXT
  (
      "How dare you... What's the\n"
      "meaning of this?\n\n"
  )
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "Seto Kaiba! I have a message\n"
      "from Master Chevalsky!\n\n"
      "Come to my castle.\n\n"
      "If you want to save your\n"
      "dear brother.\n\n"
      "You have no choice but to\n"
      "come to my castle!\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 5, PORTRAIT_RIGHT)
  TEXT
  (
      "You worm!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
  PLAY_MUSIC(MUSIC_277)
  SLIDE_OBJECT(4, 1, 8)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBD0, map_22_state_08_08E8CBD0, 0x08E8CBDC, 0x08F04040)
  DELAY(16)
  SET_OBJECT_POSITION(3, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(3, 24)
  WALK_OBJECT_X(3, 80)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "Younger brother, you have\n"
      "fulfilled your mission!\n\n"
      "Master Chevalsky will\n"
      "promote you to a higher\n\n"
      "position!\n\n"
  )
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "Elder brother, you also have\n"
      "done your job with most\n\n"
      "excellence!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_RIGHT)
  TEXT
  (
      "You punks! How dare you mock\n"
      "me!\n\n"
  )
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "Fufufufufufu...\n\n"
  )
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "Fufufufufufu...\n\n"
  )
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Master Chevalsky demands\n"
      "your presence, Kaiba!\n\n"
  )
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Come to Master Chevalsky's\n"
      "castle!\n\n"
  )
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "The castle that you...\n\n"
  )
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "...Know so well! Fufufu...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_315)
  SLIDE_OBJECT(3, 1, 96)
  PLAY_MUSIC(MUSIC_315)
  SLIDE_OBJECT(4, 1, 64)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_RIGHT)
  TEXT
  (
      "Mokuba!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 4, 0)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBDC, map_22_state_08_08E8CBDC, 0x08E8CBE8, 0x08E8CBF4)
  SET_OBJECT_POSITION(0, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(0, 24)
  WALK_OBJECT_X(0, 82)
  DELAY(16)
  SET_OBJECT_POSITION(13, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(13, 18)
  WALK_OBJECT_X(13, 87)
  DELAY(16)
  SET_OBJECT_POSITION(14, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(14, 30)
  WALK_OBJECT_X(14, 87)
  DELAY(16)
  SET_OBJECT_POSITION(5, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(5, 24)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  WALK_OBJECT_X(0, 77)
  DELAY(16)
  TEXT
  (
      "{CARD_1}Let us help!\n"
      "Lend us your God Card!{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBE8, map_22_state_08_08E8CBE8, 0x08E8CC00, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER} is right, Kaiba.\n\n"
      "Now is the time for\n"
      "teamwork.\n\n"
      "The Dark Being must be\n"
      "sealed again...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "Quiet, you!\n\n"
      "I'm never going to cooperate\n"
      "with you!\n\n"
      "I'll crush Pegasus on my own\n"
      "and get Mokuba back!\n\n"
      "How many times do I have to\n"
      "say that I don't have time\n\n"
      "for your so-called ancient\n"
      "magic!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CC00, map_22_state_08_08E8CC00, 0x08F04040, 0x08F04040)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 0)
  SET_OBJECT_POSITION(1, 128, 96, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "We're left with no choice.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "We must also go to Sol\n"
      "Chevalsky's... I mean...\n\n"
      "We must also go to Pegasus's\n"
      "castle.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "But who knows where the\n"
      "castle is?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_5 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PLAY_MUSIC(MUSIC_402)
  WALK_OBJECT_X(6, 48)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_5)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "You have proven yourselves\n"
      "to the Millennium Items.\n\n"
      "Trace the flow of time and\n"
      "accept your destiny.\n\n"
      "One man knows where you must\n"
      "go.\n\n"
      "You must seek out Paradox.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Paradox awaits you in China.\n\n"
      "He will show you the way.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(6, DIRECTION_LEFT, 64, 0)
  DELAY(32)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "The Millennium Guard comes\n"
      "from the order that\n\n"
      "protects the Millennium\n"
      "Items...\n\n"
      "I sensed that he was telling\n"
      "the truth.\n\n"
      "{PLAYER}, you must go to\n"
      "China.\n\n"
      "As soon as possible.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  WALK_OBJECT_X(5, 0)
  SET_OBJECT_POSITION(5, 128, 96, 0)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "I'm worried about Mokuba and\n"
      "Kaiba...\n\n"
      "We'd better find Pegasus's\n"
      "castle quickly.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Yugi's right.\n\n"
      "If this Parachute guy can\n"
      "help us...\n\n"
      "We'd betta find him quick.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "That's Paradox, Joey.\n"
      "Not Parachute.\n\n"
      "{PLAYER}, let's go! We're\n"
      "off to China!\n\n"
  )
  HIDE_PORTRAIT()
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  SET_FLAG(EVENT_FLAG_SAW_MOKUBA_GET_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBF4, map_22_state_08_08E8CBF4, 0x08E8CC00, 0x08F04040)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "Don't make me laugh,\n"
      "{PLAYER}!\n\n"
      "Reshef the Dark Being... The\n"
      "end of the world...\n\n"
      "You've been reading too many\n"
      "fantasy novels!\n\n"
      "You guys do what you want!\n\n"
      "But I'll get Mokuba back on\n"
      "my own!\n\n"
      "And nobody is going to stop\n"
      "me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
