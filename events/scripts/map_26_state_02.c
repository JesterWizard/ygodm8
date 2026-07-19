#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_02: map 26 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3B78, map_26_state_02_08EA3B78, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_MAI)
  LOAD_SPRITE(2, SPRITE_TRISTAN)
  LOAD_SPRITE(3, SPRITE_DUKE)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  WALK_OBJECT_Y(2, 70)
  WALK_OBJECT_Y(2, 40)
  WALK_OBJECT_Y(3, 40)
  WALK_OBJECT_Y(3, 70)
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY,
      "C'mon, boys! Work harder, you two!",
      "At this rate, you'll never become real duelists.",
      "It'll take you a hundred years to reach my skill",
      "level!"
  )
  TALK(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_TEETH_GRITTED, "Wh-why are we working for Mai?")
  TALK(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, "What'd we do to deserve this?")
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  TALK(PORTRAIT_MAI,
      "Oh, hi Joey!",
      "Do you want me to train you too?"
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, "Why would I need training?")
  TALK(PORTRAIT_MAI,
      "Ahahaha, I'm only joking.",
      "Minion One and Minion Two, stop slacking off!"
  )
  TALK(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_TEETH_GRITTED, "M-Minion One?")
  TALK(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, "Two?!")
  TALK(PORTRAIT_NONE, "This sucks...")
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_SWEATDROP,
      "Wipe those frowns off your faces.",
      "If you really want to improve your dueling",
      "skills, you should hit the road on a training quest."
  )
  TALK(PORTRAIT_DUKE, "A training quest?")
  TALK(PORTRAIT_TRISTAN, EXPRESSION_TRISTAN_HAPPY,
      "I'm going! I am soooo going!",
      "Anything beats getting worked like a mule.",
      "I would rather be anywhere else but here!",
      "Duke, let's go!"
  )
  WALK_OBJECT_Y(2, 70)
  WALK_OBJECT_X(2, 52)
  WALK_OBJECT_Y(2, 96)
  TALK(PORTRAIT_DUKE, "S-sure. Wait for me, Tristan.")
  WALK_OBJECT_X(3, 60)
  WALK_OBJECT_Y(3, 96)
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_SWEATDROP,
      "Those two... I was only kidding. I mean, what's a",
      "training quest anyway?",
      "Sigh... Now that my minions are gone, I have to do my",
      "own work."
  )
  SET_FLAG(EVENT_FLAG_SAW_TRISTAN_AND_DUKE_LEAVING_ON_A_TRAINING_QUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3B84, map_26_state_02_08EA3B84, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI,
      "Tristan and Duke left on a training quest.",
      "But what are they training for?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
