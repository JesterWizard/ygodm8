#include "event_macros.h"
#include "overworld.h"

/* map_48_state_05: map 48 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE980, map_48_state_05_08EDE980, 0x08EDE98C, 0x08F04040)
  PLAY_MUSIC(400)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "That's why I can't waste any\ntime.\n\nI won't be stopped!\n\n")
  LANGUAGE_TEXT(1, "Oui... Je n'ai pas\nde temps \xe0 perdre.\n\nJe ne peux pas rester\nici trop longtemps.\n\n")
  LANGUAGE_TEXT(2, "Ja...\n\nIch darf meine Zeit nicht\nvergeuden.\n\nIch darf mich nicht\naufhalten lassen.\n\n")
  LANGUAGE_TEXT(3, "S\xec...\nNon posso perdere tempo.\n\nNon posso trattenermi qui.\n\n\n")
  LANGUAGE_TEXT(4, "S\xed... No puede ser una\np\xe9rdida de tiempo.\n\nNo me puedo quedar aqu\xed.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
