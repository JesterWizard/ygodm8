#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_12: map 0 state 12 */

EVENT_SCRIPT_REPLACEMENT(0x08E34E80, map_00_state_12_08E34E80, 0x08E34E8C, 0x08E34E98)
  LOAD_SPRITE(1, SPRITE_ESPA)
  LOAD_SPRITE(2, SPRITE_ROBA_BROTHER_1)
  LOAD_SPRITE(3, SPRITE_ROBA_BROTHER_2)
  LOAD_SPRITE(4, SPRITE_ROBA_BROTHER_3)
  PLAY_MUSIC(MUSIC_DOMINO_CITY_LIBERATED)
  MOVE_OBJECT(2, DIRECTION_LEFT, 4, 0)
  DELAY(16)
  TEXT
  (
      "Big brother, we can go too,\n"
      "right?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 4, 0)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "No... I have a bad feeling\n"
      "about this.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_LEFT, 4, 0)
  TEXT
  (
      "But the Neo Ghouls...\n"
      "They're almost gone.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_RIGHT, 4, 0)
  MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Let's wait until {PLAYER}\n"
      "and his friends come back.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_LEFT, 4, 0)
  DELAY(16)
  TEXT
  (
      "You never let us do\n"
      "anything!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 4, 0)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'm only trying to keep you\n"
      "safe!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_LEFT, 4, 0)
  DELAY(16)
  TEXT
  (
      "I'm old enough to take care\n"
      "of myself! I mean, I need\n\n"
      "both my hands to count my\n"
      "age!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 4, 0)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TEXT
  (
      "C'mon, don't fight.\n\n"
  )
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "If that's what you want to\n"
      "do, fine.\n\n"
  )
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But you're going to have to\n"
      "look after everyone.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 4, 0)
  DELAY(16)
  TEXT
  (
      "Okay, big brother, I will.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 4, 0)
  DELAY(16)
  TEXT
  (
      "Let's go, you guys.\n\n"
      "Yay!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(4, 97)
  WALK_OBJECT_Y(4, 37)
  WALK_OBJECT_X(4, 144)
  WALK_OBJECT_X(3, 97)
  WALK_OBJECT_Y(3, 37)
  WALK_OBJECT_X(3, 144)
  WALK_OBJECT_X(2, 97)
  WALK_OBJECT_Y(2, 37)
  WALK_OBJECT_X(2, 144)
  DELAY(16)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_ESPA_ROBA_SWEATDROP, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My brothers can be so\n"
      "frustrating...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(0, 31)
  WALK_OBJECT_X(0, 38)
  WALK_OBJECT_Y(13, 37)
  WALK_OBJECT_X(13, 28)
  WALK_OBJECT_Y(14, 25)
  WALK_OBJECT_X(14, 28)
  DELAY(32)
  WALK_OBJECT_Y(1, 31)
  WALK_OBJECT_X(1, 48)
  DELAY(16)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh, you're back.\n\n"
      "Most of the Neo Ghouls have\n"
      "been routed from the Town\n\n"
      "of Domino.\n\n"
      "But there are some still\n"
      "lurking around.\n\n"
      "Can you find and defeat\n"
      "them?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E8C, map_00_state_12_08E34E8C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Okay, thanks!\n\n"
      "They should still be in\n"
      "Clocktower Square.\n\n"
  )
  SET_FLAG(EVENT_FLAG_SEARCHING_FOR_SEEKER2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34E98, map_00_state_12_08E34E98, 0x08E34E8C, 0x08E34E98)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh, come on, don't be that\n"
      "way. We need your help.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34EA4, map_00_state_12_08E34EA4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ESPA_ROBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Most of the Neo Ghouls have\n"
      "been routed from the Town\n\n"
      "of Domino.\n\n"
      "But there are still some\n"
      "lurking around.\n\n"
      "They should still be in\n"
      "Clocktower Square.\n\n"
      "Please find and defeat them.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
