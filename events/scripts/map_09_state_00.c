#include "event_macros.h"

/* map_09_state_00: map 9 state 0 */

EVENT_SCRIPT_REPLACEMENT(0x08E621E4, map_09_state_00_08E621E4, 0x08E621F0, 0x08F04040)
  PLAY_MUSIC(365)
  SPECIAL(0)
  RESTORE_LIFE_POINTS()
  LANGUAGE_TEXT(0, "Your Life Points {BYTE_8169}LP{BYTE_816A} have\nbeen restored.\n\nWould you like to save?\n\n{CARD_1}Yes\nNo{CARD_2}\n\n")
  LANGUAGE_TEXT(1, "Tu as r\xe9cup\xe9r\xe9 tes\npoints de vie {BYTE_8169}LP{BYTE_816A}.\n\nVeux-tu enregistrer ?\n\n{CARD_1}Oui\nNon{CARD_2}\n\n")
  LANGUAGE_TEXT(2, "Ihre Lebenspunkte {BYTE_8169}LP{BYTE_816A}\nwurden wiederhergestellt.\n\nM\xf6chten Sie speichern?\n\n{CARD_1}Ja\nNein{CARD_2}\n\n")
  LANGUAGE_TEXT(3, "I tuoi punti vita {BYTE_8169}LP{BYTE_816A}\nsono stati ripristinati.\n\nVuoi salvare?\n\n{CARD_1}S\xec\nNo{CARD_2}\n\n")
  LANGUAGE_TEXT(4, "Tus puntos de vida {BYTE_8169}LP{BYTE_816A}\nhan sido restaurados.\n\n\xbfDeseas guardar?\n\n{CARD_1}S\xed\nNo{CARD_2}\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E621F0, map_09_state_00_08E621F0, 0x08F04040, 0x08F04040)
  SAVE()
  LANGUAGE_TEXT(0, "Your progress has been\nsaved.\n\n")
  LANGUAGE_TEXT(1, "Ta progression dans la\npartie a \xe9t\xe9 enregistr\xe9e.\n\n")
  LANGUAGE_TEXT(2, "Ihr Spielstand wurde\ngespeichert\n\n")
  LANGUAGE_TEXT(3, "I tuoi progressi sono\nstati salvati.\n\n")
  LANGUAGE_TEXT(4, "Tu progreso\nse ha guardado.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
