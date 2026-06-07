#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_33_state_05: map 33 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08EBEBE0, map_33_state_05_08EBEBE0, 0x08EBEBEC, 0x08EBEBF8)
  LOAD_SPRITE(1, SPRITE_PARADOX)
  PLAY_MUSIC(MUSIC_410)
  DELAY(16)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(1, 60, 68, 0, 1, 0)
  DELAY(64)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What took you so long?\n\n"
      "However, you've passed the\n"
      "challenges so far.\n\n"
      "Along the way, you have\n"
      "been given cards.\n\n"
      "Do you understand what they\n"
      "represent?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEBEC, map_33_state_05_08EBEBEC, 0x08EBEC04, 0x08F04040)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ah! Good, good!\n"
      "Good for you!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC04, map_33_state_05_08EBEC04, 0x08EBEC10, 0x08EBEC1C)
  TEXT
  (
      "Fine.\n"
      "Then answer my questions.\n\n"
      "Which card should come\n"
      "first?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Celtic Guardian\n"
      "Kuriboh{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC10, map_33_state_05_08EBEC10, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That isn't right, is it?\n\n"
  )
  CLEAR_FLAG(152)
  CLEAR_FLAG(154)
  CLEAR_FLAG(155)
  CLEAR_FLAG(156)
  CLEAR_FLAG(157)
  WARP(LOCATION_CHINA_GREAT_WALL_ENTRANCE, 7, 1, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC1C, map_33_state_05_08EBEC1C, 0x08EBEC28, 0x08EBEC40)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ah, good!\n"
      "You seem to understand.\n\n"
      "Then which card should come\n"
      "fifth?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Curse of Dragon\n"
      "Giant Soldier of Stone{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC28, map_33_state_05_08EBEC28, 0x08EBEC4C, 0x08EBEC34)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Well done! You seem to\n"
      "really understand.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh, I get it. The cards we\n"
      "received were in sequence.\n\n"
      "They were in the order of\n"
      "their levels.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Kuriboh's level one, so it\n"
    "came first.\n\n"
    "Curse of Dragon came last\n"
    "because it's level five.\n\n"
    "That's what we had to\n"
    "figure out, right,\n\n"
    "{PLAYER}?\n\n"
)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You still haven't passed\n"
    "all my tests.\n\n"
    "You claim to be a duelist.\n"
    "Therefore, we shall duel.\n\n"
)
  DUEL(DUELIST_PARADOX_083)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC4C, map_33_state_05_08EBEC4C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_410)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hmm... I haven't dueled for\n"
      "so long my instincts are\n\n"
      "rusty.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Making excuses?\n"
      "Some sage.\n\n"
  )
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "...Oh well.\n\n"
      "I will grant your wish.\n\n"
      "Pegasus is on his island.\n\n"
      "The island is cloaked by a\n"
      "magical barrier.\n\n"
      "I shall extinguish that\n"
      "barrier for you.\n\n"
      "Hah!\n\n"
  )
  PLAY_MUSIC(MUSIC_331)
  SPECIAL(0)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "That is all I can do\n"
    "to help you.\n\n"
    "I'm afraid the rest is\n"
    "entirely up to you.\n\n"
    "The hope of the world rests\n"
    "with you...\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_1, OBJECT_EFFECT_TELEPORT)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  DELAY(32)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO,
    "Wh-what?\n"
    "He disappeared?\n\n"
)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "What a strange old man.\n\n"
)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO,
    "Strange? Freaktacular, I'd\n"
    "say. Let's get outta here.\n\n"
)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Yes, let's go to Pegasus's\n"
    "island, {PLAYER}!\n\n"
)
  SET_FLAG(EVENT_FLAG_DEFEATED_PARADOX)
  SET_FLAG(EVENT_FLAG_UNLOCKED_PEGASUS_ISLAND)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC34, map_33_state_05_08EBEC34, 0x08F0404C, 0x08F04040)
  CLEAR_FLAG(152)
  CLEAR_FLAG(154)
  CLEAR_FLAG(155)
  CLEAR_FLAG(156)
  CLEAR_FLAG(157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEC40, map_33_state_05_08EBEC40, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What's that?\n"
      "You don't know?\n\n"
      "That's the wrong card.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  OBJECT_EFFECT(OBJECT_0 | OBJECT_13 | OBJECT_14, OBJECT_EFFECT_TELEPORT)
  CLEAR_FLAG(152)
  CLEAR_FLAG(154)
  CLEAR_FLAG(155)
  CLEAR_FLAG(156)
  CLEAR_FLAG(157)
  FADE_SCREEN(4)
  WARP(LOCATION_CHINA_GREAT_WALL_ENTRANCE, 7, 1, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EBEBF8, map_33_state_05_08EBEBF8, 0x08EBEC04, 0x08F04040)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't disappoint me.\n\n"
      "At least pretend that you\n"
      "know!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
