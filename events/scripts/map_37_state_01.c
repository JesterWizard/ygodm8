#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_37_state_01: map 37 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08ECD7D8, map_37_state_01_08ECD7D8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_MAKO)
  PLAY_MUSIC(MUSIC_708)
  PLAY_MUSIC(MUSIC_383)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 8, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I can hear the sea raging...\n\n"
      "It's shouting as if nature\n"
      "is out of balance.\n\n"
  )
  SET_FLAG(EVENT_FLAG_SAW_MAKO_TALK_TO_HIMSELF)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD7E4, map_37_state_01_08ECD7E4, 0x08ECD7FC, 0x08ECD820)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_MAKO)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD7FC, map_37_state_01_08ECD7FC, 0x08ECD808, 0x08ECD814)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Can you not hear it? Can you\n"
      "not hear the pain of the\n\n"
      "ocean?\n\n"
      "I was raised on the high\n"
      "seas, so I can understand\n\n"
      "when all is not right.\n\n"
      "The waters are crying, but\n"
      "about what...\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Actually...\n"
      "You're imagining things{CARD_2}\n\n"
  )
  SET_FLAG(EVENT_FLAG_TALKED_TO_MAKO)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD808, map_37_state_01_08ECD808, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What's going on?\n\n"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(8)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Reshef the Dark Being?\n"
      "That's hard to believe.\n\n"
      "But the tides have been far\n"
      "from normal.\n\n"
      "If anything has to do with\n"
      "this mystery...\n\n"
      "Go deeper into the island.\n"
      "You may find something.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD814, map_37_state_01_08ECD814, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Oh, I'm imagining things, am\n"
      "I?\n\n"
      "You cannot deceive me.\n\n"
      "I can tell you're hiding\n"
      "something...important.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You do not have to reveal\n"
      "your secrets if you are not\n\n"
      "so inclined.\n\n"
      "But I will let you know that\n"
      "the tides have been far\n\n"
      "from normal.\n\n"
      "If anything has to do with\n"
      "this mystery...\n\n"
      "Go deeper into the island.\n"
      "You may find something.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD820, map_37_state_01_08ECD820, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "There's something wrong with\n"
      "the sea.\n\n"
      "I hope it's not a sign of\n"
      "some impending catastrophe.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD7F0, map_37_state_01_08ECD7F0, 0x08ECD7FC, 0x08ECD82C)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_MAKO)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD82C, map_37_state_01_08ECD82C, 0x08ECD838, 0x08F0404C)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_MAKO_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Fine! Mako Tsunami does not\n"
      "flee from any challenge!\n\n"
  )
  DUEL(48)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD838, map_37_state_01_08ECD838, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_246)
  PORTRAIT(PORTRAIT_MAKO, EXPRESSION_MAKO_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Excellent duel!\n\n"
      "But next time, you won't win\n"
      "so easily!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
