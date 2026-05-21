#include "event_macros.h"
#include "overworld.h"

/* map_49_state_01: map 49 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EDEBF0, map_49_state_01_08EDEBF0, 0x08F04040, 0x08F04040)
  SET_FLAG(EVENT_FLAG_UNLOCKED_PEGASUS_CASTLE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EDEBD8, map_49_state_01_08EDEBD8, 0x08EDEBE4, 0x08F0404C)
  PORTRAIT(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Gawry nida! Gawry nida!\n\nYou'll go no further! Gawry!\n\n")
  LANGUAGE_TEXT(1, "Grrr ah !\nGrrr ah !\n\nVous n'irez pas\nplus loin ! Grr !\n\n")
  LANGUAGE_TEXT(2, "Grrrrr!\nGrrrrr!\n\nKeinen Schritt weiter!\nGrrrrr!\n\n")
  LANGUAGE_TEXT(3, "Uaaaahhh!\nUaaaahhh!\n\nNon andrete oltre!\nUahh!\n\n")
  LANGUAGE_TEXT(4, "\xa1Vas a ver!\n\xa1Vas a ver!\n\n\xa1No ir\xe9is m\xe1s lejos!\n\xa1Vas a ver!\n\n")
  END_LANGUAGE_TEXT()
  DUEL(112)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EDEBE4, map_49_state_01_08EDEBE4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(17)
  PORTRAIT(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "G-gawry n-nida...\nM-master... G-gaah...\n\n")
  LANGUAGE_TEXT(1, "G-grr ah...\nM-ma\xeetre... G-grrr...\n\n")
  LANGUAGE_TEXT(2, "G-grrrr...\nM-Meister... G-gaah...\n\n")
  LANGUAGE_TEXT(3, "U-uuuuahhh...\nM-maestro... U-ahhh...\n\n")
  LANGUAGE_TEXT(4, "V-va-a v-vee...\nA-amo... G-gaah...\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(282)
  OBJECT_EFFECT(2, 2)
  FALLTHROUGH()
END_EVENT_SCRIPT()
