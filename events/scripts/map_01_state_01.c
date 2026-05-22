#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_01_state_01: map 1 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E42670, map_01_state_01_08E42670, 0x08E4267C, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_RED_HAT)
  LOAD_SPRITE(2, SPRITE_STYLISH_HAIR)
  LOAD_SPRITE(3, SPRITE_TEA)
  LOAD_SPRITE(4, SPRITE_ISHIZU)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  WALK_OBJECT_X(0, 24)
  WALK_OBJECT_X(14, 28)
  WALK_OBJECT_X(13, 28)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "{PLAYER}, what are you still\n"
      "doing here?\n\n"
      "Weren't the three of you\n"
      "taking the Duel Express?\n\n"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_TEA_SURPRISED, PORTRAIT_RIGHT)
  TEXT
  (
      "Whaaat? The Millennium\n"
      "Puzzle is gone?\n\n"
      "But how? How did that\n"
      "happen?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(64)
  WALK_OBJECT_X(4, 40)
  WALK_OBJECT_Y(4, 32)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Forgive me, but I overheard\n"
      "your conversation.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_3 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(3, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "So it seems the Millennium\n"
      "Puzzle has also\n\n"
      "disappeared...\n\n"
      "What I have feared the most\n"
      "is coming to fruition...\n\n"
      "Please.\n\n"
      "I need your help.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_3 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I see you're puzzled, but\n"
      "that is only to be\n\n"
      "expected.\n\n"
      "Please bear with me and\n"
      "listen to my words\n\n"
      "carefully.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4267C, map_01_state_01_08E4267C, 0x08E42688, 0x08F04040)
  TEXT
  (
      "I have come to ask you\n"
      "duelists for your help.\n\n"
      "You must save the world from\n"
      "Reshef the Dark Being.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_3 | OBJECT_13 | OBJECT_14)
  DELAY(32)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I understand this is sudden\n"
      "and confusing.\n\n"
      "However, the world is in\n"
      "grave peril.\n\n"
      "Only strong duelists, such\n"
      "as yourselves, can save us\n\n"
      "all from ruin before it's\n"
      "too late!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  WALK_OBJECT_X(4, 24)
  DELAY(32)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "All the Millennium Items\n"
      "have disappeared...\n\n"
      "This is most likely due to\n"
      "Reshef's resurrection.\n\n"
      "An unknown entity must have\n"
      "commenced a fusion ritual\n\n"
      "on the Egyptian God Cards...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Which re-released Reshef the\n"
      "Dark Being into the world.\n\n"
      "The ritual stole the mighty\n"
      "power of the Egyptian God\n\n"
      "Cards.\n\n"
      "And the cards, now drained\n"
      "of its mystical energies,\n\n"
      "transformed into stone.\n\n"
      "You must send the Dark Being\n"
      "to its eternal rest before\n\n"
      "the world is destroyed.\n\n"
      "But in order to accomplish\n"
      "this feat, the Egyptian God\n\n"
      "Cards are absolutely\n"
      "essential.\n\n"
      "However, since the Egyptian\n"
      "God Cards have been turned\n\n"
      "to stone, they no longer\n"
      "have power.\n\n"
      "Only the Millennium Items\n"
      "can restore them to their\n\n"
      "former glory.\n\n"
      "The Items have been\n"
      "scattered all over the\n\n"
      "world.\n\n"
      "They must be regained to\n"
      "resurrect the Egyptian God\n\n"
      "Cards.\n\n"
      "And with help from the\n"
      "Egyptian Gods, we may have\n\n"
      "a chance of sealing away the\n"
      "Dark Being.\n\n"
      "I am counting on you to\n"
      "accomplish this task.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(4, DIRECTION_DOWN, 4, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Please, my powerful\n"
      "duelists...\n\n"
      "If left unchecked, the Dark\n"
      "Being's strength will keep\n\n"
      "growing.\n\n"
      "The world will be shrouded\n"
      "in perpetual darkness.\n\n"
      "Please help save the world!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "What should we do, {PLAYER}?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42688, map_01_state_01_08E42688, 0x08E42694, 0x08E426D0)
  TEXT
  (
      "{CARD_1}Defeat the Dark Being\n"
      "That's impossible...{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42694, map_01_state_01_08E42694, 0x08E426A0, 0x08F04040)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "I knew you'd say that.\n\n"
      "Besides, I have to find my\n"
      "Millennium Puzzle.\n\n"
      "I'll go with you, {PLAYER}.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  DELAY(16)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Since you said I'm a\n"
      "powerful duelist, how can I\n\n"
      "refuse!\n\n"
      "I'm coming along, too,\n"
      "{PLAYER}!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426A0, map_01_state_01_08E426A0, 0x08E426AC, 0x08E426B8)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "I thank you from the bottom\n"
      "of my heart.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "First, the Millennium Items\n"
      "must be recovered.\n\n"
      "As a descendent of a clan of\n"
      "gravekeepers...\n\n"
      "I can sense the faint pulses\n"
      "of the Millennium Items.\n\n"
      "You must first make your way\n"
      "to the Egypt Exhibition.\n\n"
      "If my feelings are correct,\n"
      "the first of the Millennium\n\n"
      "Items should be there.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  WALK_OBJECT_X(4, 16)
  DELAY(32)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I know what I ask is a great\n"
      "imposition.\n\n"
      "But I have no one to turn to\n"
      "except for you...\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "{CARD_1}Leave it to us!\n"
      "...{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426AC, map_01_state_01_08E426AC, 0x08E426C4, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_RIGHT)
  TEXT
  (
      "Your words have given me\n"
      "hope for the first time in\n\n"
      "a long time.\n\n"
      "I leave the fate of the\n"
      "world in your hands...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426C4, map_01_state_01_08E426C4, 0x08F04040, 0x08F04040)
  FADE_MUSIC(4)
  MOVE_OBJECT(4, DIRECTION_LEFT, 32, 0)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426B8, map_01_state_01_08E426B8, 0x08E426C4, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "I know this seems like an\n"
      "impossible task...\n\n"
      "But I have faith in your\n"
      "spirit that you will save\n\n"
      "the world...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426D0, map_01_state_01_08E426D0, 0x08E42688, 0x08F04040)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "What? And pretend that this\n"
      "Dark Being doesn't exist?\n\n"
      "This doesn't sound like you,\n"
      "{PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426E8, map_01_state_01_08E426E8, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I want to ride the Duel\n"
      "Express...\n\n"
      "But at my level, I'll get\n"
      "creamed in seconds.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426F4, map_01_state_01_08E426F4, 0x08E42700, 0x08E42718)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_HAT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42700, map_01_state_01_08E42700, 0x08E4270C, 0x08F0404C)
  TEXT
  (
      "A street duel? Sure! Let's\n"
      "duel!\n\n"
  )
  DUEL(1)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4270C, map_01_state_01_08E4270C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "Sigh... I knew I needed to\n"
      "be better.\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_HAT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42718, map_01_state_01_08E42718, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'll challenge you when I\n"
      "have more experience.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42724, map_01_state_01_08E42724, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Today's the day the Duel\n"
      "Express starts chugging!\n\n"
      "The best duelists have\n"
      "entered this tournament,\n\n"
      "and when I say the best, I\n"
      "mean the best!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42730, map_01_state_01_08E42730, 0x08E4273C, 0x08E42754)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_STYLISH_HAIR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4273C, map_01_state_01_08E4273C, 0x08E42748, 0x08F0404C)
  TEXT
  (
      "You must be a bad duelist if\n"
      "you're out here.\n\n"
  )
  DUEL(2)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42748, map_01_state_01_08E42748, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT
  (
      "I said all the top duelists\n"
      "are aboard the Duel\n\n"
      "Express.\n\n"
      "...But I may be wrong.\n"
      "You're pretty tough!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_STYLISH_HAIR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42754, map_01_state_01_08E42754, 0x08F04040, 0x08F04040)
  TEXT
  (
      "You know I'm no match for\n"
      "you.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426DC, map_01_state_01_08E426DC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "You're going, {PLAYER}?\n\n"
      "The Egypt Exhibition is the\n"
      "last stop on the Duel\n\n"
      "Express.\n\n"
      "I don't think it's left yet,\n"
      "but it will soon! If you\n\n"
      "hurry, you can still catch\n"
      "it at the station.\n\n"
      "I'll be waiting at Yugi's\n"
      "grandpa's place.\n\n"
      "Come see us when you get\n"
      "back, okay?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_LEFT, 48, 0)
  SET_FLAG(EVENT_FLAG_TEA_LEFT_FOR_THE_SHOP)
  FALLTHROUGH()
END_EVENT_SCRIPT()
