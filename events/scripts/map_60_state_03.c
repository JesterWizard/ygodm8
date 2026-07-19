#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_60_state_03: map 60 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08F03AD4, map_60_state_03_08F03AD4, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_MARIK)
  LOAD_SPRITE(2, SPRITE_ODION)
  FADE_MUSIC(4)
  FADE_SCREEN(4)
  CLEAR_FLAG(226)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A68, map_60_state_03_08F03A68, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Winged Dragon of Ra has been fully awakened.",
      "{PLAYER}!",
      "Imprison Reshef with the power of Ra!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A74, map_60_state_03_08F03A74, 0x08F03A80, 0x08F0404C)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You wish to test Ra's full power on me?",
      "Fine. I accept.",
      "I will not hold anything back!"
  )
  DUEL(DUELIST_MARIK_158)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A80, map_60_state_03_08F03A80, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "...You are a true duelist.",
      "You can fully control The Winged Dragon of Ra.",
      "I did not realize how powerful you have become",
      "until now."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03AB0, map_60_state_03_08F03AB0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Reshef toys with the spirits of duelists...",
      "It dominates through deception and terror.",
      "But before the Phoenix Mode, it will cower."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03ABC, map_60_state_03_08F03ABC, 0x08F03AC8, 0x08F0404C)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}, you have obtained the power of the Egyptian",
      "God Phoenix.",
      "I have little idea how I will fare against you.",
      "But I accept your challenge. It's time to duel!"
  )
  DUEL(DUELIST_ODION_157)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03AC8, map_60_state_03_08F03AC8, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  TALK(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Ah, yes. You have mastered the Phoenix Mode.",
      "I am no match for your brilliance."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
