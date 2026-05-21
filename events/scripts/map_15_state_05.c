#include "event_macros.h"
#include "overworld.h"

/* map_15_state_05: map 15 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A614, map_15_state_05_08E7A614, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Take this train if you want\nto go to the Egypt\n\nExhibition.\n\n")
  LANGUAGE_TEXT(1, "C'est le train \xe0 destination\nde l'Exposition \xe9gyptienne.\n\n")
  LANGUAGE_TEXT(2, "Dies ist der Zug zur\n\xe4gyptischen Ausstellung.\n\n")
  LANGUAGE_TEXT(3, "Se siete diretti alla Mostra\nEgizia, \xe8 questo il treno.\n\n")
  LANGUAGE_TEXT(4, "Este es el tren que va a la\nExposici\xf3n Egipcia.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A620, map_15_state_05_08E7A620, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "This train will be departing\nshortly.\n\nPlease wait on board.\n\n")
  LANGUAGE_TEXT(1, "Ce train va bient\xf4t\npartir.\n\nEn voiture, s'il vous pla\xeet.\n\n")
  LANGUAGE_TEXT(2, "Der Zug f\xe4hrt in K\xfcrze ab.\nBitte warten Sie im Zug.\n\n")
  LANGUAGE_TEXT(3, "Questo treno parte\ntra poco.\n\nAspettate a bordo.\n\n")
  LANGUAGE_TEXT(4, "El tren saldr\xe1\nen breve.\n\nPor favor, esperad\na bordo.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
