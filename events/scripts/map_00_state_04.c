#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_04: map 0 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E34A9C, map_00_state_04_08E34A9C, 0x08E34AB4, 0x08E34AFC)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_KEY_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AB4, map_00_state_04_08E34AB4, 0x08E34AC0, 0x08F04040)
  WALK_OBJECT_Y(0, 32)
  WALK_OBJECT_X(0, 48)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 42)
  WALK_OBJECT_X(13, 54)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 42)
  WALK_OBJECT_X(14, 42)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  COMMAND_7C_ARG(2, 2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You have obtained the\n"
      "Millennium Key.\n\n"
      "With the power of two\n"
      "Millennium Items...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AC0, map_00_state_04_08E34AC0, 0x08E34ACC, 0x08F04040)
  PLAY_MUSIC(MUSIC_290)
  COMMAND_7C_ARG(8, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34ACC, map_00_state_04_08E34ACC, 0x08E34AD8, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Slifer the Sky Dragon has\n"
      "regained its power!\n\n"
      "Egyptian God Cards choose\n"
      "their bearers.\n\n"
      "This card... chooses you,\n"
      "Yugi.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_13)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ishizu... Slifer the Sky\n"
      "Dragon...\n\n"
      "I can't use it.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That card belongs to my\n"
      "other self.\n\n"
      "It doesn't belong to me.\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But... After all the trouble\n"
      "you undergone to attain it,\n\n"
      "you will forfeit the\n"
      "resurrected Egyptian God\n\n"
      "Card?\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I think {PLAYER} should\n"
      "hold on to that card.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER} also saw the\n"
      "Millennium Necklace's\n\n"
      "vision.\n\n"
      "I know he can control the\n"
      "power of the Egyptian God\n\n"
      "Cards. I'm absolutely sure\n"
      "of it!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, don't be shy! Take\n"
      "it! I'd be leapin' outta my\n\n"
      "skin to get a card like dat!\n\n"
      "Besides, Slifer the Sky\n"
      "Dragon proves that the\n\n"
      "power of our friendship can\n"
      "defeat anybody!\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I understand... Since you\n"
      "all agree...\n\n"
      "{PLAYER}, I will entrust you\n"
      "with this card.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  DELAY(16)
  TEXT
  (
      "Received Slifer the Sky\n"
      "Dragon!\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yeah! Awesome!\n\n"
      "We have the first Egyptian\n"
      "God Card!\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Still... It seems that in\n"
      "order to restore a single\n\n"
      "Egyptian God Card...\n\n"
      "We need the magical powers\n"
      "of two Millennium Items,\n\n"
      "{PLAYER}.\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You are correct.\n\n"
      "In order to resurrect all\n"
      "three Egyptian God Cards...\n\n"
      "You must gather the other\n"
      "Millennium Items. And\n\n"
      "quickly!\n\n"
  )
  ADD_CARD(238)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AD8, map_00_state_04_08E34AD8, 0x08E34AF0, 0x08E34AE4)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Okay\n"
      "I don't get it{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AF0, map_00_state_04_08E34AF0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The next Millennium Item...\n\n"
      "Is in Italy."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      ". "
  )
  DELAY(43)
  TEXT
  (
      "Among the\n"
      "Catacombs...\n\n"
      "Catacombs are underground\n"
      "cemeteries.\n\n"
      "A Millennium Item is certain\n"
      "to be hidden there.\n\n"
  )
  HIDE_PORTRAIT()
  COMMAND_7C_ARG(2, 2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_KEY_TO_ISHIZU)
  SET_FLAG(EVENT_FLAG_UNLOCKED_ITALY)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AE4, map_00_state_04_08E34AE4, 0x08E34AD8, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "To resurrect a single\n"
      "Egyptian God Card...\n\n"
      "We need the power from two\n"
      "Millennium Items.\n\n"
      "In order to resurrect all\n"
      "three Egyptian God Cards...\n\n"
      "You must gather the other\n"
      "Millennium Items, and we do\n\n"
      "not have much time!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AFC, map_00_state_04_08E34AFC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Sol Chevalsky resurrected\n"
      "the Dark Being...\n\n"
      "We must have the Egyptian\n"
      "God Cards in order to stop\n\n"
      "the terror.\n\n"
      "Therefore, we must restore\n"
      "the Egyptian God Cards from\n\n"
      "stone.\n\n"
      "But in order to do so, we\n"
      "need the Millennium Items.\n\n"
      "The third Millennium Item is\n"
      "in the Catacombs of Italy.\n\n"
      "Please find it in the\n"
      "communal cemetery.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AA8, map_00_state_04_08E34AA8, 0x08E34AB4, 0x08E34B08)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_KEY_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B08, map_00_state_04_08E34B08, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Please hurry to the\n"
      "Catacombs of Italy.\n\n"
      "Reshef the Dark Being will\n"
      "soon engulf the world in\n\n"
      "darkness.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
