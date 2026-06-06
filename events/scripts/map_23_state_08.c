#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_23_state_08: map 23 state 8 */

LOAD_SPRITE(1, SPRITE_MILLENNIUM_GUARDIAN)
LOAD_SPRITE(2, SPRITE_PANIK)
PLAY_MUSIC(SOUND_NONE)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO)
TEXT
(
    "That image I just saw...\n\n"
)
HIDE_PORTRAIT()
DELAY(8)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
DELAY(8)
MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
DELAY(8)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, OBJECT_13)
DELAY(8)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO)
TEXT
(
    "{PLAYER}, you saw it too,\n"
    "didn't you?\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SAD, PORTRAIT_POSITION_AUTO)
TEXT
(
    "Reshef the Dark Being will\n"
    "destroy the world...\n\n"
    "What Ishizu said really was\n"
    "true...\n\n"
)
TEXT
(
    "And... My other self...\n\n"
    "But... Why...\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_272)
REACTION(REACTION_ELLIPSIS, OBJECT_0)
DELAY(16)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
TEXT
(
    "We have to hurry!\n\n"
    "If we don't, there's going\n"
    "to be a world of trouble!\n\n"
    "Let's go back and see Ishizu\n"
    "right away!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
HIDE_PORTRAIT()
HIDE_PORTRAIT()
FADE_MUSIC(2)
DELAY(32)

EVENT_SCRIPT_REPLACEMENT(0x08E952DC, map_23_state_08_08E952DC, 0x08E952E8, 0x08F04040)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I know that it's hard to\n"
      "believe.\n\n"
      "Reshef the Dark Being\n"
      "destroying the world...\n\n"
      "I don't want to believe it\n"
      "either.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E952F4, map_23_state_08_08E952F4, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We have secretly guarded\n"
      "over the Millennium Items.\n\n"
      "Millennium Items are\n"
      "believed to attract each\n\n"
      "other.\n\n"
      "The Millennium Necklace will\n"
      "lead you to the next one.\n\n"
      "Along with the Millennium\n"
      "Items...\n\n"
      "You will face the Millennium\n"
      "Guardians.\n\n"
      "You must overcome the\n"
      "challenges we present.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E95300, map_23_state_08_08E95300, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You are only allowed to duel\n"
      "me once.\n\n"
      "Did you not have to leave\n"
      "immediately?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9530C, map_23_state_08_08E9530C, 0x08F04040, 0x08F04040)
TEXT
  (
      "...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
