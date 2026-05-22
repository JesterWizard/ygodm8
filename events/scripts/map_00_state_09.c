#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_09: map 0 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08E34C34, map_00_state_09_08E34C34, 0x08E34C4C, 0x08E34CB8)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_LUCKY)
  CHECK_FLAG(EVENT_FLAG_ISHIZU_IS_WAITING_FOR_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C4C, map_00_state_09_08E34C4C, 0x08E34C7C, 0x08E34C64)
  CHECK_FLAG(EVENT_FLAG_SAW_LUCKY_IN_CLOCK_TOWER_SQUARE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C7C, map_00_state_09_08E34C7C, 0x08E34C94, 0x08E34C88)
  WALK_OBJECT_Y(0, 32)
  WALK_OBJECT_X(0, 48)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 42)
  WALK_OBJECT_X(13, 54)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 42)
  WALK_OBJECT_X(14, 42)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You have obtained the\n"
      "Millennium Scale.\n\n"
      "We now have six Millennium\n"
      "Items... Thank you.\n\n"
      "We should now be able to use\n"
      "all three Egyptian God\n\n"
      "Cards!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(SOUND_NONE)
  PLAY_MUSIC(MUSIC_704)
  PLAY_MUSIC(MUSIC_291)
  REMOVE_CARD(238)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Slifer the Sky Dragon card\n"
      "turned into stone!\n\n"
  )
  TEXT
  (
      "The deck adjustment menu\n"
      "will be opened."
  )
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C94, map_00_state_09_08E34C94, 0x08E34CA0, 0x08E34CAC)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wh-what's happening?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What's wrong?\n\n"
      "N-no! The Winged Dragon of\n"
      "Ra did not resurrect...\n\n"
      "And even worse, Slifer the\n"
      "Sky Dragon has turned back\n\n"
      "into stone...\n\n"
  )
  CHECK_FLAG(EVENT_FLAG_UNLOCKED_MONKEY_ROBOT_SIDEQUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CA0, map_00_state_09_08E34CA0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Reshef's power must be\n"
      "growing exponentially!\n\n"
      "The same fate most likely\n"
      "befell Kaiba's card.\n\n"
      "Obelisk the Tormentor has\n"
      "also turned back into\n\n"
      "stone.\n\n"
      "Please bring Kaiba here\n"
      "quickly.\n\n"
      "We must fully revive the\n"
      "Egyptian God Cards...\n\n"
      "But in order to do so, we\n"
      "need the power of all seven\n\n"
      "Millennium Items.\n\n"
      "Furthermore, all three\n"
      "Egyptian God Cards must be\n\n"
      "reunited in one location.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The final Millennium Item...\n\n"
      "We have yet to find the\n"
      "Millennium Puzzle.\n\n"
      "But I have an idea as to its\n"
      "whereabouts.\n\n"
      "Please leave the Millennium\n"
      "Puzzle to me.\n\n"
      "While I look for it, please\n"
      "bring Kaiba here.\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_ISHIZU_IS_WAITING_FOR_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CAC, map_00_state_09_08E34CAC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Is this the force of Reshef\n"
      "the Dark Being?\n\n"
      "But without the Egyptian God\n"
      "Cards, we are helpless.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "There must be something we\n"
      "can do.\n\n"
      "I must think of all\n"
      "possibilities, no matter\n\n"
      "how small.\n\n"
      "In the meantime, please\n"
      "train diligently.\n\n"
      "You must raise your duelist\n"
      "level, or you will have no\n\n"
      "chance to win.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "If you insist, Ishizu.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I guess we have no other\n"
      "choice.\n\n"
  )
  WALK_OBJECT_Y(2, 56)
  WALK_OBJECT_X(2, 48)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_1 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_MONKEY_ROBOTS)
  PLAY_MUSIC(MUSIC_203)
  TEXT
  (
      "Arf arf arf arf arf!\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "This dog... Isn't this\n"
      "Lucky, Tristan's dog?\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "What would Lucky be doing\n"
      "here?\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  PLAY_MUSIC(MUSIC_203)
  TEXT
  (
      "Arf arf arf arf arf!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 55)
  WALK_OBJECT_Y(2, 71)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Do ya think somethin'\n"
      "happened at Tristan's\n\n"
      "house?\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't worry about me.\n\n"
      "You should check on your\n"
      "friend immediately.\n\n"
      "In the meantime, I will\n"
      "think of a plan to stop\n\n"
      "Reshef.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Okay, Ishizu. Good luck!\n\n"
      "{PLAYER}, Joey, let's go!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  PLAY_MUSIC(MUSIC_203)
  TEXT
  (
      "Arf!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 112)
  SET_FLAG(EVENT_FLAG_SAW_LUCKY_IN_CLOCK_TOWER_SQUARE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C88, map_00_state_09_08E34C88, 0x08E34C94, 0x08E34C88)
  TEXT
  (
      "The deck adjustment menu\n"
      "will be opened."
  )
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C64, map_00_state_09_08E34C64, 0x08E34CD0, 0x08E34CE8)
  CHECK_FLAG(EVENT_FLAG_COMPLETED_ROBOT_MONKEY_SIDEQUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CD0, map_00_state_09_08E34CD0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "In order to restore the\n"
      "Egyptian God Cards from\n\n"
      "stone...\n\n"
      "I'm sorry, but I have yet to\n"
      "find the solution.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CE8, map_00_state_09_08E34CE8, 0x08F04040, 0x08F04040)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You have returned at the\n"
      "right time.\n\n"
      "To restore the Egyptian God\n"
      "Cards from stone...\n\n"
      "We need the Millennium\n"
      "Items.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But we tried that already.\n"
      "It didn't work.\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That was because the Items\n"
      "were too weak.\n\n"
      "We need all the Millennium\n"
      "Items in one place.\n\n"
      "If we have them all, the\n"
      "Egyptian God Cards will be\n\n"
      "restored.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "All the Millennium Items...\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yes, all that remains is the\n"
      "Millennium Puzzle.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_13)
  DELAY(8)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Have no fear.\n\n"
      "I have an idea of its\n"
      "whereabouts.\n\n"
      "I will retrieve the\n"
      "Millennium Puzzle.\n\n"
  )
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ishizu, you don't have to\n"
      "go.\n\n"
      "Let us handle it.\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I have a different task for\n"
      "you.\n\n"
  )
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "A different one?\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Ra and Slifer were not the\n"
      "only Egyptian God Cards\n\n"
      "that turned into stone...\n\n"
      "Kaiba's Obelisk the\n"
      "Tormentor must have turned\n\n"
      "into stone as well.\n\n"
      "Please find Kaiba.\n\n"
      "We need to bring the seven\n"
      "Millennium Items...\n\n"
      "And the three Egyptian God\n"
      "Cards together.\n\n"
      "Only then can we fully\n"
      "restore the Egyptian God\n\n"
      "Cards.\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_ISHIZU_IS_WAITING_FOR_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CB8, map_00_state_09_08E34CB8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I will find the Millennium\n"
      "Puzzle..\n\n"
      "In the meantime, please\n"
      "bring Kaiba here.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C40, map_00_state_09_08E34C40, 0x08E34C58, 0x08E34CC4)
  CHECK_FLAG(EVENT_FLAG_ISHIZU_IS_WAITING_FOR_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C58, map_00_state_09_08E34C58, 0x08E34C7C, 0x08E34C70)
  CHECK_FLAG(EVENT_FLAG_SAW_LUCKY_IN_CLOCK_TOWER_SQUARE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C70, map_00_state_09_08E34C70, 0x08E34CDC, 0x08E34CE8)
  CHECK_FLAG(EVENT_FLAG_COMPLETED_ROBOT_MONKEY_SIDEQUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CDC, map_00_state_09_08E34CDC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I thought you were going to\n"
      "look for your friend\n\n"
      "Tristan.\n\n"
      "I'm having difficulty\n"
      "finding out how to restore\n\n"
      "the Egyptian God Cards.\n\n"
      "It will take me more time.\n"
      "Since there is little that\n\n"
      "you can do to help...\n\n"
      "You should concentrate on\n"
      "finding your friend.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CC4, map_00_state_09_08E34CC4, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "The Egyptian God Cards have\n"
      "been turned back into\n\n"
      "stone.\n\n"
      "To fully resurrect them, the\n"
      "seven Millennium Items...\n\n"
      "And the three Egyptian God\n"
      "Cards must be brought\n\n"
      "together.\n\n"
      "Please bring Kaiba here\n"
      "right away.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
