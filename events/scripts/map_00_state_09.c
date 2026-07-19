#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_09: map 0 state 9 */


END()
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
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You have obtained the Millennium Scale.",
      "We now have six Millennium Items... Thank you.",
      "We should now be able to use all three Egyptian God",
      "Cards!"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(SOUND_NONE)
  PLAY_MUSIC(MUSIC_704)
  PLAY_MUSIC(MUSIC_291)
  REMOVE_CARD(238)
  TALK(PORTRAIT_NONE, "Slifer the Sky Dragon card turned into stone!")
  TEXT("The deck adjustment menu will be opened.")
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C94, map_00_state_09_08E34C94, 0x08E34CA0, 0x08E34CAC)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Wh-what's happening?")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  DELAY(8)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_SURPRISED, PORTRAIT_POSITION_AUTO,
      "What's wrong?",
      "N-no! The Winged Dragon of Ra did not resurrect...",
      "And even worse, Slifer the Sky Dragon has turned back",
      "into stone..."
  )
  CHECK_FLAG(EVENT_FLAG_UNLOCKED_MONKEY_ROBOT_SIDEQUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CA0, map_00_state_09_08E34CA0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Reshef's power must be growing exponentially!",
      "The same fate most likely befell Kaiba's card.",
      "Obelisk the Tormentor has also turned back into",
      "stone.",
      "Please bring Kaiba here quickly.",
      "We must fully revive the Egyptian God Cards...",
      "But in order to do so, we need the power of all seven",
      "Millennium Items.",
      "Furthermore, all three Egyptian God Cards must be",
      "reunited in one location."
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The final Millennium Item...",
      "We have yet to find the Millennium Puzzle.",
      "But I have an idea as to its whereabouts.",
      "Please leave the Millennium Puzzle to me.",
      "While I look for it, please bring Kaiba here."
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_ISHIZU_IS_WAITING_FOR_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CAC, map_00_state_09_08E34CAC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Is this the force of Reshef the Dark Being?",
      "But without the Egyptian God Cards, we are helpless."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "There must be something we can do.",
      "I must think of all possibilities, no matter",
      "how small.",
      "In the meantime, please train diligently.",
      "You must raise your duelist level, or you will have no",
      "chance to win."
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "If you insist, Ishizu.")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I guess we have no other choice.")
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
  TEXT("Arf arf arf arf arf!")
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "This dog... Isn't this Lucky, Tristan's dog?")
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "What would Lucky be doing here?")
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  PLAY_MUSIC(MUSIC_203)
  TEXT("Arf arf arf arf arf!")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 55)
  WALK_OBJECT_Y(2, 71)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, PORTRAIT_POSITION_AUTO,
      "Do ya think somethin' happened at Tristan's",
      "house?"
  )
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Don't worry about me.",
      "You should check on your friend immediately.",
      "In the meantime, I will think of a plan to stop",
      "Reshef."
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_POSITION_AUTO,
      "Okay, Ishizu. Good luck!",
      "{PLAYER}, Joey, let's go!"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  PLAY_MUSIC(MUSIC_203)
  TEXT("Arf!")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(2, 112)
  SET_FLAG(EVENT_FLAG_SAW_LUCKY_IN_CLOCK_TOWER_SQUARE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C88, map_00_state_09_08E34C88, 0x08E34C94, 0x08E34C88)
  TEXT("The deck adjustment menu will be opened.")
  PAGE_BREAK()
  START_MENU()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34C64, map_00_state_09_08E34C64, 0x08E34CD0, 0x08E34CE8)
  CHECK_FLAG(EVENT_FLAG_COMPLETED_ROBOT_MONKEY_SIDEQUEST)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CD0, map_00_state_09_08E34CD0, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "In order to restore the Egyptian God Cards from",
      "stone...",
      "I'm sorry, but I have yet to find the solution."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CE8, map_00_state_09_08E34CE8, EVENT_NOP, EVENT_NOP)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You have returned at the right time.",
      "To restore the Egyptian God Cards from stone...",
      "We need the Millennium Items."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "But we tried that already. It didn't work.")
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "That was because the Items were too weak.",
      "We need all the Millennium Items in one place.",
      "If we have them all, the Egyptian God Cards will be",
      "restored."
  )
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "All the Millennium Items...")
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Yes, all that remains is the Millennium Puzzle.")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_13)
  DELAY(8)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Have no fear.",
      "I have an idea of its whereabouts.",
      "I will retrieve the Millennium Puzzle."
  )
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Ishizu, you don't have to go.",
      "Let us handle it."
  )
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I have a different task for you.")
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "A different one?")
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Ra and Slifer were not the only Egyptian God Cards",
      "that turned into stone...",
      "Kaiba's Obelisk the Tormentor must have turned",
      "into stone as well.",
      "Please find Kaiba.",
      "We need to bring the seven Millennium Items...",
      "And the three Egyptian God Cards together.",
      "Only then can we fully restore the Egyptian God",
      "Cards."
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_ISHIZU_IS_WAITING_FOR_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CB8, map_00_state_09_08E34CB8, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I will find the Millennium Puzzle..",
      "In the meantime, please bring Kaiba here."
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

EVENT_SCRIPT_REPLACEMENT(0x08E34CDC, map_00_state_09_08E34CDC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I thought you were going to look for your friend",
      "Tristan.",
      "I'm having difficulty finding out how to restore",
      "the Egyptian God Cards.",
      "It will take me more time. Since there is little that",
      "you can do to help...",
      "You should concentrate on finding your friend."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34CC4, map_00_state_09_08E34CC4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "The Egyptian God Cards have been turned back into",
      "stone.",
      "To fully resurrect them, the seven Millennium Items...",
      "And the three Egyptian God Cards must be brought",
      "together.",
      "Please bring Kaiba here right away."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
