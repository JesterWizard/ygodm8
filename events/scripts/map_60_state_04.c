#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_60_state_04: map 60 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08F039D8, map_60_state_04_08F039D8, 0x08F039E4, 0x08F0404C)
  LOAD_SPRITE(1, SPRITE_MARIK)
  LOAD_SPRITE(2, SPRITE_ODION)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Urk... Yeah, you're right.\n"
      "Ra is seriously scary.\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "So, I have a proposal,\n"
      "{PLAYER}.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I will test you.\n\n"
      "I will determine if you are\n"
      "worthy of using Ra.\n\n"
      "If you fail to defeat me in\n"
      "a duel...\n\n"
      "Then you are unfit to bear\n"
      "The Winged Dragon of Ra!\n\n"
      "All right! It's time to\n"
      "duel!\n\n"
  )
  DUEL(158)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F039E4, map_60_state_04_08F039E4, 0x08F039FC, 0x08F039F0)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I see... You have learned\n"
      "much from your previous\n\n"
      "duels..\n\n"
      "{PLAYER}, I believe that you\n"
      "can control Ra.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 64)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I need The Winged Dragon of\n"
      "Ra.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  DELAY(16)
  WALK_OBJECT_Y(1, 44)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  PLAY_MUSIC(MUSIC_360)
  REACTION(REACTION_CHANT, OBJECT_1)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Awaken! The Winged Dragon of\n"
      "Ra!\n\n"
  )
  PLAY_MUSIC(MUSIC_377)
  COMMAND_7C_ARG(8, 48)
  PLAY_MUSIC(MUSIC_359)
  COMMAND_7C_ARG(8, 43)
  COMMAND_7C_ARG(8, 45)
  PLAY_MUSIC(MUSIC_378)
  COMMAND_7C_ARG(8, 49)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 64)
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  REMOVE_CARD(297)
  ADD_CARD(240)
  DELAY(16)
  WALK_OBJECT_Y(1, 44)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Received The Winged Dragon\n"
      "of Ra {BYTE_8169}Battle Mode{BYTE_816A}.\n\n"
  )
  TEXT
  (
      "The deck adjustment menu\n"
      "will be opened."
  )
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F039FC, map_60_state_04_08F039FC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ra has awakened...\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah! That's it!\n\n"
      "The Winged Dragon of Ra is\n"
      "back in all its glory!\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "...Unfortunately, no.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wh-what are you saying,\n"
      "Marik?\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Have you forgotten?\n\n"
      "The Winged Dragon of Ra has\n"
      "one other form.\n\n"
      "Its immortal form... The\n"
      "Phoenix Mode.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I remember that... That's\n"
      "the scariest mode of them\n\n"
      "all.\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yes. Exactly.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Then wake that form up!\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That... I cannot do now.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "It's true that I woke up the\n"
      "third form in the past.\n\n"
      "However, that was when\n"
      "darkness ruled my heart.\n\n"
      "I have no idea how to awaken\n"
      "it now.\n\n"
      "There must be a secret...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But there is nothing to\n"
      "fear.\n\n"
      "Ra is immensely powerful\n"
      "even in its present form.\n\n"
      "It should be sufficient to\n"
      "help seal the Dark Being.\n\n"
      "However, there must be a\n"
      "secret behind the Phoenix\n\n"
      "Mode.\n\n"
      "You should return if you\n"
      "discover what it is.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We'll do that, Marik.\n\n"
      "I'm sure Paradox will help\n"
      "us.\n\n"
      "He'll tell us where\n"
      "Pegasus's castle is.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah!\n\n"
      "Phoenix Mode or not, we can\n"
      "get the job done!\n\n"
      "We'll put Reshef down for\n"
      "good!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_MARIK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F039F0, map_60_state_04_08F039F0, 0x08F039FC, 0x08F039F0)
  TEXT
  (
      "The deck adjustment menu\n"
      "will be opened."
  )
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()
