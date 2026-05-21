#include "event_macros.h"

/* map_20_state_01: map 20 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E84F30, map_20_state_01_08E84F30, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "A big guy took off running\nup the stairs.\n\n")
  LANGUAGE_TEXT(1, "Un gros type est parti en\ncourant dans les escaliers.\n\n")
  LANGUAGE_TEXT(2, "Ein H\xfcne rannte die Treppe\nhoch.\n\n")
  LANGUAGE_TEXT(3, "Un tizio alto \xe8 scappato di\ncorsa sulle scale.\n\n")
  LANGUAGE_TEXT(4, "Un tipo grande sali\xf3\ncorriendo escaleras arriba.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F3C, map_20_state_01_08E84F3C, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "This is where I lost. I have\nno more ante cards.\n\n")
  LANGUAGE_TEXT(1, "Voil\xe0, j'ai perdu. Je n'ai\nplus de Cartes Ante.\n\n")
  LANGUAGE_TEXT(2, "Das ist mein Untergang. Ich\nhabe keine Ante-Karten\n\nmehr.\n\n")
  LANGUAGE_TEXT(3, "\xc8 qui che ho perso. Non\nho pi\xf9 Ante-carte.\n\n")
  LANGUAGE_TEXT(4, "Aqu\xed es donde perd\xed.\nNo tengo m\xe1s Cartas Ante.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
