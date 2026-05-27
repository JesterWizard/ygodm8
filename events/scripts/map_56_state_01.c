#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_56_state_01: map 56 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EF2F84, map_56_state_01_08EF2F84, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_NOAH)
  LOAD_SPRITE(2, SPRITE_MARIK)
  LOAD_SPRITE(3, SPRITE_BAKURA)
  LOAD_SPRITE(4, SPRITE_ATEM)
  LOAD_SPRITE(5, SPRITE_JOEY)
  LOAD_SPRITE(6, SPRITE_SETO)
  LOAD_SPRITE(7, SPRITE_PEGASUS)
  LOAD_SPRITE(8, SPRITE_PARADOX)
  LOAD_SPRITE(9, SPRITE_SHADI)
  PORTRAIT(PORTRAIT_NOAH, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My name is Noah.\n\n"
      "Shall I make you a\n"
      "permanent citizen of my\n\n"
      "virtual world?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2F90, map_56_state_01_08EF2F90, 0x08EF2F9C, 0x08F0404C)
  PORTRAIT(PORTRAIT_NOAH, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Heh. You want me to duel\n"
      "you?\n\n"
      "I admire your courage, but\n"
      "your stupidity will be\n\n"
      "your downfall!\n\n"
      "Savor the bitter taste of\n"
      "defeat!\n\n"
  )
  DUEL(DUELIST_NOAH_134)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2F9C, map_56_state_01_08EF2F9C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_NOAH, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "This can't be!\n\n"
      "My skills are superior to\n"
      "yours in every way!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FA8, map_56_state_01_08EF2FA8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DARK_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hahahahahahaha!\n\n"
      "I'll destroy you and plunge\n"
      "the world into darkness!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FB4, map_56_state_01_08EF2FB4, 0x08EF2FC0, 0x08F0404C)
  PORTRAIT(PORTRAIT_DARK_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'll annihilate you quick.\n\n"
      "In fact, I'll beat you in\n"
      "one turn!\n\n"
      "Fuhahahahaha!\n\n"
  )
  DUEL(DUELIST_DARK_MARIK_135)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FC0, map_56_state_01_08EF2FC0, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_DARK_MARIK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wh-what? How could I lose...\n\n"
      "Just wait. I will send you\n"
      "to the Shadow Realm in\n\n"
      "time! Ha ha ha...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FCC, map_56_state_01_08EF2FCC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DARK_BAKURA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hahahahaha!\n\n"
      "I don't think it's wise for\n"
      "you to get to know me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FD8, map_56_state_01_08EF2FD8, 0x08EF2FE4, 0x08F0404C)
  PORTRAIT(PORTRAIT_DARK_BAKURA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My occult deck will banish\n"
      "you into the shadows!\n\n"
  )
  DUEL(DUELIST_DARK_BAKURA_136)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FE4, map_56_state_01_08EF2FE4, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_DARK_BAKURA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Grr... I won't forget\n"
      "this... I will get my\n\n"
      "revenge!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FF0, map_56_state_01_08EF2FF0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ATEM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, what can be seen\n"
      "and not seen at the same\n\n"
      "time?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF2FFC, map_56_state_01_08EF2FFC, 0x08EF3008, 0x08F0404C)
  PORTRAIT(PORTRAIT_ATEM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I accept your challenge!\n\n"
  )
  DUEL(DUELIST_ATEM_137)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3008, map_56_state_01_08EF3008, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_ATEM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You've become much stronger,\n"
      "{PLAYER}.\n\n"
      "But you won't win so easily\n"
      "next time.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3014, map_56_state_01_08EF3014, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DARK_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}...\n\n"
      "You're goin' down...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3020, map_56_state_01_08EF3020, 0x08EF302C, 0x08F0404C)
  PORTRAIT(PORTRAIT_DARK_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Even your family won't\n"
      "recognize you after I\n\n"
      "finish pummeling ya!\n\n"
  )
  DUEL(DUELIST_DARK_JOEY_138)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF302C, map_56_state_01_08EF302C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_DARK_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My... Memories...\n\n"
      "I remember I'm a...\n"
      "True duelist...\n\n"
      "Gwaaaaaaaaaaah!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3038, map_56_state_01_08EF3038, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You want to know who my\n"
      "strongest rival is?\n\n"
      "Heh. One thing's for\n"
      "certain. It's not you.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3044, map_56_state_01_08EF3044, 0x08EF3050, 0x08F0404C)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "A duel can start anyplace\n"
      "and anytime two duelists\n\n"
      "meet.\n\n"
      "I accept your duel!\n\n"
  )
  DUEL(DUELIST_SETO_139)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3050, map_56_state_01_08EF3050, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I... Lost?\n\n"
      "Grr... You better not lose\n"
      "to anyone else!\n\n"
      "Not after you'd beaten me!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF305C, map_56_state_01_08EF305C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The finest drink,\n"
      "The tastiest Gorgonzola\n\n"
      "cheese...\n\n"
      "The funniest comic book in\n"
      "the world...\n\n"
      "What more can any man want?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3068, map_56_state_01_08EF3068, 0x08EF3074, 0x08F0404C)
  PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I've scanned your mind.\n\n"
      "I can read your strategies\n"
      "as if it were an open book!\n\n"
      "I hate to say this, but you\n"
      "have no chance to win!\n\n"
  )
  DUEL(DUELIST_SOL_CHEVALSKY_140)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3074, map_56_state_01_08EF3074, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Noooooo!\n\n"
      "I'm the creator of Duel\n"
      "Monsters!\n\n"
      "Losing is not in the cards!\n"
      "Unbelievable!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3080, map_56_state_01_08EF3080, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I am Paradox.\n\n"
      "I am the sage for all\n"
      "duelists.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF308C, map_56_state_01_08EF308C, 0x08EF3098, 0x08F0404C)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You're challenging me?\n"
      "Either you're brave...\n\n"
      "Or you underestimate me...\n\n"
  )
  DUEL(DUELIST_PARADOX_141)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF3098, map_56_state_01_08EF3098, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_PARADOX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Perhaps my time has\n"
      "passed...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF30A4, map_56_state_01_08EF30A4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My name is Shadi...\n\n"
      "You have a room in your\n"
      "soul...\n\n"
      "Which I will disassemble!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF30B0, map_56_state_01_08EF30B0, 0x08EF30BC, 0x08F0404C)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "This duel has been foretold\n"
      "millenniums ago...\n\n"
      "Can you overcome my test?\n\n"
  )
  DUEL(DUELIST_SHADI_142)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EF30BC, map_56_state_01_08EF30BC, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_HALL_OF_ETERNITY)
  PORTRAIT(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You have prevailed...\n"
      "I am thoroughly defeated.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
