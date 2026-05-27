#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_34_state_04: map 34 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EC265C, map_34_state_04_08EC265C, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SERIOUS_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_CHIEF_ARCHEOLOGIST)
  LOAD_SPRITE(3, SPRITE_FRIVOULOUS_ARCHEOLOGIST)
  TEXT
  (
      "A long time ago, we were on\n"
      "a dig in Egypt where we\n\n"
      "unearthed a stone tablet.\n\n"
      "Legend says the Egyptian\n"
      "Gods fused together to\n\n"
      "contain a malevolent and\n"
      "dangerous force inside the\n\n"
      "tablet.\n\n"
      "If the darkness is ever set\n"
      "free, the world will end.\n\n"
      "It might just be a fairy\n"
      "tale, but it's pretty scary\n\n"
      "stuff.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2668, map_34_state_04_08EC2668, 0x08EC2674, 0x08EC268C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2674, map_34_state_04_08EC2674, 0x08EC2680, 0x08F0404C)
  TEXT
  (
      "A duel, eh?\n\n"
      "Well, all right. It'll be a\n"
      "nice change of pace.\n\n"
  )
  DUEL(DUELIST_ID_101)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2680, map_34_state_04_08EC2680, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_244)
  TEXT
  (
      "Hey, that was fun!\n\n"
      "But it's about time I got\n"
      "back to work.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC268C, map_34_state_04_08EC268C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm working. Another time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2698, map_34_state_04_08EC2698, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I hear Duel Monsters are\n"
      "based on stone tablets.\n\n"
      "Weren't those tablets found\n"
      "in Egypt?\n\n"
      "We only dig fossils here, so\n"
      "we won't find any tablets.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26A4, map_34_state_04_08EC26A4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Nah, I'm focused on my work.\n\n"
      "I don't duel at all.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26B0, map_34_state_04_08EC26B0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I wish I could unearth some\n"
      "rare fossils.\n\n"
      "Actually, I'd like to find\n"
      "anything, as long as it's\n\n"
      "rare.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26BC, map_34_state_04_08EC26BC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "No, I'll get in trouble if I\n"
      "goof off too much.\n\n"
      "Sorry, next time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
