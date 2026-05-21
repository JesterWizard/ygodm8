#include "event_macros.h"

/* map_14_state_03: map 14 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E77414, map_14_state_03_08E77414, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "First class costs too much.\nAn economy seat will do.\n\n")
  LANGUAGE_TEXT(1, "Un ticket en {BYTE_8250}\xe8re\nclasse, c'est trop cher.\n\nIl suffit de r\xe9server\nson si\xe8ge.\n\n")
  LANGUAGE_TEXT(2, "Erster Klasse ist zu teuer.\nEin reservierter Platz\n\nreicht mir.\n\n")
  LANGUAGE_TEXT(3, "La prima classe costa\ntroppo. Andr\xe0 bene un\n\nposto riservato.\n\n")
  LANGUAGE_TEXT(4, "La primera clase\nes muy cara.\n\nUn sitio reservado\nvaldr\xe1.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77420, map_14_state_03_08E77420, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "This is where they punch\nyour ticket.\n\nGo shuffle your deck\nsomewhere else.\n\n")
  LANGUAGE_TEXT(1, "C'est l\xe0 o\xf9 ils\npoin\xe7onnent les tickets.\n\nVa jouer ailleurs.\n\n")
  LANGUAGE_TEXT(2, "Hier wird deine Fahrkarte\nabgestempelt.\n\nHeb dein Deck woanders\nab.\n\n")
  LANGUAGE_TEXT(3, "Qui forano i\nbiglietti.\n\nVai a tagliare il deck\nda qualche altra parte.\n\n")
  LANGUAGE_TEXT(4, "Aqu\xed es cuando te\nagujerean el billete.\n\nVete a cortar tu deck\na otro lugar.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
