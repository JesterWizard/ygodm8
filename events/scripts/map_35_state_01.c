#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_35_state_01: map 35 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EC62A8, map_35_state_01_08EC62A8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_REX)
  LOAD_SPRITE(2, SPRITE_GIRL_ARCHEOLOGIST)
  LOAD_SPRITE(3, SPRITE_THOUGHTFUL_ARCHEOLOGIST)
  PLAY_MUSIC(MUSIC_263)
  COMMAND_7C_ARG(7, 16)
  DELAY(16)
  PLAY_MUSIC(MUSIC_245)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What... It's an earthquake!\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Is Reshef's resurrection\n"
      "causing the tremors?\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_TEETH_GRITTED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Whatever it is, stay on your\n"
      "toes.\n\n"
      "We better keep moving, guys.\n\n"
  )
  SET_FLAG(EVENT_FLAG_SAW_CAVE_EARTHQUAKE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62CC, map_35_state_01_08EC62CC, 0x08EC62D8, 0x08EC632C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_MILLENNIUM_GUARDIAN5)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62D8, map_35_state_01_08EC62D8, 0x08EC62F0, 0x08EC6320)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_REX)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62F0, map_35_state_01_08EC62F0, 0x08EC62FC, 0x08EC6308)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What are you three\n"
      "chumpasaurs doing here?\n\n"
      "You came all the way out\n"
      "here to see me?\n\n"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_REX_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Millennium Item?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_1)
  DELAY(16)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You came all the way here\n"
      "looking for one of those\n\n"
      "things?\n\n"
      "Well... I could tell you\n"
      "what I know...\n\n"
      "But only if you can beat my\n"
      "Dino Deck!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62FC, map_35_state_01_08EC62FC, 0x08EC6314, 0x08F0404C)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That's the spirit! Let's\n"
      "duel!\n\n"
  )
  DUEL(46)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC6314, map_35_state_01_08EC6314, 0x08EC6320, 0x08F04040)
  PLAY_MUSIC(MUSIC_245)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Graaaah! You win!\n\n"
      "I wanted to learn how to\n"
      "strengthen my deck.\n\n"
      "That's why I came here\n"
      "because there's supposed to\n\n"
      "be some secret in these\n"
      "parts, but I guess I was\n\n"
      "wrong.\n\n"
      "I won't lose next time,\n"
      "though.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_REX)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 9, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 9, 0)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC6320, map_35_state_01_08EC6320, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I don't know if it's what\n"
      "you're looking for...\n\n"
      "But I hear there's something\n"
      "odd in the back of the\n\n"
      "cave.\n\n"
      "Good luck on finding that\n"
      "thing.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC6308, map_35_state_01_08EC6308, 0x08EC62FC, 0x08EC6308)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_REX_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah, I know you have more\n"
      "urgent things to do.\n\n"
      "But I don't care what you\n"
      "think.\n\n"
      "I've got my own reasons for\n"
      "dueling and dealing dino\n\n"
      "demolition.\n\n"
      "Come on, you wanna duel or\n"
      "not!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC632C, map_35_state_01_08EC632C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Heh, looks like you found\n"
      "what you wanted.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62E4, map_35_state_01_08EC62E4, 0x08EC62F0, 0x08EC6338)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_REX)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC6338, map_35_state_01_08EC6338, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'm starting over and\n"
      "rebuilding my deck from\n\n"
      "scratch. Another time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62B4, map_35_state_01_08EC62B4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "That quake was off the\n"
      "Richter scale!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC62C0, map_35_state_01_08EC62C0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "We don't often get quakes\n"
      "around these parts.\n\n"
      "I hope nothing bad is going\n"
      "to happen.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
