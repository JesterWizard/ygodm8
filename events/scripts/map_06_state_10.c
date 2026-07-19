#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_06_state_10: map 6 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CD80, map_06_state_10_08E5CD80, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_LUCKY)
  LOAD_SPRITE(2, SPRITE_DUKE)
  LOAD_SPRITE(3, SPRITE_SERENITY)
  LOAD_SPRITE(4, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(5, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(6, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(7, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(8, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(9, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(10, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(11, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(12, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(13, SPRITE_YUGI)
  LOAD_SPRITE(14, SPRITE_JOEY)
  TALK(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, PORTRAIT_POSITION_AUTO, "...And that's what happened.")
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  TALK(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_POSITION_AUTO,
      "Big brother... I saw this look on Tristan's face...",
      "It was as if he was saying that he didn't want anyone",
      "to follow him.",
      "I wonder if he's going to be okay..."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
      "Don't worry about a thing, Serenity.",
      "Tristan's our friend. There's no way we'll",
      "abandon him!",
      "We'll look for him, but I want you to stay here,",
      "Serenity. Just in case he comes back."
  )
  SET_FLAG(EVENT_FLAG_SEARCHING_FOR_ROBOT_TRISTAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD98, map_06_state_10_08E5CD98, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I bet Tristan ran off on purpose!",
      "That's the only way Serenity would pay attention to him",
      "instead of me!",
      "...N-no, he wouldn't do that. He's not that type of",
      "guy."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD8C, map_06_state_10_08E5CD8C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, PORTRAIT_POSITION_AUTO, "Where could Tristan have gone?")
  FALLTHROUGH()
END_EVENT_SCRIPT()
