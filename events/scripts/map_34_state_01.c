#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_34_state_01: map 34 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EC2524, map_34_state_01_08EC2524, 0x08EC2530, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_SERIOUS_ARCHEOLOGIST)
  LOAD_SPRITE(2, SPRITE_CHIEF_ARCHEOLOGIST)
  LOAD_SPRITE(3, SPRITE_FRIVOULOUS_ARCHEOLOGIST)
  CHECK_FLAG(EVENT_FLAG_ENTERED_CANADA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2530, map_34_state_01_08EC2530, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_707)
  PLAY_MUSIC(MUSIC_381)
  SET_FLAG(EVENT_FLAG_ENTERED_CANADA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC253C, map_34_state_01_08EC253C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "You can find a ton of\n"
      "dinosaur fossils here.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2548, map_34_state_01_08EC2548, 0x08EC2554, 0x08EC256C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2554, map_34_state_01_08EC2554, 0x08EC2560, 0x08F0404C)
  TEXT
  (
      "You want to duel, eh? Well,\n"
      "I can use a break.\n\n"
  )
  DELAY(16)
  TEXT
  (
      "Okay!\n"
  )
  DELAY(16)
  TEXT
  (
      "Let's duel!\n\n"
  )
  DUEL(DUELIST_ID_044)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2560, map_34_state_01_08EC2560, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_244)
  TEXT
  (
      "That was fun, eh?\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_SERIOUS_ARCHEOLOGIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC256C, map_34_state_01_08EC256C, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I can't play too many times.\n"
      "I'm actually working.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2578, map_34_state_01_08EC2578, 0x08EC2584, 0x08EC25B4)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_CHIEF_ARCHEOLOGIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2584, map_34_state_01_08EC2584, 0x08EC2590, 0x08EC259C)
  TEXT
  (
      "Are you a duelist, too?\n\n"
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC2590, map_34_state_01_08EC2590, 0x08EC25A8, 0x08F04040)
  TEXT
  (
      "Is the latest fad among\n"
      "duelists to dig up fossils?\n\n"
      "Some of your buddies are in\n"
      "the back digging.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25A8, map_34_state_01_08EC25A8, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO,
    "What are duelists doing\n"
    "here? What if it's...\n\n"
)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
    "It might be the Neo Ghouls!\n"
    "Let's go, {PLAYER}!\n\n"
)
  SET_FLAG(EVENT_FLAG_TALKED_TO_CHIEF_ARCHEOLOGIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC259C, map_34_state_01_08EC259C, 0x08EC25A8, 0x08F04040)
  TEXT
  (
      "Some guys calling themselves\n"
      "duelists came by.\n\n"
      "They're out in the back\n"
      "digging for fossils.\n\n"
      "I thought they were your\n"
      "buddies.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25B4, map_34_state_01_08EC25B4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Some duelist pals of yours\n"
      "are digging for fossils.\n\n"
      "They're out in the back.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25C0, map_34_state_01_08EC25C0, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm no duelist. So no\n"
      "dueling for me, buddy.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25CC, map_34_state_01_08EC25CC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm hoping for a big\n"
      "discovery, eh?\n\n"
      "Then I'll be famous!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25D8, map_34_state_01_08EC25D8, 0x08EC25E4, 0x08EC25FC)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_FRIVOLOUS_ARCHEOLOGIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25E4, map_34_state_01_08EC25E4, 0x08EC25F0, 0x08F0404C)
  TEXT
  (
      "Instead of looking for\n"
      "fossils, maybe I'll become\n\n"
      "the King of Games.\n\n"
      "It's a quicker way to become\n"
      "famous!\n\n"
      "It sure beats digging old\n"
      "bones up. Sure, let's duel!\n\n"
  )
  DUEL(DUELIST_JOEY_045)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25F0, map_34_state_01_08EC25F0, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_244)
  TEXT
  (
      "At this rate, I'll never\n"
      "become famous...\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_FRIVOLOUS_ARCHEOLOGIST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC25FC, map_34_state_01_08EC25FC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I gave up trying to be the\n"
      "world's best duelist.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
