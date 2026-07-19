#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_60_state_04: map 60 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08F039D8, map_60_state_04_08F039D8, 0x08F039E4, 0x08F0404C)
  LOAD_SPRITE(1, SPRITE_MARIK)
  LOAD_SPRITE(2, SPRITE_ODION)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO, "Urk... Yeah, you're right. Ra is seriously scary.")
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "So, I have a proposal, {PLAYER}.")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I will test you.",
      "I will determine if you are worthy of using Ra.",
      "If you fail to defeat me in a duel...",
      "Then you are unfit to bear The Winged Dragon of Ra!",
      "All right! It's time to duel!"
  )
  DUEL(DUELIST_MARIK_158)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F039E4, map_60_state_04_08F039E4, 0x08F039FC, 0x08F039F0)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I see... You have learned much from your previous",
      "duels..",
      "{PLAYER}, I believe that you can control Ra."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 64)
  DELAY(16)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I need The Winged Dragon of Ra.")
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
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Awaken! The Winged Dragon of Ra!")
  PLAY_MUSIC(MUSIC_377)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_SPARKLE_RETURNS)
  PLAY_MUSIC(MUSIC_359)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_RA_ENTERS_BATTLE_MODE)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_RA_TRANSFORMS_TO_PHOENIX_MODE)
  PLAY_MUSIC(MUSIC_378)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_PHOENIX_RA_DESCENDS)
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
  TALK(PORTRAIT_NONE, "Received The Winged Dragon of Ra {BYTE_8169}Battle Mode{BYTE_816A}.")
  TEXT("The deck adjustment menu will be opened.")
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F039FC, map_60_state_04_08F039FC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Ra has awakened...")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Yeah! That's it!",
      "The Winged Dragon of Ra is back in all its glory!"
  )
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "...Unfortunately, no.")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Wh-what are you saying, Marik?")
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Have you forgotten?",
      "The Winged Dragon of Ra has one other form.",
      "Its immortal form... The Phoenix Mode."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO,
      "I remember that... That's the scariest mode of them",
      "all."
  )
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Yes. Exactly.")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Then wake that form up!")
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "That... I cannot do now.")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "It's true that I woke up the third form in the past.",
      "However, that was when darkness ruled my heart.",
      "I have no idea how to awaken it now.",
      "There must be a secret..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "But there is nothing to fear.",
      "Ra is immensely powerful even in its present form.",
      "It should be sufficient to help seal the Dark Being.",
      "However, there must be a secret behind the Phoenix",
      "Mode.",
      "You should return if you discover what it is."
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_HAPPY, PORTRAIT_POSITION_AUTO,
      "We'll do that, Marik.",
      "I'm sure Paradox will help us.",
      "He'll tell us where Pegasus's castle is."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Yeah!",
      "Phoenix Mode or not, we can get the job done!",
      "We'll put Reshef down for good!"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_MARIK)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F039F0, map_60_state_04_08F039F0, 0x08F039FC, 0x08F039F0)
  TEXT("The deck adjustment menu will be opened.")
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()
