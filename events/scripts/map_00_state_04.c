#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_04: map 0 state 4 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08E34A9C, map_00_state_04_08E34A9C, 0x08E34AB4, 0x08E34AFC)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_KEY_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AB4, map_00_state_04_08E34AB4, 0x08E34AC0, EVENT_NOP)
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
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You have obtained the Millennium Key.",
      "With the power of two Millennium Items..."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AC0, map_00_state_04_08E34AC0, 0x08E34ACC, EVENT_NOP)
  PLAY_MUSIC(MUSIC_290)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_SLIFER_REVIVAL)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34ACC, map_00_state_04_08E34ACC, 0x08E34AD8, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Slifer the Sky Dragon has regained its power!",
      "Egyptian God Cards choose their bearers.",
      "This card... chooses you, Yugi."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_13)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Ishizu... Slifer the Sky Dragon...",
      "I can't use it."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "That card belongs to my other self.",
      "It doesn't belong to me."
  )
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "But... After all the trouble you undergone to attain it,",
      "you will forfeit the resurrected Egyptian God",
      "Card?"
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I think {PLAYER} should hold on to that card.")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER} also saw the Millennium Necklace's",
      "vision.",
      "I know he can control the power of the Egyptian God",
      "Cards. I'm absolutely sure of it!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "{PLAYER}, don't be shy! Take it! I'd be leapin' outta my",
      "skin to get a card like dat!",
      "Besides, Slifer the Sky Dragon proves that the",
      "power of our friendship can defeat anybody!"
  )
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I understand... Since you all agree...",
      "{PLAYER}, I will entrust you with this card."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  DELAY(16)
  TEXT("Received Slifer the Sky Dragon!")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Yeah! Awesome!",
      "We have the first Egyptian God Card!"
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Still... It seems that in order to restore a single",
      "Egyptian God Card...",
      "We need the magical powers of two Millennium Items,",
      "{PLAYER}."
  )
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You are correct.",
      "In order to resurrect all three Egyptian God Cards...",
      "You must gather the other Millennium Items. And",
      "quickly!"
  )
  ADD_CARD(238)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AD8, map_00_state_04_08E34AD8, 0x08E34AF0, 0x08E34AE4)
  TALK(PORTRAIT_NONE, "{CARD_1}Okay\nI don't get it{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AF0, map_00_state_04_08E34AF0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The next Millennium Item...",
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
  TEXT(
      "Among the Catacombs...",
      "Catacombs are underground cemeteries.",
      "A Millennium Item is certain to be hidden there."
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_KEY_TO_ISHIZU)
  SET_FLAG(EVENT_FLAG_UNLOCKED_ITALY)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AE4, map_00_state_04_08E34AE4, 0x08E34AD8, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "To resurrect a single Egyptian God Card...",
      "We need the power from two Millennium Items.",
      "In order to resurrect all three Egyptian God Cards...",
      "You must gather the other Millennium Items, and we do",
      "not have much time!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AFC, map_00_state_04_08E34AFC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Sol Chevalsky resurrected the Dark Being...",
      "We must have the Egyptian God Cards in order to stop",
      "the terror.",
      "Therefore, we must restore the Egyptian God Cards from",
      "stone.",
      "But in order to do so, we need the Millennium Items.",
      "The third Millennium Item is in the Catacombs of Italy.",
      "Please find it in the communal cemetery."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34AA8, map_00_state_04_08E34AA8, 0x08E34AB4, 0x08E34B08)
  CHECK_FLAG(EVENT_FLAG_BROUGHT_MILLENNIUM_KEY_TO_ISHIZU)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34B08, map_00_state_04_08E34B08, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Please hurry to the Catacombs of Italy.",
      "Reshef the Dark Being will soon engulf the world in",
      "darkness."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
