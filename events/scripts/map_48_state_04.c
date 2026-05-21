#include "event_macros.h"
#include "overworld.h"

/* map_48_state_04: map 48 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE8E4, map_48_state_04_08EDE8E4, 0x08EDE8F0, 0x08F04040)
  PLAY_MUSIC(17)
  PORTRAIT(PORTRAIT_YUGI, 0, 8)
  LANGUAGE_TEXT(0, "I also have to get the\nspirit of the Puzzle back.\n\nThat's why I have to keep up\nwith your skills, {PLAYER}.\n\n")
  LANGUAGE_TEXT(1, "Je dois retrouver\nmon autre moi.\n\nJe n'ai pas de temps\n\xe0 perdre, {PLAYER}.\n\n")
  LANGUAGE_TEXT(2, "Ich muss mein anderes\nIch zur\xfcckbekommen.\n\nIch darf nicht hinterher-\nhinken, {PLAYER}.\n\n")
  LANGUAGE_TEXT(3, "Devo fare tornare\nl'altro me stesso.\n\nNon posso tirarmi\nindietro, {PLAYER}.\n\n")
  LANGUAGE_TEXT(4, "Tengo que recuperar\na mi otro yo.\n\nNo puedo quedarme\natr\xe1s, {PLAYER}.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
