#include "event_macros.h"
#include "overworld.h"

/* map_34_state_04: map 34 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EC265C, map_34_state_04_08EC265C, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SERIOUS_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_CHIEF_ARCHEOLOGIST)
  LOAD_SPRITE(3, SPRITE_FRIVOULOUS_ARCHEOLOGIST)
  TEXT("A long time ago, we were on\na dig in Egypt where we\n\nunearthed a stone tablet.\n\nLegend says the Egyptian\nGods fused together to\n\ncontain a malevolent and\ndangerous force inside the\n\ntablet.\n\nIf the darkness is ever set\nfree, the world will end.\n\nIt might just be a fairy\ntale, but it's pretty scary\n\nstuff.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2668, map_34_state_04_08EC2668, 0x08EC2674, 0x08EC268C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2674, map_34_state_04_08EC2674, 0x08EC2680, 0x08F0404C)
  TEXT("A duel, eh?\n\nWell, all right. It'll be a\nnice change of pace.\n\n")
  DUEL(101)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2680, map_34_state_04_08EC2680, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(244)
  TEXT("Hey, that was fun!\n\nBut it's about time I got\nback to work.\n\n")
  SET_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC268C, map_34_state_04_08EC268C, 0x08F04040, 0x08F04040)
  TEXT("I'm working. Another time.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2698, map_34_state_04_08EC2698, 0x08F04040, 0x08F04040)
  TEXT("I hear Duel Monsters are\nbased on stone tablets.\n\nWeren't those tablets found\nin Egypt?\n\nWe only dig fossils here, so\nwe won't find any tablets.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26A4, map_34_state_04_08EC26A4, 0x08F04040, 0x08F04040)
  TEXT("Nah, I'm focused on my work.\n\nI don't duel at all.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26B0, map_34_state_04_08EC26B0, 0x08F04040, 0x08F04040)
  TEXT("I wish I could unearth some\nrare fossils.\n\nActually, I'd like to find\nanything, as long as it's\n\nrare.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26BC, map_34_state_04_08EC26BC, 0x08F04040, 0x08F04040)
  TEXT("No, I'll get in trouble if I\ngoof off too much.\n\nSorry, next time.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
