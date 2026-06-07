#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_29_state_07: map 29 state 7 */

EVENT_SCRIPT_REPLACEMENT(0x08EAC90C, map_29_state_07_08EAC90C, 0x08EAC918, 0x08EAC924)
  LOAD_SPRITE(1, SPRITE_BONZ)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC918, map_29_state_07_08EAC918, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Ahhh... It's good to be back\n"
    "in the dark.\n\n"
    "I don't know why everyone\n"
    "want to be in the light.\n\n"
    "It's so relaxing...\n\n"
    "But something doesn't feel\n"
    "right...\n\n"
    "It feels the same as the\n"
    "time I was taking orders\n\n"
    "from Bandit Keith...\n\n"
    "The best way to forget my\n"
    "troubles is to have a duel!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC924, map_29_state_07_08EAC924, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Your journey is far from\n"
    "over.\n\n"
    "But my card will definitely\n"
    "help you.\n\n"
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
    "I've dueled you before,\n"
    "{PLAYER}...\n\n"
    "But I've never seen you so\n"
    "determined.\n\n"
    "You must be preparing for an\n"
    "enormous duel.\n\n"
    "Okay! {PLAYER}, I'll duel\n"
    "you anytime you want.\n\n"
)
  DUEL(DUELIST_BONZ_100)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC948, map_29_state_07_08EAC948, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I lost because you wanted to\n"
    "win more than I did.\n\n"
    "It's easy to tell you're\n"
    "preparing for a great\n\n"
    "battle, {PLAYER}.\n\n"
    "You have an enormous weight\n"
    "on your shoulders. I wish I\n\n"
    "could help you...\n\n"
    "I know! Take this card.\n\n"
    "It represents me.\n\n"
    "It's Pumpking the King of\n"
    "Ghosts.\n\n"
    "I know it will come in\n"
    "handy...\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Received Pumpking the King\n"
    "of Ghosts."
)
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
    "I'm a better duelist now\n"
    "than when I was in Bandit\n\n"
    "Keith's gang.\n\n"
    "If dueling me will hone your\n"
    "skills...\n\n"
    "I'll duel you anytime you\n"
    "want.\n\n"
)
  DUEL(DUELIST_BONZ_148)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC960, map_29_state_07_08EAC960, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_ITALY)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "D-did I help you a little?\n\n"
    "I'm rooting for you. Win!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
