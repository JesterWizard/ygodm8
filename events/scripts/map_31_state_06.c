#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_06: map 31 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08EB43C0, map_31_state_06_08EB43C0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PARADOX)
  PLAY_MUSIC(MUSIC_410)
  DELAY(16)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(1, 72, 44, 0, 1, 0)
  DELAY(64)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "The Winged Dragon of Ra has awakened, I see.")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "We did exactly what you said, pops.",
      "Now come on, where's Pegasus hiding?"
  )
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Be patient.",
      "I've been living in the mountains for generations,",
      "and I've become bored.",
      "I feel like playing a game.",
      "It's very simple.",
      "You have to first catch me, then duel me.",
      "If you win, I will tell you whatever you wish.",
      "But I won't be caught so easily.",
      "Fwohoho."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 128)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_242)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "What's up with dat guy...")
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Who knows...",
      "Let's go catch him!"
  )
  SET_FLAG(EVENT_FLAG_SAW_PARADOX_FLEE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB43B4, map_31_state_06_08EB43B4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You must restore Ra's power.",
      "There must be someone who knows how to wake it..."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
