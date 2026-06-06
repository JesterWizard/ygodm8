#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_07_state_03: map 7 state 3 */

LOAD_SPRITE(1, SPRITE_TEA)
LOAD_SPRITE(2, SPRITE_GRANDPA_MUTO)
LOAD_SPRITE(3, SPRITE_YUGI)
LOAD_SPRITE(4, SPRITE_JOEY)
LOAD_SPRITE(5, SPRITE_INVISIBLE)
LOAD_SPRITE(6, SPRITE_INVISIBLE)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Grandpa! We're in trouble!\n\n"
    "Tristan turned into a monkey\n"
    "robot and ran away!\n\n"
)
PORTRAIT(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Monkey robot?\n\n"
    "Like the ones made by\n"
    "KaibaCorp?\n\n"
)
PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
TEXT
(
    "I knew it was that dirty rat\n"
    "Kaiba's fault!\n\n"
    "Only a psycho like him would\n"
    "make a monkey out of my\n\n"
    "friend!\n\n"
)
PORTRAIT(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "The robot looked harmless to\n"
    "me...\n\n"
)
SET_FLAG(EVENT_FLAG_GRANDPA_MUTO_SAID_KAIBA_CORP_PRODUCES_MONKEY_ROBOTS)

EVENT_SCRIPT_REPLACEMENT(0x08E5F8F4, map_07_state_03_08E5F8F4, 0x08E5F900, 0x08F04040)
PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Why would Kaiba turn Tristan\n"
      "into a robot...?\n\n"
      "Well, we have more important\n"
      "things to worry about.\n\n"
      "If Tristan is a monkey,\n"
      "where would he go?\n\n"
      "...Of course! He'd look for\n"
      "bananas.\n\n"
      "Look for him where you can\n"
      "find bananas.\n\n"
  )
  CHECK_FLAG(EVENT_FLAG_TEA_SAID_TO_LOOK_FOR_BANANAS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F900, map_07_state_03_08E5F900, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Bananas? That would be...\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Galapagos Islands?\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We'll search where monkeys\n"
      "hang out!\n\n"
  )
  SET_FLAG(EVENT_FLAG_TEA_SAID_TO_LOOK_FOR_BANANAS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F90C, map_07_state_03_08E5F90C, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't you have to find\n"
      "Tristan first?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
