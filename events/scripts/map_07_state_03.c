#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_07_state_03: map 7 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E5F8E8, map_07_state_03_08E5F8E8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_TEA)
  LOAD_SPRITE(2, SPRITE_GRANDPA_MUTO)
  LOAD_SPRITE(3, SPRITE_YUGI)
  LOAD_SPRITE(4, SPRITE_JOEY)
  LOAD_SPRITE(5, SPRITE_INVISIBLE)
  LOAD_SPRITE(6, SPRITE_INVISIBLE)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO,
      "Grandpa! We're in trouble!",
      "Tristan turned into a monkey robot and ran away!"
  )
  TALK(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Monkey robot?",
      "Like the ones made by KaibaCorp?"
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
      "I knew it was that dirty rat Kaiba's fault!",
      "Only a psycho like him would make a monkey out of my",
      "friend!"
  )
  TALK(PORTRAIT_SOLOMON, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "The robot looked harmless to me...")
  SET_FLAG(EVENT_FLAG_GRANDPA_MUTO_SAID_KAIBA_CORP_PRODUCES_MONKEY_ROBOTS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8F4, map_07_state_03_08E5F8F4, 0x08E5F900, EVENT_NOP)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Why would Kaiba turn Tristan into a robot...?",
      "Well, we have more important things to worry about.",
      "If Tristan is a monkey, where would he go?",
      "...Of course! He'd look for bananas.",
      "Look for him where you can find bananas."
  )
  CHECK_FLAG(EVENT_FLAG_TEA_SAID_TO_LOOK_FOR_BANANAS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F900, map_07_state_03_08E5F900, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Bananas? That would be...")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "The Galapagos Islands?")
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "We'll search where monkeys hang out!")
  SET_FLAG(EVENT_FLAG_TEA_SAID_TO_LOOK_FOR_BANANAS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F90C, map_07_state_03_08E5F90C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Don't you have to find Tristan first?")
  FALLTHROUGH()
END_EVENT_SCRIPT()
