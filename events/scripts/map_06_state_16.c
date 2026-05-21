#include "event_macros.h"
#include "overworld.h"

/* map_06_state_16: map 6 state 16 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CDF8, map_06_state_16_08E5CDF8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TRISTAN, 0, 8)
  LANGUAGE_TEXT(0, "Have fun with Serenity.\n\n")
  LANGUAGE_TEXT(1, "Amuse-toi bien\navec Serenity.\n\n")
  LANGUAGE_TEXT(2, "Viel Spa\xdf mit Serenity.\n\n")
  LANGUAGE_TEXT(3, "Divertiti con Serenity.\n\n")
  LANGUAGE_TEXT(4, "Que te lo pases bien\ncon Serenity.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CE04, map_06_state_16_08E5CE04, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DUKE, 0, 8)
  LANGUAGE_TEXT(0, "Huh? Aren't you supposed to\nbe with Serenity?\n\nYou have to catch the\nKaibaman show.\n\n")
  LANGUAGE_TEXT(1, "Mmm ? Tu n'es pas cens\xe9\n\xeatre avec Serenity ?\n\nTu dois regarder avec elle\nle spectacle Kaibaman.\n\n")
  LANGUAGE_TEXT(2, "Hm? Solltest du nicht bei\nSerenity sein? Du wolltest\n\ndir doch die Kaibaman\nShow mit ihr ansehen.\n\n")
  LANGUAGE_TEXT(3, "Eh? Ma non devi\nstare con Serenity?\n\nDevi raggiungerla\nal Kaibaman Show.\n\n")
  LANGUAGE_TEXT(4, "\xbfHuh? \xbfNo se supone\nque deber\xedas estar con\n\nSerenity? Tienes que ver el\nshow de Kaibaman con ella.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
