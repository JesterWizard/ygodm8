#include "event_macros.h"
#include "overworld.h"

/* map_18_state_02: map 18 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E80AD8, map_18_state_02_08E80AD8, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "A journey by train has its\ncharms.\n\n")
  LANGUAGE_TEXT(1, "C'est vrai que\nvoyager en train,\n\nc'est tr\xe8s agr\xe9able.\n\n")
  LANGUAGE_TEXT(2, "Eine Zugreise hat auch\nihre angenehmen Seiten,\n\ndas muss ich wirklich\nzugeben.\n\n")
  LANGUAGE_TEXT(3, "Devo dire che viaggiare\nin treno pu\xf2 essere\n\naffascinante.\n\n")
  LANGUAGE_TEXT(4, "He de admitir que\nun viaje en tren\n\ntiene sus encantos.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80AE4, map_18_state_02_08E80AE4, 0x08E80AF0, 0x08E80B20)
  CHECK_FLAG(56)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80AF0, map_18_state_02_08E80AF0, 0x08E80AFC, 0x08F0404C)
  LANGUAGE_TEXT(0, "It'll be a nice change of\npace to duel in a place\n\nlike this.\n\n")
  LANGUAGE_TEXT(1, "Se battre en duel ici,\n\xe7a change.\n\n")
  LANGUAGE_TEXT(2, "Sie beschleunigt das Duell-\ntempo ganz hervorragend.\n\n")
  LANGUAGE_TEXT(3, "\xc8 un bel cambiamento di\nritmo duellare qui.\n\n")
  LANGUAGE_TEXT(4, "Es un cambio agradable\nluchar aqu\xed.\n\n")
  END_LANGUAGE_TEXT()
  DUEL(28)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80AFC, map_18_state_02_08E80AFC, 0x08E80B08, 0x08E80B14)
  CHECK_FLAG(244)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80B08, map_18_state_02_08E80B08, 0x08E80B20, 0x08F04040)
  PLAY_MUSIC(232)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80B20, map_18_state_02_08E80B20, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "The shaking of the train has\nmade me carsick.\n\n")
  LANGUAGE_TEXT(1, "Les mouvements du train\nm'ont donn\xe9 la naus\xe9e.\n\n")
  LANGUAGE_TEXT(2, "Das R\xfctteln des Zuges hat\nmich schwindelig gemacht.\n\n")
  LANGUAGE_TEXT(3, "Gli scossoni del treno mi\nhanno dato la nausea.\n\n")
  LANGUAGE_TEXT(4, "El movimiento del\ntren me ha mareado.\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(56)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E80B14, map_18_state_02_08E80B14, 0x08E80B20, 0x08F04040)
  PLAY_MUSIC(236)
  FALLTHROUGH()
END_EVENT_SCRIPT()
