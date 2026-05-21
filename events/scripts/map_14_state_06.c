#include "event_macros.h"
#include "overworld.h"

/* map_14_state_06: map 14 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E774C8, map_14_state_06_08E774C8, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "The next stop is the Egypt\nExhibition.\n\n")
  LANGUAGE_TEXT(1, "Prochain arr\xeat :\nl'Exposition \xe9gyptienne.\n\n")
  LANGUAGE_TEXT(2, "Der n\xe4chste Halt ist die\n\xe4gyptische Ausstellung.\n\n")
  LANGUAGE_TEXT(3, "La prossima fermata \xe8\nla Mostra Egizia.\n\n")
  LANGUAGE_TEXT(4, "La pr\xf3xima parada es la\nExposici\xf3n Egipcia.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E774D4, map_14_state_06_08E774D4, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Sorry, I'm working.\n\n")
  LANGUAGE_TEXT(1, "D\xe9sol\xe9, je travaille.\n\n")
  LANGUAGE_TEXT(2, "Tut mir Leid, ich arbeite.\n\n")
  LANGUAGE_TEXT(3, "Spiacente, sto lavorando.\n\n")
  LANGUAGE_TEXT(4, "Lo siento, estoy\ntrabajando.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
