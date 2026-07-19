#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_38_state_05: map 38 state 5 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08ED1688, map_38_state_05_08ED1688, 0x08ED1694, 0x08ED16A0)
  LOAD_SPRITE(1, SPRITE_WEEVIL)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED1694, map_38_state_05_08ED1694, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Hyo?",
      "You're looking for bugs too, {PLAYER}?",
      "Too bad. There aren't any bugs around.",
      "They all disappeared as if something scared them.",
      "I have a really bad feeling about this."
  )
  SET_FLAG(EVENT_FLAG_TALKED_TO_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16A0, map_38_state_05_08ED16A0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The bugs all disappeared as if they were scared.",
      "I have a really bad feeling about this."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16AC, map_38_state_05_08ED16AC, 0x08ED16B8, 0x08ED16D0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16B8, map_38_state_05_08ED16B8, 0x08ED16C4, 0x08F0404C)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO,
      "Hyohyohyo!",
      "You want to be infested by my Super Insect deck?"
  )
  DUEL(DUELIST_WEEVIL_104)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16C4, map_38_state_05_08ED16C4, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_250)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "My Queen!",
      "Humph, humph, humph!",
      "I can't beat you when you take enormous risks in a",
      "duel! All my strategies become as weak as a worm!",
      "Take this with you.",
      "It's Insect Queen, the card that represents me.",
      "It's a useful rare card...",
      "But only if you consider it as my spirit..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Arrrrgh, what a terrible waste...",
      "I wasted a rare card on you...",
      "Get outta here! Bye-bye, my beautiful bug!"
  )
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Received Insect Queen."
)
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_250)
  PAGE_BREAK()
  ADD_CARD(762)
  SET_FLAG(EVENT_FLAG_DEFEATED_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16D0, map_38_state_05_08ED16D0, 0x08ED16DC, 0x08F0404C)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Oh, okay okay!",
      "If you insist on bugging me, I'll duel you!"
  )
  DUEL(DUELIST_WEEVIL_151)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16DC, map_38_state_05_08ED16DC, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_247)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You stole my technique!",
      "You knew my strategies were the best!",
      "If you're using my tactics, you better not lose! Or",
      "I'll pour cockroaches down your pants!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
