#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_37_state_05: map 37 state 5 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08ECD844, map_37_state_05_08ECD844, 0x08ECD850, 0x08ECD85C)
  LOAD_SPRITE(1, SPRITE_MAKO)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD850, map_37_state_05_08ECD850, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Do you sense it? The tortured waves,",
      "the crashing sea...",
      "Something's wrong. Something's different."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD85C, map_37_state_05_08ECD85C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I've passed you my spirit.",
      "Just as the world's oceans are connected, our souls",
      "are united."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD868, map_37_state_05_08ECD868, 0x08ECD874, 0x08ECD88C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD874, map_37_state_05_08ECD874, 0x08ECD880, 0x08F0404C)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}, you feel it, too?",
      "The sea... It's afraid.",
      "The ocean is terrified!",
      "{PLAYER}, you are intending to fight something that can",
      "paralyze the waters to its briny deep!",
      "Do not deny it. I can tell.",
      "In that case, take my spirit to battle with you!"
  )
  DUEL(DUELIST_MAKO_103)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD880, map_37_state_05_08ECD880, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_249)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I've passed you my spirit.",
      "Just as the world's oceans are connected, our souls",
      "are united.",
      "Wait, take my spirit card.",
      "It's The Legendary Fisherman.",
      "The sea will drown you if you show fear.",
      "It's the same with dueling.",
      "Keep fighting without fear!"
  )
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Received The Legendary Fisherman.")
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_249)
  PAGE_BREAK()
  ADD_CARD(257)
  SET_FLAG(EVENT_FLAG_DEFEATED_MAKO3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD88C, map_37_state_05_08ECD88C, 0x08ECD898, 0x08F0404C)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "No matter how tough the enemy, there's nothing to",
      "fear!",
      "Attack your foe with all your might!",
      "I'm going to give my all in this duel!"
  )
  DUEL(DUELIST_MAKO_150)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ECD898, map_37_state_05_08ECD898, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_249)
  TALK(PORTRAIT_MAKO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Did you learn anything from this duel?",
      "All oceans may look the same to you, but I can tell the",
      "difference.",
      "You just need to develop a discerning eye."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
