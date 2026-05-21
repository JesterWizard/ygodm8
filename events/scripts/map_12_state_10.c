#include "event_macros.h"
#include "overworld.h"

/* map_12_state_10: map 12 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F0F0, map_12_state_10_08E6F0F0, 0x08E6F0FC, 0x08E6F108)
  CHECK_FLAG(133)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F0FC, map_12_state_10_08E6F0FC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Master Mokuba was abducted?\n\nThe last thing I know was\nthat he left to tell Master\n\nSeto...\n\nThat the Neo Ghouls had been\ndriven out of the Town of\n\nDomino...\n\nI've failed as a security\nguard...\n\nYou must save Master Mokuba.\n\nPlease help Master Seto\nrescue him.\n\n")
  LANGUAGE_TEXT(1, "Ma\xeetre Mokuba a \xe9t\xe9 enlev\xe9 ?\n\nIl \xe9tait all\xe9 avertir\nma\xeetre Seto...\n\nque les Neo Ghouls avaient\n\xe9t\xe9 chass\xe9s de Domino...\n\nJe n'ai pas reconnu\nle danger...\n\nS'il te pla\xeet, il faut\naider ma\xeetre Mokuba.\n\nVa aider ma\xeetre Seto \xe0\nlui venir \xe0 la rescousse.\n\n")
  LANGUAGE_TEXT(2, "Meister Mokuba wurde\nentf\xfchrt?\n\nEr wollte Meister Seto\nberichten...\n\nDass die Neo Ghouls aus Do-\nmino vertrieben wurden...\n\nIch verkannte die Gefahr...\nBitte, hilf Meister Mokuba.\n\nBitte hilf Meister Seto, ihn\nzu retten.\n\n")
  LANGUAGE_TEXT(3, "Il maestro Mokuba \xe8\nstato rapito?\n\nSar\xe0 andato a dire al\nmaestro Seto che i\n\nNeo Ghouls sono stati\ncacciati da Domino...\n\nHo fallito: non ho rico-\nnosciuto il pericolo...\n\nTi prego, devi aiutare il\nmaestro Mokuba.\n\nVai ad aiutare il maestro\nSeto a salvarlo.\n\n")
  LANGUAGE_TEXT(4, "\xbfHan raptado al amo Mokuba?\n\nSe fue a decirle al amo\nSeto...\n\nQue se hab\xeda expulsado a los\nNeo Ghouls de Domino...\n\nNo supe darme cuenta\ndel peligro...\n\nPor favor, tienes que\nayudar al amo Mokuba.\n\nPor favor, ve y ayuda al amo\nSeto a rescatarle.\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(133)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F108, map_12_state_10_08E6F108, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "You must save Master Mokuba.\n\nPlease help Master Seto\nrescue him.\n\n")
  LANGUAGE_TEXT(1, "S'il te pla\xeet, tu dois aider\nma\xeetre Mokuba.\n\nVa aider ma\xeetre Seto pour\nvenir \xe0 sa rescousse.\n\n")
  LANGUAGE_TEXT(2, "Bitte, du musst Meister\nMokuba helfen.\n\nBitte hilf Meister Seto bei\nder Befreiungsaktion.\n\n")
  LANGUAGE_TEXT(3, "Ti prego, devi aiutare il\nmaestro Mokuba.\n\nVai ad aiutare il maestro\nSeto a salvarlo.\n\n")
  LANGUAGE_TEXT(4, "Por favor, tienes que\nayudar al amo Mokuba.\n\nPor favor, ve y ayuda al\namo Seto a rescatarle.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
