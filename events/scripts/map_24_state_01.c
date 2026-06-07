#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_24_state_01: map 24 state 1 */

LOAD_SPRITE(1, SPRITE_TAKESHI)
LOAD_SPRITE(2, SPRITE_ETSUKO)
PLAY_MUSIC(MUSIC_239)
DELAY(16)
MOVE_OBJECT(SPRITE_ETSUKO, DIRECTION_LEFT, 0, 0)
DELAY(16)
TEXT
(
    "Takeshi, is it really okay\n"
    "to be onboard this luxury\n\n"
    "liner?\n\n"
    "It looks, like, really\n"
    "expensive.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(SPRITE_TAKESHI, DIRECTION_RIGHT, 0, 0)
DELAY(16)
TEXT
(
    "Don't you worry about a\n"
    "thing, babe.\n\n"
    "All I have to do is win some\n"
    "duels. Piece of cake!\n\n"
    "Really? Takeshi, you're so\n"
    "smart!\n\n"
    "Aww, shucks. C'mon, I'm not\n"
    "that smart."
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
TEXT
(
    "Okay, I admit\n\n"
    "it! I am smart! My cranium's\n"
    "bursting with brains!\n\n"
)
PLAY_MUSIC(MUSIC_272)
REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
DELAY(32)
MOVE_OBJECT(SPRITE_TAKESHI, DIRECTION_UP, 0, 0)
MOVE_OBJECT(SPRITE_ETSUKO, DIRECTION_UP, 0, 0)
SET_FLAG(EVENT_FLAG_SAW_TAKESHI_BRAG)

EVENT_SCRIPT_REPLACEMENT(0x08E981BC, map_24_state_01_08E981BC, 0x08E98174, 0x08E981A4)
CHECK_FLAG(EVENT_FLAG_DEFEATED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98174, map_24_state_01_08E98174, 0x08E98180, 0x08E9818C)
TEXT
  (
      "Huh? You want to duel\n"
      "against me?\n\n"
  )
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98180, map_24_state_01_08E98180, 0x08E98198, 0x08F0404C)
TEXT
  (
      "F-fine! Watch me, Etsuko!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  DUEL(DUELIST_ID_031)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98198, map_24_state_01_08E98198, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_239)
  TEXT
  (
      "Takeshi, are you okay?\n\n"
      "He dueled you, like, totally\n"
      "seriously! That is, like,\n\n"
      "so not cool!\n\n"
      "Takeshi, let's ditch these\n"
      "jerks!\n\n"
      "Uh... Yeah.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  SET_FLAG(EVENT_FLAG_DEFEATED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9818C, map_24_state_01_08E9818C, 0x08F04040, 0x08F04040)
MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TEXT
  (
      "He chickened out because\n"
      "he's scared of you,\n\n"
      "Takeshi!\n\n"
      "You're soooo awesome,\n"
      "Takeshi!\n\n"
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

EVENT_SCRIPT_REPLACEMENT(0x08E981A4, map_24_state_01_08E981A4, 0x08F04040, 0x08F04040)
TEXT
  (
      "Hey, we told you to take a\n"
      "hike, creep.\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981C8, map_24_state_01_08E981C8, 0x08E98174, 0x08E981B0)
CHECK_FLAG(EVENT_FLAG_DEFEATED_TAKESHI)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E981B0, map_24_state_01_08E981B0, 0x08F04040, 0x08F04040)
TEXT
  (
      "What's your problem! I'm not\n"
      "playing you again.\n\n"
  )
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9815C, map_24_state_01_08E9815C, 0x08F04040, 0x08F04040)
TEXT
  (
      "Don't bug us! Go away,\n"
      "creep!\n\n"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98168, map_24_state_01_08E98168, 0x08F04040, 0x08F04040)
TEXT
  (
      "What's your problem?\n\n"
      "You are, like, so uncool!\n\n"
  )
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
