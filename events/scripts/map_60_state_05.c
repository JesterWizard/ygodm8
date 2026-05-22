#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_60_state_05: map 60 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08F03A8C, map_60_state_05_08F03A8C, 0x08F03AA4, 0x08F03A98)
  LOAD_SPRITE(1, SPRITE_MARIK)
  LOAD_SPRITE(2, SPRITE_ODION)
  PLAY_MUSIC(MUSIC_MARIK_ISHTAR)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, you've finally\n"
      "succeeded.\n\n"
      "You have obtained the secret\n"
      "behind the Phoenix Mode.\n\n"
  )
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Master Marik...\n\n"
  )
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yes, I know, Odion.\n\n"
      "I am going to awaken\n"
      "{PLAYER}'s The Winged\n\n"
      "Dragon of Ra so that he can\n"
      "use the Phoenix Mode.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 64)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'll need to see The Winged\n"
      "Dragon of Ra.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  DELAY(16)
  WALK_OBJECT_Y(1, 48)
  DELAY(16)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Awaken! Phoenix Mode!\n\n"
  )
  PLAY_MUSIC(MUSIC_377)
  COMMAND_7C_ARG(8, 48)
  PLAY_MUSIC(MUSIC_385)
  COMMAND_7C_ARG(8, 46)
  COMMAND_7C_ARG(8, 22)
  PLAY_MUSIC(MUSIC_386)
  COMMAND_7C_ARG(8, 50)
  COMMAND_7C_ARG(8, 51)
  SET_FLAG(EVENT_FLAG_LIGHT_THE_CANDLE_IN_MARIKS_ROOM)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Phoenix! Be calm!\n\n"
      "Your enemy is the one who\n"
      "weakened the Egyptian God\n\n"
      "Cards.\n\n"
      "With {PLAYER}, you must\n"
      "smite that enemy!\n\n"
  )
  PORTRAIT(PORTRAIT_ODION, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What terrifying power...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 64)
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  REMOVE_CARD(240)
  ADD_CARD(412)
  DELAY(16)
  WALK_OBJECT_Y(1, 44)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Received The Winged Dragon\n"
      "of Ra {BYTE_8169}Phoenix Mode{BYTE_816A}!\n\n"
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

EVENT_SCRIPT_REPLACEMENT(0x08F03AA4, map_60_state_05_08F03AA4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Winged Dragon of Ra has\n"
      "fully awakened.\n\n"
      "What you do with its power\n"
      "is up to you, {PLAYER}.\n\n"
  )
  SET_FLAG(EVENT_FLAG_OBTAINED_PHOENIX_MODE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F03A98, map_60_state_05_08F03A98, 0x08F03AA4, 0x08F03A98)
  TEXT
  (
      "The deck adjustment menu\n"
      "will be opened."
  )
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()
