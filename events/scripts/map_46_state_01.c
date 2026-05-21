#include "event_macros.h"
#include "overworld.h"

/* map_46_state_01: map 46 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EDAD34, map_46_state_01_08EDAD34, 0x08EDAD40, 0x08F0404C)
  PORTRAIT(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "Gawry nida! Gawry nida!\n\nWe win all duels! Gawry!\n\n")
  LANGUAGE_TEXT(1, "Grrrr ah !\nGrrrr ah !\n\nNous remportons tous\nles duels ! Aaah !\n\n")
  LANGUAGE_TEXT(2, "Grrrrr!\nGrrrrr!\n\nWir gewinnen alle Duelle!\nGrrr!\n\n")
  LANGUAGE_TEXT(3, "Uaaahhhh!\nUaaahhhh!\n\nVinciamo tutti i\nduelli! Uahhh!\n\n")
  LANGUAGE_TEXT(4, "\xa1Vas a ver!\n\xa1Vas a ver!\n\n\xa1Ganamos todos los duelos!\n\xa1Vas a ver!\n\n")
  END_LANGUAGE_TEXT()
  DUEL(110)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EDAD40, map_46_state_01_08EDAD40, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(17)
  PORTRAIT(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "G-gawry nida... G-ga..\nn-niii.... urrri...\n\n")
  LANGUAGE_TEXT(1, "G-grrrr ahhh...\nG-ga... n-niii... urrri...\n\n")
  LANGUAGE_TEXT(2, "G-grrrrrr...\nG-grr... n-niii... urrri...\n\n")
  LANGUAGE_TEXT(3, "U-uaahhhh...\nU-uah... ahhh...\n\n")
  LANGUAGE_TEXT(4, "V-vas a ver...\nV-va... A aa... V-v-e..\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(282)
  OBJECT_EFFECT(2, 2)
  FALLTHROUGH()
END_EVENT_SCRIPT()
