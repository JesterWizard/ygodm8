#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_03: map 22 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E8CB34, map_22_state_03_08E8CB34, EVENT_NOP, EVENT_NOP)
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
  TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Humph. So the merry band of losers finally have a clue",
      "about what's really going on."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_RIGHT, 8, 0)
  DELAY(16)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Ishizu visited my big brother.",
      "She wanted him to get the Egyptian God Cards back."
  )
  TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Mokuba, keep quiet.",
      "The title as champion And the strongest cards...",
      "Only the most powerful duelist is worthy of these",
      "two things.",
      "And that duelist is me!",
      "I will recover the Egyptian God Cards quick and easy."
  )
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I bet you guys are happy that my big bro's gonna",
      "help you out, huh?"
  )
  TALK(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO, "Mokuba!")
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(3, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SURPRISED, PORTRAIT_POSITION_AUTO, "W-what is it, Seto?")
  TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I have no intention of teaming up with these",
      "clowns!"
  )
  TALK(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SAD, PORTRAIT_POSITION_AUTO, "Big brother...")
  TALK(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO,
      "Listen up, you fools!",
      "A real duelist doesn't need help from a bunch of",
      "cheerleaders!",
      "All you should count on is your own strength!",
      "You guys are so weak that none of you can survive",
      "alone...",
      "And you expect me to team up with you losers? Don't make",
      "me laugh!",
      "Let's go, Mokuba!"
  )
  TALK(PORTRAIT_SETO, 1, PORTRAIT_POSITION_AUTO, "Wahahahahaha!")
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

EVENT_SCRIPT_REPLACEMENT(0x08E8CB1C, map_22_state_03_08E8CB1C, EVENT_NOP, EVENT_NOP)
  TEXT("This is the Egypt Exhibition.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CB28, map_22_state_03_08E8CB28, EVENT_NOP, EVENT_NOP)
  TEXT(
      "No way, I'm not a duelist.",
      "I came here for the exhibition."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
