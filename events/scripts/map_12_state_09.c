#include "event_macros.h"

/* map_12_state_09: map 12 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F114, map_12_state_09_08E6F114, 0x08E6F120, 0x08E6F12C)
  CHECK_FLAG(145)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F120, map_12_state_09_08E6F120, 0x08F04040, 0x08F04040)
  PORTRAIT(10, 0, 8)
  LANGUAGE_TEXT(0, "My big brother turned\nTristan into a monkey?\n\nThat is the nuttiest thing I\never heard!\n\nWhy would Seto do that!\n\n...But that reminds me...\n\nWe made monkey robots, but\nthey never sold well.\n\nI think we donated them to\nsome island.\n\n")
  LANGUAGE_TEXT(1, "Mon grand fr\xe8re\n\naurait transform\xe9\nTristan en singe ?\n\nQuoi, tu d\xe9lires ?\n\nMon grand fr\xe8re\nne ferait jamais \xe7a.\n\nMais par contre, nous avons\nfabriqu\xe9 des robots singes,\n\nmais ils se vendaient mal\nalors, si je me souviens\n\nbien, nous en avons\nfait don \xe0 une \xeele,\n\nje ne sais plus laquelle.\n\n")
  LANGUAGE_TEXT(2, "Mein gro\xdfer Bruder hat\nTristan in einen Affen\n\nverwandelt? Spinnst du?\n\nMein Bruder w\xfcrde so etwas\nnat\xfcrlich nie tun.\n\n... Aber warte...\nWir fertigten die\n\nAffenroboter, doch sie\nverkauften sich nicht gut.\n\nDaher schenkten wir sie\nirgendeiner Insel.\n\n")
  LANGUAGE_TEXT(3, "Mio fratello ha trasformato\nTristan in una scimmia?\n\nSei pazzo per caso?\n\nMio fratello non farebbe\nmai una cosa simile.\n\n... Ma c'\xe8 una cosa...\nAbbiamo fabbricato scimmie\n\nrobot, ma non hanno mai\navuto un gran successo.\n\nPenso che le abbiamo\ndonate a qualche isola.\n\n")
  LANGUAGE_TEXT(4, "\xbfMi gran hermano convirti\xf3\na Tristan en un mono?\n\nPero, \xbfest\xe1s loco?\n\nPues claro que mi gran\nhermano no har\xeda eso.\n\n... Pero hay algo...\n\nHicimos los robots\nmono pero nunca\n\nse vendieron bien.\n\nCreo que los donamos\na una isla.\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(145)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F12C, map_12_state_09_08E6F12C, 0x08F04040, 0x08F04040)
  PORTRAIT(10, 0, 8)
  LANGUAGE_TEXT(0, "We programmed the monkey\nrobots to behave like real\n\nmonkeys.\n\nSo if you show one a banana,\nit becomes excited.\n\n")
  LANGUAGE_TEXT(1, "Les robots singes\nsont programm\xe9s\n\npour se comporter\ncomme des singes.\n\nSi tu leur montres\nune banane,\n\nils seront tout excit\xe9s.\n\n")
  LANGUAGE_TEXT(2, "Affenroboter sind so pro-\ngrammiert, dass sie sich\n\nwie echte Affen verhalten.\n\nWenn du ihm eine Banane\nzeigst, freut er sich sehr.\n\n")
  LANGUAGE_TEXT(3, "Le scimmie robot sono\nprogrammate per\n\ncomportarsi come quelle\nvere. Se gli mostri una\n\nbanana, si agitano\ndalla gioia.\n\n")
  LANGUAGE_TEXT(4, "Los robots mono est\xe1n\nprogramados para\n\ncomportarse como\nmonos.\n\nPor lo que si le\nmuestras a uno un\n\npl\xe1tano, se emocionar\xe1.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
