#include "event_macros.h"
#include "overworld.h"

/* map_07_state_03: map 7 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E5F8E8, map_07_state_03_08E5F8E8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT("Grandpa! We're in trouble!\n\nTristan turned into a monkey\nrobot and ran away!\n\n")
  PORTRAIT(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Monkey robot?\n\nLike the ones made by\nKaibaCorp?\n\n")
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT("I knew it was that dirty rat\nKaiba's fault!\n\nOnly a psycho like him would\nmake a monkey out of my\n\nfriend!\n\n")
  PORTRAIT(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The robot looked harmless to\nme...\n\n")
  SET_FLAG(EVENT_FLAG_GRANDPA_MUTO_SAID_KAIBA_CORP_PRODUCES_MONKEY_ROBOTS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8F4, map_07_state_03_08E5F8F4, 0x08E5F900, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Why would Kaiba turn Tristan\ninto a robot...?\n\nWell, we have more important\nthings to worry about.\n\nIf Tristan is a monkey,\nwhere would he go?\n\n...Of course! He'd look for\nbananas.\n\nLook for him where you can\nfind bananas.\n\n")
  CHECK_FLAG(EVENT_FLAG_TEA_SAID_TO_LOOK_FOR_BANANAS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F900, map_07_state_03_08E5F900, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Bananas? That would be...\n\n")
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("The Galapagos Islands?\n\n")
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("We'll search where monkeys\nhang out!\n\n")
  SET_FLAG(EVENT_FLAG_TEA_SAID_TO_LOOK_FOR_BANANAS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F90C, map_07_state_03_08E5F90C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Don't you have to find\nTristan first?\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
