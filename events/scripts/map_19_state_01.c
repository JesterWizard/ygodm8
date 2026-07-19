#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_19_state_01: map 19 state 1 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E83A84, map_19_state_01_08E83A84, 0x08E83A9C, 0x08E83B44)
  LOAD_SPRITE(1, SPRITE_BONZ)
  LOAD_SPRITE(2, SPRITE_YUGI)
  LOAD_SPRITE(3, SPRITE_JOEY)
  LOAD_SPRITE(4, SPRITE_BANDIT_KEITH)
  LOAD_SPRITE(5, SPRITE_ARKANA)
  LOAD_SPRITE(6, SPRITE_STRINGS)
  LOAD_SPRITE(7, SPRITE_SEEKER)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83A9C, map_19_state_01_08E83A9C, 0x08E83AA8, 0x08E83AB4)
  WALK_OBJECT_Y(0, 60)
  WALK_OBJECT_X(0, 96)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 70)
  WALK_OBJECT_X(13, 102)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 70)
  WALK_OBJECT_X(14, 90)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BONZ,
      "Welcome to the Catacombs.",
      "This is a communal graveyard from long,",
      "long ago.",
      "I'm Bonz, your tour guide.",
      "If you'd like, I'll show you sights you've never seen",
      "before."
  )
  TALK(PORTRAIT_NONE, "{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AA8, map_19_state_01_08E83AA8, 0x08E83AC0, EVENT_NOP)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED,
      "Man, why do we hafta sightsee in this spooky",
      "place... Not that I'm scared!"
  )
  TALK(PORTRAIT_BONZ,
      "What are you talking about? This place is the best!",
      "If you're not tourists, what brings you here?"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AC0, map_19_state_01_08E83AC0, 0x08E83ACC, 0x08E83AD8)
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  TALK(PORTRAIT_BONZ, "You're searching for a Millennium Item?")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_1)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I'm not sure if that thing is a Millennium Item...")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, "{PLAYER}, Bonz seems to know something!")
  TALK(PORTRAIT_NONE, "{CARD_1}Where is it?\nLet's duel!{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83ACC, map_19_state_01_08E83ACC, 0x08E83AE4, EVENT_NOP)
  TALK(PORTRAIT_BONZ, "...I may not look like one, but I'm a duelist, too.")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "If you want to get my info...",
      "Duel against my ghouls!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AE4, map_19_state_01_08E83AE4, 0x08E83AF0, 0x08F0404C)
  TEXT(
      "I'll tell you what I know if you can beat me.",
      "But what are your chances against my powerful Neo",
      "Ghost Deck!"
  )
  DUEL(DUELIST_BONZ_036)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AF0, map_19_state_01_08E83AF0, 0x08E83AFC, 0x08E83B08)
  TALK(PORTRAIT_BONZ, "No! I lost!")
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_1 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  WALK_OBJECT_X(4, 56)
  WALK_OBJECT_X(6, 44)
  WALK_OBJECT_X(7, 40)
  DELAY(8)
  PLAY_MUSIC(MUSIC_407)
  TALK(PORTRAIT_BANDIT_KEITH,
      "Kukuku...",
      "You said your deck's improved, but it's the same",
      "lame deck as always, Bonz."
  )
  TALK(PORTRAIT_BONZ, "B-Bandit Keith!")
  TALK(PORTRAIT_BANDIT_KEITH,
      "I've never seen so many losers in one place!",
      "I've watched tougher duels in kindergarten!"
  )
  TALK(PORTRAIT_NONE, "{CARD_1}I'll take you on!\nWho's behind you?{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AFC, map_19_state_01_08E83AFC, 0x08E83B14, EVENT_NOP)
  TALK(PORTRAIT_BANDIT_KEITH,
      "Kukuku... We could duel, but...",
      "I'm not in the mood. I'm just here to show you that",
      "I'm alive and kickin'!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B14, map_19_state_01_08E83B14, 0x08E83B20, 0x08E83B2C)
  TEXT(
      "After Marik's pathetic defeat, I took control of",
      "the Ghouls and their Rare Hunters."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PORTRAIT(PORTRAIT_STRINGS, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  DELAY(64)
  PORTRAIT(PORTRAIT_SEEKER, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  DELAY(64)
  TALK(PORTRAIT_BANDIT_KEITH,
      "The Ghouls are now reborn as the Neo Ghouls!",
      "And I, Bandit Keith, am the leader of the Neo Ghouls!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(5, 48)
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  TALK(PORTRAIT_ARCANA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Master Keith...",
      "We have obtained the information you seek..."
  )
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "So that's the key item for getting the Egyptian God",
      "Cards...",
      "Kukuku... With this info, I've earned the right to",
      "join the game..."
  )
  TALK(PORTRAIT_NONE, "{CARD_1}You want the God Cards?\nJoin the game?{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B20, map_19_state_01_08E83B20, 0x08E83B38, EVENT_NOP)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BANDIT_KEITH,
      "You know why!",
      "I need 'em to thrash that arrogant punk!",
      "I'll do anything, and I mean anything, to beat him!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B38, map_19_state_01_08E83B38, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I'll let you in on a little secret.",
      "You won't find what you're looking for here.",
      "See you losers around.",
      "Kukuku..."
  )
  WALK_OBJECT_X(4, 248)
  WALK_OBJECT_X(6, 248)
  WALK_OBJECT_X(7, 248)
  WALK_OBJECT_X(5, 248)
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_DEFEATED_BONZ)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B2C, map_19_state_01_08E83B2C, 0x08E83B38, EVENT_NOP)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BANDIT_KEITH,
      "Heh, it's not fair that you runts get all the fun.",
      "We want to take part, too. Oh, and another thing...",
      "I'll do anything to thrash that arrogant punk!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B08, map_19_state_01_08E83B08, 0x08E83B14, EVENT_NOP)
  TALK(PORTRAIT_BANDIT_KEITH, "Oops, I forgot to introduce you to my crew.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AD8, map_19_state_01_08E83AD8, 0x08E83AE4, EVENT_NOP)
  TALK(PORTRAIT_BONZ,
      "I see you have the heart of a duelist.",
      "I accept your duel!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AB4, map_19_state_01_08E83AB4, 0x08E83AC0, EVENT_NOP)
  TALK(PORTRAIT_BONZ, "Then what brings you here?")
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B44, map_19_state_01_08E83B44, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_BONZ, "Bandit Keith said you won't find anything here...")
  TEXT("But there's a hidden chamber in the back.")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  TALK(PORTRAIT_BONZ,
      "I bet Bandit Keith's gang couldn't get in.",
      "It's over here."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 108)
  WALK_OBJECT_Y(1, 64)
  WALK_OBJECT_X(1, 128)
  SET_FLAG(EVENT_FLAG_BONZ_SAID_THERE_IS_A_HIDDEN_CHAMBER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83A90, map_19_state_01_08E83A90, 0x08E83A9C, 0x08E83B44)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_BONZ)
  FALLTHROUGH()
END_EVENT_SCRIPT()
