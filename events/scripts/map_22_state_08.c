#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_08: map 22 state 8 */

LOAD_SPRITE(1, SPRITE_SETO)
LOAD_SPRITE(2, SPRITE_MOKUBA)
LOAD_SPRITE(3, SPRITE_PARA)
LOAD_SPRITE(4, SPRITE_DOX_FLIPPING)
LOAD_SPRITE(5, SPRITE_ISHIZU)
LOAD_SPRITE(6, SPRITE_MILLENNIUM_GUARDIAN)
PLAY_MUSIC(MUSIC_405)
DELAY(32)
WALK_OBJECT_X(SPRITE_MOKUBA, 52)
DELAY(16)
TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Big brother!\n\n"
    "Most of the Neo Ghouls have\n"
    "left the Town of Domino.\n\n"
)
TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Good.\n\n"
)
TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I protected KaibaCorp, just\n"
    "like you told me.\n\n"
    "So you don't have to worry\n"
    "about a thing.\n\n"
)
TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Good work, Mokuba.\n\n"
)
TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Heheh, thanks. You know I'll\n"
    "do anything for you.\n\n"
    "So, anything new with your\n"
    "Egyptian God Card?\n\n"
)
TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Somehow, it's back to\n"
    "normal.\n\n"
)
HIDE_PORTRAIT()
DELAY(32)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_RIGHT, 0, 0)
DELAY(32)
TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I don't know what they did,\n"
    "but...\n\n"
)
PLAY_MUSIC(MUSIC_404)
WALK_OBJECT_X(SPRITE_DOX_FLIPPING, 48)
TALK(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SURPRISED, PORTRAIT_LEFT,
    "Urk! S-Seto...\n\n"
)
HIDE_PORTRAIT()
DELAY(8)
SET_OBJECT_POSITION(SPRITE_MOKUBA, 128, 96, 0)
PLAY_MUSIC(MUSIC_314)
LOAD_SPRITE(4, SPRITE_DOX_WITH_MOKUBA)
DELAY(8)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_LEFT, 0, 0)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, SPRITE_SETO)
DELAY(8)
TALK(PORTRAIT_SETO, 6, PORTRAIT_RIGHT,
    "How dare you... What's the\n"
    "meaning of this?\n\n"
)
TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT,
    "Seto Kaiba! I have a message\n"
    "from Master Chevalsky!\n\n"
    "Come to my castle.\n\n"
    "If you want to save your\n"
    "dear brother.\n\n"
    "You have no choice but to\n"
    "come to my castle!\n\n"
)
TALK(PORTRAIT_SETO, 5, PORTRAIT_RIGHT,
    "You worm!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_LEFT, 8, 0)
PLAY_MUSIC(MUSIC_277)
SLIDE_OBJECT(SPRITE_DOX_WITH_MOKUBA, 1, 8)
DELAY(16)
SET_OBJECT_POSITION(SPRITE_PARA, 95, 16, 0)
DELAY(16)
WALK_OBJECT_Y(SPRITE_PARA, 24)
WALK_OBJECT_X(SPRITE_PARA, 80)
DELAY(16)
TALK(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT,
    "Younger brother, you have\n"
    "fulfilled your mission!\n\n"
    "Master Chevalsky will\n"
    "promote you to a higher\n\n"
    "position!\n\n"
)
TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT,
    "Elder brother, you also have\n"
    "done your job with most\n\n"
    "excellence!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_RIGHT, 0, 0)
DELAY(32)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_LEFT, 0, 0)
DELAY(16)
TALK(PORTRAIT_SETO, 2, PORTRAIT_RIGHT,
    "You punks! How dare you mock\n"
    "me!\n\n"
)
TALK(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT,
    "Fufufufufufu...\n\n"
)
TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT,
    "Fufufufufufu...\n\n"
)
TALK(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Master Chevalsky demands\n"
    "your presence, Kaiba!\n\n"
)
TALK(PORTRAIT_DOX, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Come to Master Chevalsky's\n"
    "castle!\n\n"
)
TALK(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT,
    "The castle that you...\n\n"
)
TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT,
    "...Know so well! Fufufu...\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_315)
SLIDE_OBJECT(SPRITE_PARA, 1, 96)
PLAY_MUSIC(MUSIC_315)
SLIDE_OBJECT(SPRITE_DOX_WITH_MOKUBA, 1, 64)
DELAY(16)
TALK(PORTRAIT_SETO, 2, PORTRAIT_RIGHT,
    "Mokuba!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_LEFT, 4, 0)
DELAY(16)
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
SET_OBJECT_POSITION(SPRITE_ISHIZU, 95, 16, 0)
DELAY(16)
WALK_OBJECT_Y(SPRITE_ISHIZU, 24)
MOVE_OBJECT(SPRITE_ISHIZU, DIRECTION_LEFT, 0, 0)
DELAY(16)
WALK_OBJECT_X(0, 77)
DELAY(16)
TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "{PLAYER} is right, Kaiba.\n\n"
    "Now is the time for\n"
    "teamwork.\n\n"
    "The Dark Being must be\n"
    "sealed again...\n\n"
)
HIDE_PORTRAIT()
DELAY(8)
MOVE_OBJECT(SPRITE_SETO, DIRECTION_RIGHT, 0, 0)
DELAY(8)
TALK(PORTRAIT_SETO, 2, PORTRAIT_LEFT,
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
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(SPRITE_SETO, 0)
SET_OBJECT_POSITION(SPRITE_SETO, 128, 96, 0)
DELAY(16)
TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "We're left with no choice.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
DELAY(16)
TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "We must also go to Sol\n"
    "Chevalsky's... I mean...\n\n"
    "We must also go to Pegasus's\n"
    "castle.\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "But who knows where the\n"
    "castle is?\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_272)
REACTION(REACTION_ELLIPSIS, OBJECT_0 | SPRITE_ISHIZU | OBJECT_13 | OBJECT_14)
DELAY(16)
PLAY_MUSIC(MUSIC_402)
WALK_OBJECT_X(SPRITE_MILLENNIUM_GUARDIAN, 48)
DELAY(8)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, SPRITE_ISHIZU)
DELAY(8)
MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
DELAY(16)
TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
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
TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Paradox awaits you in China.\n\n"
    "He will show you the way.\n\n"
)
HIDE_PORTRAIT()
DELAY(32)
MOVE_OBJECT(SPRITE_MILLENNIUM_GUARDIAN, DIRECTION_LEFT, 64, 0)
DELAY(32)
MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
DELAY(16)
TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
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
WALK_OBJECT_X(SPRITE_ISHIZU, 0)
SET_OBJECT_POSITION(SPRITE_ISHIZU, 128, 96, 0)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I'm worried about Mokuba and\n"
    "Kaiba...\n\n"
    "We'd better find Pegasus's\n"
    "castle quickly.\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Yugi's right.\n\n"
    "If this Parachute guy can\n"
    "help us...\n\n"
    "We'd betta find him quick.\n\n"
)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "That's Paradox, Joey.\n"
    "Not Parachute.\n\n"
    "{PLAYER}, let's go! We're\n"
    "off to China!\n\n"
)
HIDE_PORTRAIT()
MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
SET_FLAG(EVENT_FLAG_SAW_MOKUBA_GET_KIDNAPPED)

EVENT_SCRIPT_REPLACEMENT(0x08E8CBF4, map_22_state_08_08E8CBF4, 0x08E8CC00, 0x08F04040)
HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_SETO, 2, PORTRAIT_LEFT,
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
