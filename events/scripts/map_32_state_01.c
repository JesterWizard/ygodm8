#include "event_macros.h"
#include "overworld.h"

/* map_32_state_01: map 32 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EB8FC4, map_32_state_01_08EB8FC4, 0x08EB8FDC, 0x08EB8FDC)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_DOX)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB8FDC, map_32_state_01_08EB8FDC, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Aiyah! This is the Great\nWall of China.\n\nIt is one of China's\ntreasures. There's nothing\n\nfiner.\n\n")
  LANGUAGE_TEXT(1, "Aiyah ! Ca \xeatre Grande\nMuraille de Chine.\n\nCa \xeatre grand tr\xe9sor\nchinois !\n\n")
  LANGUAGE_TEXT(2, "Aiyah! Das ist Chinesische\nMauer.\n\nChinesische Mauer ein\nnationales Erbe.\n\n")
  LANGUAGE_TEXT(3, "Salve! Questa \xe8 la Grande\nMuraglia cinese.\n\nGrande Muraglia cinese uno\ndei tesori della Cina.\n\n")
  LANGUAGE_TEXT(4, "\xa1Aiyah! Esto es Gran\nMuralla China.\n\nGran Muralla China, uno\nde los tesoros chinos.\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(EVENT_FLAG_TALKED_TO_DOX)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB8FD0, map_32_state_01_08EB8FD0, 0x08EB8FDC, 0x08EB8FE8)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_DOX)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB8FE8, map_32_state_01_08EB8FE8, 0x08EB8FF4, 0x08EB8FF4)
  CHECK_FLAG(EVENT_FLAG_JOEY_FOUND_PARA_AND_DOX_SUSPICIOUS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB8FF4, map_32_state_01_08EB8FF4, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "Aiyah! I do not know how to\nduel.\n\n")
  LANGUAGE_TEXT(1, "Aiyah ! Moi pas\nconna\xeetre duels.\n\n")
  LANGUAGE_TEXT(2, "Aiyah! Ich wei\xdf nichts\nvon Duellen.\n\n")
  LANGUAGE_TEXT(3, "Ehehi! Io non\nsapere duellare.\n\n")
  LANGUAGE_TEXT(4, "\xa1Aiyah!\nNo s\xe9 de duelos.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
