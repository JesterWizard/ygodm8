#include "event_macros.h"
#include "overworld.h"

/* map_11_state_02: map 11 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E64334, map_11_state_02_08E64334, 0x08E64340, 0x08E6434C)
  CHECK_FLAG(EVENT_FLAG_SCARED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E64340, map_11_state_02_08E64340, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "N-no! I swear, I wasn't\nhiding from you!\n\n")
  LANGUAGE_TEXT(1, "N-non ! Je le jure,\nje ne me cachais pas !\n\n")
  LANGUAGE_TEXT(2, "N-nein! Ich schw\xf6re, ich\nhabe mich nicht vor\n\ndir versteckt!\n\n")
  LANGUAGE_TEXT(3, "N-no! Lo giuro, non\nmi nascondevo da te!\n\n")
  LANGUAGE_TEXT(4, "\xa1N...no! \xa1Lo juro, no me\nescond\xeda de ti!\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(272)
  REACTION(REACTION_ELLIPSIS, 2)
  LANGUAGE_TEXT(0, "Oh... You're not with the\nNeo Ghouls.\n\nDon't scare me like that,\nokay?\n\n")
  LANGUAGE_TEXT(1, "Oh... Tu n'es pas\navec les Neo Ghouls !\n\nPlus question de me faire\npeur comme \xe7a, OK ?\n\n")
  LANGUAGE_TEXT(2, "Oh... Du geh\xf6rst nicht zu\nden Neo Ghouls.\n\nErschreck mich nicht mehr\nso, h\xf6rst du?\n\n")
  LANGUAGE_TEXT(3, "Oh... Non sei uno dei\nNeo Ghouls. Mi hai fatto\n\nprendere un colpo.\nNon farlo pi\xf9, intesi?\n\n")
  LANGUAGE_TEXT(4, "Oh... No est\xe1s con\nlos Neo Ghouls.\n\nNo me asustes m\xe1s\nas\xed, \xbfvale?\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(EVENT_FLAG_SCARED_AMBUSHER)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6434C, map_11_state_02_08E6434C, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "I'm not giving up my rare\ncards to anyone.\n\n")
  LANGUAGE_TEXT(1, "Je ne donnerais mes\ncartes rares \xe0 personne.\n\n")
  LANGUAGE_TEXT(2, "Meine seltenen Karten\nbekommt keiner.\n\n")
  LANGUAGE_TEXT(3, "Io non do le mie\ncarte rare a nessuno.\n\n")
  LANGUAGE_TEXT(4, "No voy a dar mis\ncartas raras a nadie.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
