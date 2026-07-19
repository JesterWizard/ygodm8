#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_23_state_08: map 23 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E952C4, map_23_state_08_08E952C4, 0x08E952D0, 0x08E952DC)
  LOAD_SPRITE(1, SPRITE_MILLENNIUM_GUARDIAN)
  LOAD_SPRITE(2, SPRITE_PANIK)
  PLAY_MUSIC(SOUND_NONE)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO, "That image I just saw...")
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
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO, "{PLAYER}, you saw it too, didn't you?")
  TALK(PORTRAIT_NONE, "{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E952D0, map_23_state_08_08E952D0, 0x08E952E8, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SAD, PORTRAIT_POSITION_AUTO,
      "Reshef the Dark Being will destroy the world...",
      "What Ishizu said really was true..."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E952E8, map_23_state_08_08E952E8, 0x08F04250, EVENT_NOP)
  TEXT(
      "And... My other self...",
      "But... Why..."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "We have to hurry!",
      "If we don't, there's going to be a world of trouble!",
      "Let's go back and see Ishizu right away!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F04250, map_23_state_08_08F04250, EVENT_NOP, EVENT_NOP)
  HIDE_PORTRAIT()
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E952DC, map_23_state_08_08E952DC, 0x08E952E8, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SAD, PORTRAIT_POSITION_AUTO,
      "I know that it's hard to believe.",
      "Reshef the Dark Being destroying the world...",
      "I don't want to believe it either."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E952F4, map_23_state_08_08E952F4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "We have secretly guarded over the Millennium Items.",
      "Millennium Items are believed to attract each",
      "other.",
      "The Millennium Necklace will lead you to the next one.",
      "Along with the Millennium Items...",
      "You will face the Millennium Guardians.",
      "You must overcome the challenges we present."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E95300, map_23_state_08_08E95300, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MILLENIUM_GUADIAN, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You are only allowed to duel me once.",
      "Did you not have to leave immediately?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9530C, map_23_state_08_08E9530C, EVENT_NOP, EVENT_NOP)
  TEXT("...")
  FALLTHROUGH()
END_EVENT_SCRIPT()
