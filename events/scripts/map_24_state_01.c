#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_24_state_01: map 24 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E98144, map_24_state_01_08E98144, 0x08E98150, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_TAKESHI)
  LOAD_SPRITE(2, SPRITE_ETSUKO)
  PLAY_MUSIC(MUSIC_239)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT(
      "Takeshi, is it really okay to be onboard this luxury",
      "liner?",
      "It looks, like, really expensive."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TEXT(
      "Don't you worry about a thing, babe.",
      "All I have to do is win some duels. Piece of cake!",
      "Really? Takeshi, you're so smart!",
      "Aww, shucks. C'mon, I'm not that smart."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT
  (
      "."
  )
  DELAY(43)
  TEXT(
      "Okay, I admit",
      "it! I am smart! My cranium's bursting with brains!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98150, map_24_state_01_08E98150, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  SET_FLAG(EVENT_FLAG_SAW_TAKESHI_BRAG)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981BC, map_24_state_01_08E981BC, 0x08E98174, 0x08E981A4)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98174, map_24_state_01_08E98174, 0x08E98180, 0x08E9818C)
  TEXT("Huh? You want to duel against me?")
  TEXT("{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98180, map_24_state_01_08E98180, 0x08E98198, 0x08F0404C)
  TEXT("F-fine! Watch me, Etsuko!")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  DUEL(DUELIST_ID_031)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98198, map_24_state_01_08E98198, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_239)
  TEXT(
      "Takeshi, are you okay?",
      "He dueled you, like, totally seriously! That is, like,",
      "so not cool!",
      "Takeshi, let's ditch these jerks!",
      "Uh... Yeah."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  SET_FLAG(EVENT_FLAG_DEFEATED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9818C, map_24_state_01_08E9818C, EVENT_NOP, EVENT_NOP)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT(
      "He chickened out because he's scared of you,",
      "Takeshi!",
      "You're soooo awesome, Takeshi!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981A4, map_24_state_01_08E981A4, EVENT_NOP, EVENT_NOP)
  TEXT("Hey, we told you to take a hike, creep.")
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981C8, map_24_state_01_08E981C8, 0x08E98174, 0x08E981B0)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981B0, map_24_state_01_08E981B0, EVENT_NOP, EVENT_NOP)
  TEXT("What's your problem! I'm not playing you again.")
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9815C, map_24_state_01_08E9815C, EVENT_NOP, EVENT_NOP)
  TEXT("Don't bug us! Go away, creep!")
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98168, map_24_state_01_08E98168, EVENT_NOP, EVENT_NOP)
  TEXT(
      "What's your problem?",
      "You are, like, so uncool!"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
