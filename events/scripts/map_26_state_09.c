#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_09: map 26 state 9 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08EA3D88, map_26_state_09_08EA3D88, 0x08EA3D94, 0x08EA3DA0)
  LOAD_SPRITE(1, SPRITE_MAI)
  LOAD_SPRITE(2, SPRITE_RICH_HUSBAND)
  LOAD_SPRITE(3, SPRITE_RICHE_WIFE)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D94, map_26_state_09_08EA3D94, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}... You came here for a reason, didn't you?",
      "Whatever it is, I'm here to help.",
      "Challenge me whenever you feel ready.",
      "As duelists, we understand each other the best when we",
      "duel.",
      "It sounds weird, but it's true."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DA0, map_26_state_09_08EA3DA0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The people in the Town of Domino are happy now that",
      "the Neo Ghouls are gone.",
      "But don't you sense something strange?",
      "I don't know what it is, but it doesn't feel good.",
      "It feels like the last turn of a duel that I'm about to",
      "lose.",
      "It's just awful!",
      "{PLAYER}, this enemy that you're facing...",
      "Who is it?",
      "Who can create so much tension in the air?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DAC, map_26_state_09_08EA3DAC, 0x08EA3DB8, 0x08EA3DD0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DB8, map_26_state_09_08EA3DB8, 0x08EA3DC4, 0x08F0404C)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Duelists get to know each other through dueling.",
      "Once duelists battle, a bond develops that didn't exist",
      "before.",
      "{PLAYER}, I accept your duel!"
  )
  DUEL(DUELIST_MAI_097)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DC4, map_26_state_09_08EA3DC4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}...",
      "I can tell you're planning to face something huge and",
      "terrible...",
      "But you'll be fine.",
      "There's a bond between us!",
      "Even when we're far apart, our hearts beat as one.",
      "This is Harpie Lady. It represents my spirit as a",
      "duelist.",
      "I'm not required to give it to you, but I want you to",
      "have it."
  )
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Received Harpie Lady."
)
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  PAGE_BREAK()
  ADD_CARD(62)
  SET_FLAG(EVENT_FLAG_DEFEATED_MAI3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DD0, map_26_state_09_08EA3DD0, 0x08EA3DDC, 0x08F0404C)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}, I don't know what you're facing.",
      "But I know it won't be easy.",
      "Remember that every duelist has unlimited potential.",
      "If you think it'll help, I'll duel you anytime!"
  )
  DUEL(DUELIST_MAI_147)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3DDC, map_26_state_09_08EA3DDC, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_DOMINO_PIER)
  TALK(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Did this duel help you?",
      "Don't lose, {PLAYER}!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
