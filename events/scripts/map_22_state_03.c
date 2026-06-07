#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_03: map 22 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E8CB34, map_22_state_03_08E8CB34, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_EGYPT_EXHIBITION_VISITOR)
  LOAD_SPRITE(2, SPRITE_SETO)
  LOAD_SPRITE(3, SPRITE_MOKUBA)
  PLAY_MUSIC(MUSIC_405)
  DELAY(16)
  WALK_OBJECT_Y(0, 26)
  WALK_OBJECT_X(0, 80)
  WALK_OBJECT_Y(13, 20)
  WALK_OBJECT_X(13, 90)
  WALK_OBJECT_Y(14, 32)
  WALK_OBJECT_X(14, 90)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 8, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Humph. So the merry band of\n"
      "losers finally have a clue\n\n"
      "about what's really going\n"
      "on.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_RIGHT, 8, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ishizu visited my big\n"
      "brother.\n\n"
      "She wanted him to get the\n"
      "Egyptian God Cards back.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Mokuba, keep quiet.\n\n"
      "The title as champion And\n"
      "the strongest cards...\n\n"
      "Only the most powerful\n"
      "duelist is worthy of these\n\n"
      "two things.\n\n"
      "And that duelist is me!\n\n"
      "I will recover the Egyptian\n"
      "God Cards quick and easy.\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I bet you guys are happy\n"
      "that my big bro's gonna\n\n"
      "help you out, huh?\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Mokuba!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(3, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "W-what is it, Seto?\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I have no intention of\n"
      "teaming up with these\n\n"
      "clowns!\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Big brother...\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Listen up, you fools!\n\n"
      "A real duelist doesn't need\n"
      "help from a bunch of\n\n"
      "cheerleaders!\n\n"
      "All you should count on is\n"
      "your own strength!\n\n"
      "You guys are so weak that\n"
      "none of you can survive\n\n"
      "alone...\n\n"
      "And you expect me to team up\n"
      "with you losers? Don't make\n\n"
      "me laugh!\n\n"
      "Let's go, Mokuba!\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wahahahahaha!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(2, DIRECTION_LEFT, 72, 0)
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
  DELAY(24)
  MOVE_OBJECT(3, DIRECTION_RIGHT, 0, 0)
  DELAY(24)
  MOVE_OBJECT(3, DIRECTION_LEFT, 68, 0)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_SAW_KAIBA_AT_EGYPT_EXHIBITION)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB1C, map_22_state_03_08E8CB1C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "This is the Egypt\n"
      "Exhibition.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB28, map_22_state_03_08E8CB28, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No way, I'm not a duelist.\n\n"
      "I came here for the\n"
      "exhibition.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
