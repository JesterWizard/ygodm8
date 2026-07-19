#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_34_state_04: map 34 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EC265C, map_34_state_04_08EC265C, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_SERIOUS_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_CHIEF_ARCHEOLOGIST)
  LOAD_SPRITE(3, SPRITE_FRIVOULOUS_ARCHEOLOGIST)
  TEXT(
      "A long time ago, we were on a dig in Egypt where we",
      "unearthed a stone tablet.",
      "Legend says the Egyptian Gods fused together to",
      "contain a malevolent and dangerous force inside the",
      "tablet.",
      "If the darkness is ever set free, the world will end.",
      "It might just be a fairy tale, but it's pretty scary",
      "stuff."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2668, map_34_state_04_08EC2668, 0x08EC2674, 0x08EC268C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2674, map_34_state_04_08EC2674, 0x08EC2680, 0x08F0404C)
  TEXT(
      "A duel, eh?",
      "Well, all right. It'll be a nice change of pace."
  )
  DUEL(DUELIST_ID_101)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2680, map_34_state_04_08EC2680, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_244)
  TEXT(
      "Hey, that was fun!",
      "But it's about time I got back to work."
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC268C, map_34_state_04_08EC268C, EVENT_NOP, EVENT_NOP)
  TEXT("I'm working. Another time.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2698, map_34_state_04_08EC2698, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I hear Duel Monsters are based on stone tablets.",
      "Weren't those tablets found in Egypt?",
      "We only dig fossils here, so we won't find any tablets."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26A4, map_34_state_04_08EC26A4, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Nah, I'm focused on my work.",
      "I don't duel at all."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26B0, map_34_state_04_08EC26B0, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I wish I could unearth some rare fossils.",
      "Actually, I'd like to find anything, as long as it's",
      "rare."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC26BC, map_34_state_04_08EC26BC, EVENT_NOP, EVENT_NOP)
  TEXT(
      "No, I'll get in trouble if I goof off too much.",
      "Sorry, next time."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
