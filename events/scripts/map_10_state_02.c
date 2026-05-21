#include "event_macros.h"
#include "overworld.h"

/* map_10_state_02: map 10 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E63254, map_10_state_02_08E63254, 0x08E63260, 0x08E6326C)
  CHECK_FLAG(88)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E63260, map_10_state_02_08E63260, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "S-sorry! I have no more rare\ncards to give you!\n\n")
  LANGUAGE_TEXT(1, "D-d\xe9sol\xe9 ! Je n'ai plus de\ncartes rares \xe0 te donner !\n\n")
  LANGUAGE_TEXT(2, "T-tut mir Leid! Ich habe ke-\nine seltenen Karten mehr!\n\n")
  LANGUAGE_TEXT(3, "Scusa, ma non ho pi\xf9\ncarte rare da darti!\n\n")
  LANGUAGE_TEXT(4, "\xa1L...lo siento! \xa1No\ntengo m\xe1s cartas\n\nraras que darte!\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(272)
  REACTION(3, 2)
  LANGUAGE_TEXT(0, "Huh? You're not the Neo\nGhouls?\n\nDon't scare me like that!\n\nThose thugs shook me down\nand took my rare cards...\n\nI'm so angry...\n\n")
  LANGUAGE_TEXT(1, "Hein ? Vous n'\xeates\npas des Neo Ghouls ?\n\nNe me faites pas\npeur comme \xe7a !\n\nCes voyous m'ont vol\xe9\nmes cartes rares...\n\nCa me tue...\n\n")
  LANGUAGE_TEXT(2, "Was?\nIhr seid keine Neo Ghouls?\n\nMacht mir nicht solche\nAngst!\n\nDiese Halunken zogen mir\nmeine seltenen Karten aus\n\nder Tasche...\nIch bin fuchsteufelswild...\n\n")
  LANGUAGE_TEXT(3, "Come? Non siete\ndei Neo Ghouls?\n\nNon mi spaventare!\n\nQuei mascalzoni mi\nhanno rivoltato come\n\nun calzino e mi hanno\npreso le carte rare...\n\nChe rabbia...\n\n")
  LANGUAGE_TEXT(4, "\xbfEh?\n\xbfNo sois Neo Ghouls?\n\n\xa1No me asust\xe9is as\xed!\n\nEsos matones me atacaron y\ncogieron mis cartas\n\nraras...\n\nMe consume...\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(88)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6326C, map_10_state_02_08E6326C, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "I'm going to practice until\nthe Neo Ghouls can't beat\n\nme!\n\n")
  LANGUAGE_TEXT(1, "Je vais devenir meilleur\nque ces Neo Ghouls !\n\n")
  LANGUAGE_TEXT(2, "Ich werde besser als die\nNeo Ghouls werden!\n\n")
  LANGUAGE_TEXT(3, "Diventer\xf2 pi\xf9\nbravo dei Neo Ghouls!\n\n")
  LANGUAGE_TEXT(4, "\xa1Voy a ser mejor\nque los Neo Ghouls!\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
