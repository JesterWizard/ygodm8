#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_37_state_01: map 37 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD7D8, map_37_state_01_08ECD7D8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_MAKO)
  PLAY_MUSIC(MUSIC_708)
  PLAY_MUSIC(MUSIC_383)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 8, 0)
  DELAY(16)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I can hear the sea raging...",
      "It's shouting as if nature is out of balance."
  )
  SET_FLAG(EVENT_FLAG_SAW_MAKO_TALK_TO_HIMSELF)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD7E4, map_37_state_01_08ECD7E4, 0x08ECD7FC, 0x08ECD820)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_MAKO)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD7FC, map_37_state_01_08ECD7FC, 0x08ECD808, 0x08ECD814)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Can you not hear it? Can you not hear the pain of the",
      "ocean?",
      "I was raised on the high seas, so I can understand",
      "when all is not right.",
      "The waters are crying, but about what..."
  )
  TALK(PORTRAIT_NONE, "{CARD_1}Actually...\nYou're imagining things{CARD_2}")
  SET_FLAG(EVENT_FLAG_TALKED_TO_MAKO)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD808, map_37_state_01_08ECD808, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "What's going on?")
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(8)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Reshef the Dark Being? That's hard to believe.",
      "But the tides have been far from normal.",
      "If anything has to do with this mystery...",
      "Go deeper into the island. You may find something."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD814, map_37_state_01_08ECD814, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Oh, I'm imagining things, am I?",
      "You cannot deceive me.",
      "I can tell you're hiding something...important."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You do not have to reveal your secrets if you are not",
      "so inclined.",
      "But I will let you know that the tides have been far",
      "from normal.",
      "If anything has to do with this mystery...",
      "Go deeper into the island. You may find something."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD820, map_37_state_01_08ECD820, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "There's something wrong with the sea.",
      "I hope it's not a sign of some impending catastrophe."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD7F0, map_37_state_01_08ECD7F0, 0x08ECD7FC, 0x08ECD82C)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_MAKO)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD82C, map_37_state_01_08ECD82C, 0x08ECD838, 0x08F0404C)
  TALK(PORTRAIT_MAKO, EXPRESSION_MAKO_HAPPY, PORTRAIT_POSITION_AUTO, "Fine! Mako Tsunami does not flee from any challenge!")
  DUEL(DUELIST_MAKO_048)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD838, map_37_state_01_08ECD838, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_246)
  TALK(PORTRAIT_MAKO, EXPRESSION_MAKO_HAPPY, PORTRAIT_POSITION_AUTO,
      "Excellent duel!",
      "But next time, you won't win so easily!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
