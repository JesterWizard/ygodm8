#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_29_state_07: map 29 state 7 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08EAC90C, map_29_state_07_08EAC90C, 0x08EAC918, 0x08EAC924)
  LOAD_SPRITE(1, SPRITE_BONZ)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC918, map_29_state_07_08EAC918, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Ahhh... It's good to be back in the dark.",
      "I don't know why everyone want to be in the light.",
      "It's so relaxing...",
      "But something doesn't feel right...",
      "It feels the same as the time I was taking orders",
      "from Bandit Keith...",
      "The best way to forget my troubles is to have a duel!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC924, map_29_state_07_08EAC924, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Your journey is far from over.",
      "But my card will definitely help you."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC930, map_29_state_07_08EAC930, 0x08EAC93C, 0x08EAC954)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC93C, map_29_state_07_08EAC93C, 0x08EAC948, 0x08F0404C)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_1)
  DELAY(8)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I've dueled you before, {PLAYER}...",
      "But I've never seen you so determined.",
      "You must be preparing for an enormous duel.",
      "Okay! {PLAYER}, I'll duel you anytime you want."
  )
  DUEL(DUELIST_BONZ_100)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC948, map_29_state_07_08EAC948, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I lost because you wanted to win more than I did.",
      "It's easy to tell you're preparing for a great",
      "battle, {PLAYER}.",
      "You have an enormous weight on your shoulders. I wish I",
      "could help you...",
      "I know! Take this card.",
      "It represents me.",
      "It's Pumpking the King of Ghosts.",
      "I know it will come in handy..."
  )
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Received Pumpking the King of Ghosts.")
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_ITALY)
  PAGE_BREAK()
  ADD_CARD(99)
  SET_FLAG(EVENT_FLAG_DEFEATED_BONZ3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC954, map_29_state_07_08EAC954, 0x08EAC960, 0x08F0404C)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I'm a better duelist now than when I was in Bandit",
      "Keith's gang.",
      "If dueling me will hone your skills...",
      "I'll duel you anytime you want."
  )
  DUEL(DUELIST_BONZ_148)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC960, map_29_state_07_08EAC960, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_ITALY)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "D-did I help you a little?",
      "I'm rooting for you. Win!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
