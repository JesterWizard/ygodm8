#include "event_macros.h"
#include "overworld.h"

/* map_07_state_02: map 7 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E5F894, map_07_state_02_08E5F894, 0x08E5F8A0, 0x08E5F8AC)
  CHECK_FLAG(96)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8A0, map_07_state_02_08E5F8A0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, 0, 8)
  LANGUAGE_TEXT(0, "The whole city is infested\nwith Neo Ghouls.\n\nI heard that Ishizu has been\nabducted, too...\n\n{PLAYER}, hurry, send the\nNeo Ghouls on a one-way\n\nticket out of here!\n\n")
  LANGUAGE_TEXT(1, "Toute la ville regorge\nde Neo Ghouls.\n\nIl para\xeet qu'Ishizu a\nm\xeame aussi \xe9t\xe9 enlev\xe9e.\n\n{PLAYER}, d\xe9barrasse-\nnous vite des Neo Ghouls.\n\n")
  LANGUAGE_TEXT(2, "Die ganze Stadt wimmelt\nvor Neo Ghouls.\n\nWie ich h\xf6rte, wurde auch\nIshizu entf\xfchrt...\n\n{PLAYER}, beeil dich, du\nmusst die Neo Ghouls\n\nvertreiben.\n\n")
  LANGUAGE_TEXT(3, "Tutta la citt\xe0 brulica\ndi Neo Ghouls.\n\nHo anche sentito dire che\nIshizu \xe8 stata rapita...\n\n{PLAYER}, sbrigati a\nscacciare i Neo Ghouls!\n\n")
  LANGUAGE_TEXT(4, "Toda la ciudad est\xe1\nrepleta de Neo Ghouls.\n\nO\xed que Ishizu tambi\xe9n\nfue raptada...\n\n{PLAYER}, r\xe1pido, manda\na los Neo Ghouls a fre\xedr\n\nesp\xe1rragos.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5F8AC, map_07_state_02_08E5F8AC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, 0, 8)
  LANGUAGE_TEXT(0, "The Neo Ghouls seem to have\nleft town.\n\nBut Ishizu is still missing.\n\nWe have to find her, and\nfast!\n\nDon't give up, {PLAYER}.\n\n")
  LANGUAGE_TEXT(1, "On dirait que les Neo Ghouls\nont quitt\xe9 la ville.\n\nMais Ishizu est toujours\nport\xe9e disparue.\n\nNous devons la\ntrouver, et vite.\n\nCe n'est pas le moment\nd'abandonner, {PLAYER}.\n\n")
  LANGUAGE_TEXT(2, "Wie es scheint, haben\ndie Neo Ghouls\n\ndie Stadt verlassen.\nAber wo ist Ishizu?\n\nWir m\xfcssen sie finden,\nund zwar schnell.\n\nGib nicht auf, {PLAYER}.\n\n")
  LANGUAGE_TEXT(3, "Pare che i Neo Ghouls\nabbiano lasciato la citt\xe0.\n\nMa Ishizu non si \xe8\nancora vista.\n\nDobbiamo trovarla,\ne in fretta.\n\nTieni duro, {PLAYER}!\n\n")
  LANGUAGE_TEXT(4, "Parece que los Neo Ghouls\nhan dejado la ciudad.\n\nPero a\xfan falta Ishizu.\n\nTenemos que\nhallarla, y pronto.\n\nNo te rindas, {PLAYER}.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
