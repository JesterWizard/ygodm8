#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_19_state_01: map 19 state 1 */

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
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Welcome to the Catacombs.\n\n"
    "This is a communal\n"
    "graveyard from long,\n\n"
    "long ago.\n\n"
    "I'm Bonz, your tour guide.\n\n"
    "If you'd like, I'll show you\n"
    "sights you've never seen\n\n"
    "before.\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "{CARD_1}Yes\n"
    "No{CARD_2}\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AA8, map_19_state_01_08E83AA8, 0x08E83AC0, 0x08F04040)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_LEFT,
    "Man, why do we hafta\n"
    "sightsee in this spooky\n\n"
    "place... Not that I'm\n"
    "scared!\n\n"
)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "What are you talking about?\n"
    "This place is the best!\n\n"
    "If you're not tourists, what\n"
    "brings you here?\n\n"
)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AC0, map_19_state_01_08E83AC0, 0x08E83ACC, 0x08E83AD8)
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "You're searching for a\n"
    "Millennium Item?\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_1)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I'm not sure if that thing\n"
    "is a Millennium Item...\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_LEFT,
    "{PLAYER}, Bonz seems to know\n"
    "something!\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "{CARD_1}Where is it?\n"
    "Let's duel!{CARD_2}\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83ACC, map_19_state_01_08E83ACC, 0x08E83AE4, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "...I may not look like one,\n"
    "but I'm a duelist, too.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "If you want to get my\n"
    "info...\n\n"
    "Duel against my ghouls!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AE4, map_19_state_01_08E83AE4, 0x08E83AF0, 0x08F0404C)
  TEXT
  (
      "I'll tell you what I know if\n"
      "you can beat me.\n\n"
      "But what are your chances\n"
      "against my powerful Neo\n\n"
      "Ghost Deck!\n\n"
  )
  DUEL(DUELIST_BONZ_036)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AF0, map_19_state_01_08E83AF0, 0x08E83AFC, 0x08E83B08)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "No! I lost!\n\n"
)
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
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Kukuku...\n\n"
    "You said your deck's\n"
    "improved, but it's the same\n\n"
    "lame deck as always, Bonz.\n\n"
)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "B-Bandit Keith!\n\n"
)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I've never seen so many\n"
    "losers in one place!\n\n"
    "I've watched tougher duels\n"
    "in kindergarten!\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "{CARD_1}I'll take you on!\n"
    "Who's behind you?{CARD_2}\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AFC, map_19_state_01_08E83AFC, 0x08E83B14, 0x08F04040)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Kukuku... We could duel,\n"
    "but...\n\n"
    "I'm not in the mood. I'm\n"
    "just here to show you that\n\n"
    "I'm alive and kickin'!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B14, map_19_state_01_08E83B14, 0x08E83B20, 0x08E83B2C)
  TEXT
  (
      "After Marik's pathetic\n"
      "defeat, I took control of\n\n"
      "the Ghouls and their Rare\n"
      "Hunters.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PORTRAIT(PORTRAIT_STRINGS, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  DELAY(64)
  PORTRAIT(PORTRAIT_SEEKER, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  DELAY(64)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "The Ghouls are now reborn as\n"
    "the Neo Ghouls!\n\n"
    "And I, Bandit Keith, am the\n"
    "leader of the Neo Ghouls!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(5, 48)
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  TALK(PORTRAIT_ARCANA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "Master Keith...\n\n"
    "We have obtained the\n"
    "information you seek...\n\n"
)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
    "So that's the key item for\n"
    "getting the Egyptian God\n\n"
    "Cards...\n\n"
    "Kukuku... With this info,\n"
    "I've earned the right to\n\n"
    "join the game...\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "{CARD_1}You want the God Cards?\n"
    "Join the game?{CARD_2}\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B20, map_19_state_01_08E83B20, 0x08E83B38, 0x08F04040)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "You know why!\n\n"
    "I need 'em to thrash that\n"
    "arrogant punk!\n\n"
    "I'll do anything, and I mean\n"
    "anything, to beat him!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B38, map_19_state_01_08E83B38, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'll let you in on a little\n"
      "secret.\n\n"
      "You won't find what you're\n"
      "looking for here.\n\n"
      "See you losers around.\n\n"
      "Kukuku...\n\n"
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

EVENT_SCRIPT_REPLACEMENT(0x08E83B2C, map_19_state_01_08E83B2C, 0x08E83B38, 0x08F04040)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Heh, it's not fair that you\n"
    "runts get all the fun.\n\n"
    "We want to take part, too.\n"
    "Oh, and another thing...\n\n"
    "I'll do anything to thrash\n"
    "that arrogant punk!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B08, map_19_state_01_08E83B08, 0x08E83B14, 0x08F04040)
  TALK(PORTRAIT_BANDIT_KEITH, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Oops, I forgot to introduce\n"
    "you to my crew.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AD8, map_19_state_01_08E83AD8, 0x08E83AE4, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I see you have the heart of\n"
    "a duelist.\n\n"
    "I accept your duel!\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83AB4, map_19_state_01_08E83AB4, 0x08E83AC0, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Then what brings you here?\n\n"
)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E83B44, map_19_state_01_08E83B44, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "Bandit Keith said you won't\n"
    "find anything here...\n\n"
)
  TEXT
  (
      "But there's a hidden chamber\n"
      "in the back.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_LEFT,
    "I bet Bandit Keith's gang\n"
    "couldn't get in.\n\n"
    "It's over here.\n\n"
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
