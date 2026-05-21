#include "event_macros.h"
#include "overworld.h"

/* map_17_state_03: map 17 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E7F148, map_17_state_03_08E7F148, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "I should've taken first\nclass...\n\n")
  LANGUAGE_TEXT(1, "J'aurais d\xfb prendre un\nticket en {BYTE_8250}\xe8re classe.\n\n")
  LANGUAGE_TEXT(2, "Ich h\xe4tte Erster Klasse\nfahren sollen...\n\n")
  LANGUAGE_TEXT(3, "Avrei dovuto prendere la\nprima classe...\n\n")
  LANGUAGE_TEXT(4, "Deber\xeda haber tomado\nprimera clase...\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7F154, map_17_state_03_08E7F154, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "This is the train's deck!\n\nDon't confuse it with a duel\ndeck!\n\n")
  LANGUAGE_TEXT(1, "C'est le Deck du train !\n\nA ne pas confondre avec\nles Decks de duel !\n\n")
  LANGUAGE_TEXT(2, "Das ist das Zugdeck!\n\nVerwechsle es nicht mit\neinem Duelldeck!\n\n")
  LANGUAGE_TEXT(3, "Questo \xe8 il deck\ndel treno!\n\nNon confonderlo con\nquello del duello!\n\n")
  LANGUAGE_TEXT(4, "\xa1\xc9ste es el deck del tren!\n\n\xa1No lo confundas con\nun deck de duelo!\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
