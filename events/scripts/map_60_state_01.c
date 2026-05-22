#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_60_state_01: map 60 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08F039CC, map_60_state_01_08F039CC, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_MARIK)
  LOAD_SPRITE(2, SPRITE_ODION)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Father, Mother...\n\n"
      "And all those people I\n"
      "harmed...\n\n"
      "I hope that the sun shines\n"
      "upon your spirits.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hello. It has been a long\n"
      "time.\n\n"
  )
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Master Marik, forgive us for\n"
      "disturbing your rituals.\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "It does not matter. They are\n"
      "always welcome.\n\n"
      "Even my departed Father\n"
      "would have welcomed them.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Marik, we need your help.\n\n"
      "We have to awaken {PLAYER}'s\n"
      "The Winged Dragon of Ra.\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "...Tell me more.\n\n"
  )
  HIDE_PORTRAIT()
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "So... That explains why my\n"
      "sister left in a hurry.\n\n"
      "It makes sense now...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I understand what you seek.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Great! Then how about\n"
      "getting on it right away?\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I will not awaken Ra so\n"
      "easily.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What?!\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I believe you know why.\n\n"
      "Ra is the most powerful of\n"
      "the Egyptian God Cards.\n\n"
      "You felt its mystical\n"
      "strength firsthand.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(MUSIC_332)
  FADE_MUSIC(4)
  FADE_SCREEN(4)
  SET_FLAG(EVENT_FLAG_FLASHBACK)
  WARP(23, 10, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A38, map_60_state_01_08F03A38, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "There must be a secret in\n"
      "the hieroglyphics.\n\n"
      "A secret method for\n"
      "awakening the Phoenix Mode.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A44, map_60_state_01_08F03A44, 0x08F03A50, 0x08F03A5C)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Fine.\n\n"
      "I have been freed of my\n"
      "obligations as a\n\n"
      "gravekeeper.\n\n"
      "When I duel, I duel for\n"
      "myself and will use all my\n\n"
      "arcane strategies!\n\n"
  )
  DUEL(158)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A50, map_60_state_01_08F03A50, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You won...\n\n"
      "You may be ready to face the\n"
      "Dark Being...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A5C, map_60_state_01_08F03A5C, 0x08F0404C, 0x08F04040)
  SET_FLAG(EVENT_FLAG_EXITED_MARIKS_HOME)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A08, map_60_state_01_08F03A08, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Since you arrived, Master\n"
      "Marik has been chanting\n\n"
      "devoutly.\n\n"
      "He is chanting to atone for\n"
      "his past sins.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A14, map_60_state_01_08F03A14, 0x08F03A20, 0x08F03A2C)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You dare enter my haven of\n"
      "traps?\n\n"
      "Fine! We shall duel!\n\n"
  )
  DUEL(157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A20, map_60_state_01_08F03A20, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Gah! Your fighting spirit is\n"
      "most impressive!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A2C, map_60_state_01_08F03A2C, 0x08F0404C, 0x08F04040)
  SET_FLAG(EVENT_FLAG_EXITED_MARIKS_HOME)
  FALLTHROUGH()
END_EVENT_SCRIPT()
