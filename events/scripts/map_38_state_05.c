#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_38_state_05: map 38 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08ED1688, map_38_state_05_08ED1688, 0x08ED1694, 0x08ED16A0)
  LOAD_SPRITE(1, SPRITE_WEEVIL)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED1694, map_38_state_05_08ED1694, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Hyo?\n\n"
    "You're looking for bugs too,\n"
    "{PLAYER}?\n\n"
    "Too bad. There aren't any\n"
    "bugs around.\n\n"
    "They all disappeared as if\n"
    "something scared them.\n\n"
    "I have a really bad feeling\n"
    "about this.\n\n"
)
  SET_FLAG(EVENT_FLAG_TALKED_TO_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16A0, map_38_state_05_08ED16A0, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "The bugs all disappeared as\n"
    "if they were scared.\n\n"
    "I have a really bad feeling\n"
    "about this.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16AC, map_38_state_05_08ED16AC, 0x08ED16B8, 0x08ED16D0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_WEEVIL3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16B8, map_38_state_05_08ED16B8, 0x08ED16C4, 0x08F0404C)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_WEEVIL_HAPPY, PORTRAIT_POSITION_AUTO,
    "Hyohyohyo!\n\n"
    "You want to be infested by\n"
    "my Super Insect deck?\n\n"
)
  DUEL(DUELIST_WEEVIL_104)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16C4, map_38_state_05_08ED16C4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_250)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "My Queen!\n\n"
    "Humph, humph, humph!\n\n"
    "I can't beat you when you\n"
    "take enormous risks in a\n\n"
    "duel! All my strategies\n"
    "become as weak as a worm!\n\n"
    "Take this with you.\n\n"
    "It's Insect Queen, the card\n"
    "that represents me.\n\n"
    "It's a useful rare card...\n\n"
    "But only if you consider it\n"
    "as my spirit...\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Arrrrgh, what a terrible\n"
    "waste...\n\n"
    "I wasted a rare card on\n"
    "you...\n\n"
    "Get outta here! Bye-bye, my\n"
    "beautiful bug!\n\n"
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
    "Oh, okay okay!\n\n"
    "If you insist on bugging me,\n"
    "I'll duel you!\n\n"
)
  DUEL(DUELIST_WEEVIL_151)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08ED16DC, map_38_state_05_08ED16DC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_247)
  TALK(PORTRAIT_WEEVIL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You stole my technique!\n\n"
    "You knew my strategies were\n"
    "the best!\n\n"
    "If you're using my tactics,\n"
    "you better not lose! Or\n\n"
    "I'll pour cockroaches down\n"
    "your pants!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
