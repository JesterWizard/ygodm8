#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_03: map 31 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08EB42AC, map_31_state_03_08EB42AC, 0x08EB42B8, 0x08EB42C4)
  LOAD_SPRITE(1, SPRITE_PARA)
  LOAD_SPRITE(2, SPRITE_DOX_FLIPPING)
  LOAD_SPRITE(3, SPRITE_YUGI)
  LOAD_SPRITE(4, SPRITE_JOEY)
  LOAD_SPRITE(5, SPRITE_SETO)
  LOAD_SPRITE(6, SPRITE_MOKUBA)
  SET_FLAG(EVENT_FLAG_JOEY_FOUND_PARA_AND_DOX_SUSPICIOUS)
  WALK_OBJECT_X(14, 104)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP,
      "There's somethin' fishy about those guys. Really",
      "fishy.",
      "{PLAYER}, you think so too, right?"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_NONE, "{CARD_1}Yup\nNope{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42B8, map_31_state_03_08EB42B8, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_JOEY, "Let's check 'em out again.")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42C4, map_31_state_03_08EB42C4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP,
      "I'm tellin' ya, there's somethin' weird about those",
      "guys!",
      "Every bone in my body tells me dat, and my instinct is",
      "never wrong!",
      "Let's check 'em out again."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
