#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_38_state_01: map 38 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08ED1640, map_38_state_01_08ED1640, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_WEEVIL)
  PLAY_MUSIC(MUSIC_247)
  DELAY(32)
  WALK_OBJECT_X(1, 40)
  DELAY(32)
  WALK_OBJECT_Y(1, 48)
  DELAY(32)
  WALK_OBJECT_X(1, 56)
  DELAY(32)
  WALK_OBJECT_Y(1, 40)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hyohyohyohyohyo!\n\n"
      "This island is a treasure\n"
      "trove of rare insects!\n\n"
  )
  SET_FLAG(EVENT_FLAG_SAW_WEEVIL_TALK_TO_HIMSELF)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED164C, map_38_state_01_08ED164C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hyo? You're trying to steal\n"
      "my beautiful bugs, aren't\n\n"
      "you?\n\n"
      "I'm not sharing any of them\n"
      "with you!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED1658, map_38_state_01_08ED1658, 0x08ED1664, 0x08ED167C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_WEEVIL)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED1664, map_38_state_01_08ED1664, 0x08ED1670, 0x08F0404C)
  PORTRAIT(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hyohyohyohyohyo! You measly\n"
      "maggot!\n\n"
      "You must have the brains of\n"
      "a louse to challenge a\n\n"
      "former champion!\n\n"
      "Prepare for a bug bashing\n"
      "with my Super Insect Deck!\n\n"
  )
  DUEL(49)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED1670, map_38_state_01_08ED1670, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_247)
  PORTRAIT(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't get cocky! That was a\n"
      "fluke!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_WEEVIL)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED167C, map_38_state_01_08ED167C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I caught most of the rare\n"
      "insects in this area.\n\n"
      "I think I'll go to China\n"
      "next.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
