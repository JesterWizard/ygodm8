#include "event_macros.h"
#include "overworld.h"

/* map_42_state_04: map 42 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08ED9E54, map_42_state_04_08ED9E54, 0x08ED9DC4, 0x08F04040)
  PLAY_MUSIC(403)
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(2, 0, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, 3, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, 0)
  LANGUAGE_TEXT(0, "I didn't realize until now\nthat you've gotten really\n\nstrong, {PLAYER}.\n\n")
  LANGUAGE_TEXT(1, "Je n'avais pas\nremarqu\xe9, mais...\n\nTu es devenu tr\xe8s\nfort, {PLAYER}.\n\n")
  LANGUAGE_TEXT(2, "Es ist mir nie aufge-\nfallen, aber...\n\nDu bist wirklich stark\ngeworden, {PLAYER}.\n\n")
  LANGUAGE_TEXT(3, "Non avevo mai dato\nl'impressione di notarlo,\n\nma... Sei diventato davvero\nforte, {PLAYER}.\n\n")
  LANGUAGE_TEXT(4, "Nunca me di\ncuenta, pero...\n\nTe has vuelto muy\nfuerte, {PLAYER}.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
