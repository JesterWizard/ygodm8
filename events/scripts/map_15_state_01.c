#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_01: map 15 state 1 */

LOAD_SPRITE(1, SPRITE_NERVOUS_DUELIST)
LOAD_SPRITE(2, SPRITE_ARROGANT_DUELIST)
LOAD_SPRITE(3, SPRITE_INSECURE_DUELIST)
LOAD_SPRITE(4, SPRITE_KAIBACORP_ADMIRER)
LOAD_SPRITE(5, SPRITE_DOMINO_STATION_GUARD_2)
PLAY_MUSIC(MUSIC_231)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "The Duel Express is reserved\n"
    "for duelists only...\n\n"
    "I'm raring to go!\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Yeah, I know.\n\n"
    "But if we raise our duelist\n"
    "level while we look for the\n\n"
    "Millennium Items...\n\n"
    "That's like killing two\n"
    "birds with one stone.\n\n"
)

EVENT_SCRIPT_REPLACEMENT(0x08E7A470, map_15_state_01_08E7A470, 0x08F04040, 0x08F04040)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Me neither!\n\n"
    "It'll be a while until we\n"
    "reach the Egypt Exhibition.\n\n"
    "Let's raise our duelist\n"
    "levels while we can!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A47C, map_15_state_01_08E7A47C, 0x08E7A494, 0x08E7A4B8)
CHECK_FLAG(EVENT_FLAG_DEFEATED_NERVOUS_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A494, map_15_state_01_08E7A494, 0x08F04040, 0x08F04040)
TEXT
  (
      "W-"
  )
  DELAY(8)
  TEXT
  (
      "w-"
  )
  DELAY(8)
  TEXT
  (
      "w-"
  )
  DELAY(8)
  TEXT
  (
      "what?\n\n"
      "I-"
  )
  DELAY(8)
  TEXT
  (
      "I-"
  )
  DELAY(8)
  TEXT
  (
      "I-"
  )
  DELAY(8)
  TEXT
  (
      "I'm\n"
      "n-"
  )
  DELAY(8)
  TEXT
  (
      "not "
  )
  DELAY(8)
  TEXT
  (
      "n-n-nervous!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4B8, map_15_state_01_08E7A4B8, 0x08F04040, 0x08F04040)
TEXT
  (
      "That one duel calmed me\n"
      "down!\n\n"
      "Thank you!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A488, map_15_state_01_08E7A488, 0x08E7A4A0, 0x08E7A4B8)
CHECK_FLAG(EVENT_FLAG_DEFEATED_NERVOUS_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4A0, map_15_state_01_08E7A4A0, 0x08E7A4AC, 0x08F0404C)
TEXT
  (
      "W-"
  )
  DELAY(8)
  TEXT
  (
      "w-"
  )
  DELAY(8)
  TEXT
  (
      "w-"
  )
  DELAY(8)
  TEXT
  (
      "well, okay.\n\n"
      "I-"
  )
  DELAY(8)
  TEXT
  (
      "i-"
  )
  DELAY(8)
  TEXT
  (
      "it's t-t-time to\n"
      "d-d-d-duel!\n\n"
  )
  DUEL(DUELIST_JOEY_017)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4AC, map_15_state_01_08E7A4AC, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "Wow, "
  )
  DELAY(8)
  TEXT
  (
      "losing helped me relax.\n"
      "There's no more pressure to\n\n"
      "win.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_NERVOUS_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4C4, map_15_state_01_08E7A4C4, 0x08F04040, 0x08F04040)
TEXT
  (
      "What a motley crew of\n"
      "pathetic duelists.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4D0, map_15_state_01_08E7A4D0, 0x08E7A4DC, 0x08E7A4F4)
CHECK_FLAG(EVENT_FLAG_DEFEATED_ARROGANT_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4DC, map_15_state_01_08E7A4DC, 0x08E7A4E8, 0x08F0404C)
TEXT
  (
      "Why? The tourney hasn't\n"
      "started yet, and we still\n\n"
      "haven't boarded the Duel\n"
      "Express!\n\n"
      "But I like your spunk!\n"
      "I accept your challenge!\n\n"
  )
  DUEL(DUELIST_JOEY_018)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4E8, map_15_state_01_08E7A4E8, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "I'm saving my real\n"
      "strategies for the\n\n"
      "tournament..\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_ARROGANT_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A4F4, map_15_state_01_08E7A4F4, 0x08F04040, 0x08F04040)
TEXT
  (
      "I'll take you on again\n"
      "inside the train.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A50C, map_15_state_01_08E7A50C, 0x08F04040, 0x08F04040)
TEXT
  (
      "Everyone looks so tough.\n\n"
      "I'm not sure if I can last\n"
      "until the end.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A500, map_15_state_01_08E7A500, 0x08E7A518, 0x08E7A530)
CHECK_FLAG(EVENT_FLAG_DEFEATED_INSECURE_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A518, map_15_state_01_08E7A518, 0x08E7A524, 0x08F0404C)
TEXT
  (
      "But you don't look so\n"
      "tough...\n\n"
  )
  DELAY(8)
  TEXT
  (
      "I think I can beat you.\n\n"
  )
  DUEL(DUELIST_JOEY_019)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A524, map_15_state_01_08E7A524, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "How could I lose to someone\n"
      "like you?\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_INSECURE_DUELIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A530, map_15_state_01_08E7A530, 0x08F04040, 0x08F04040)
TEXT
  (
      "I'm fixing my deck.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A53C, map_15_state_01_08E7A53C, 0x08F04040, 0x08F04040)
TEXT
  (
      "KaibaCorp sure knows how to\n"
      "throw an event.\n\n"
      "They're letting us ride a\n"
      "chartered express train for\n\n"
      "free.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A548, map_15_state_01_08E7A548, 0x08E7A554, 0x08E7A56C)
CHECK_FLAG(EVENT_FLAG_DEFEATED_KAIBA_CORP_ADMIRER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A554, map_15_state_01_08E7A554, 0x08E7A560, 0x08F0404C)
TEXT
  (
      "Huh, sure.\n\n"
  )
  DUEL(DUELIST_JOEY_020)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A560, map_15_state_01_08E7A560, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "Oh, yup, I lost. But that\n"
      "was fun.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA_CORP_ADMIRER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A56C, map_15_state_01_08E7A56C, 0x08F04040, 0x08F04040)
TEXT
  (
      "The train's leaving soon.\n"
      "Next time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A578, map_15_state_01_08E7A578, 0x08F04040, 0x08F04040)
TEXT
  (
      "The Duel Express is bound\n"
      "for the Egypt Exhibition.\n\n"
      "The station is very crowded\n"
      "due to the duel tournament.\n\n"
      "Please board the train in an\n"
      "orderly manner.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A584, map_15_state_01_08E7A584, 0x08E7A590, 0x08E7A5A8)
CHECK_FLAG(EVENT_FLAG_DEFEATED_DOMINO_STATION_GUARD2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A590, map_15_state_01_08E7A590, 0x08E7A59C, 0x08F0404C)
TEXT
  (
      "Uhh, I'm on duty...\n\n"
      "B-but, I did want to give\n"
      "this game a try.\n\n"
      "Let's duel!\n\n"
  )
  DUEL(DUELIST_JOEY_021)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A59C, map_15_state_01_08E7A59C, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_231)
  TEXT
  (
      "I quite enjoyed that.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_DOMINO_STATION_GUARD2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5A8, map_15_state_01_08E7A5A8, 0x08F04040, 0x08F04040)
TEXT
  (
      "The next stop is the Egypt\n"
      "Exhibition.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
