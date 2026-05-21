#include "event_macros.h"
#include "overworld.h"

/* map_24_state_05: map 24 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E9821C, map_24_state_05_08E9821C, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "It's so awesome that the Neo\nGhouls are gone.\n\n")
  END_LANGUAGE_TEXT()
  MOVE_OBJECT(1, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98228, map_24_state_05_08E98228, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Get lost! Stop making fun of\nme!\n\nHow am I supposed to duel\nwithout any cards?\n\nThe Neo Ghouls stole every\none of my cards!\n\n")
  END_LANGUAGE_TEXT()
  MOVE_OBJECT(1, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98234, map_24_state_05_08E98234, 0x08F04040, 0x08F04040)
  DELAY(16)
  MOVE_OBJECT(2, 1, 0, 0)
  LANGUAGE_TEXT(0, "Takeshi, like, I don't care\nif you can't duel. I love\n\nyou!\n\n")
  END_LANGUAGE_TEXT()
  MOVE_OBJECT(2, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E98240, map_24_state_05_08E98240, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "What are you, like some kind\nof dueling fanatic?\n\nYou're, like, totally\nbugging me! Go away.\n\n")
  END_LANGUAGE_TEXT()
  MOVE_OBJECT(2, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
