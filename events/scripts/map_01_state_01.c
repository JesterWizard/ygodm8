#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_01_state_01: map 1 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E42670, map_01_state_01_08E42670, 0x08E4267C, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_RED_HAT)
  LOAD_SPRITE(2, SPRITE_STYLISH_HAIR)
  LOAD_SPRITE(3, SPRITE_TEA)
  LOAD_SPRITE(4, SPRITE_ISHIZU)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  WALK_OBJECT_X(0, 24)
  WALK_OBJECT_X(14, 28)
  WALK_OBJECT_X(13, 28)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "{PLAYER}, what are you still doing here?",
      "Weren't the three of you taking the Duel Express?"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  TALK(PORTRAIT_TEA, EXPRESSION_TEA_SURPRISED, PORTRAIT_RIGHT,
      "Whaaat? The Millennium Puzzle is gone?",
      "But how? How did that happen?"
  )
  HIDE_PORTRAIT()
  DELAY(64)
  WALK_OBJECT_X(4, 40)
  WALK_OBJECT_Y(4, 32)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Forgive me, but I overheard your conversation.")
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
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "So it seems the Millennium Puzzle has also",
      "disappeared...",
      "What I have feared the most is coming to fruition...",
      "Please.",
      "I need your help."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_3 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "I see you're puzzled, but that is only to be",
      "expected.",
      "Please bear with me and listen to my words",
      "carefully."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4267C, map_01_state_01_08E4267C, 0x08E42688, EVENT_NOP)
  TEXT(
      "I have come to ask you duelists for your help.",
      "You must save the world from Reshef the Dark Being."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_3 | OBJECT_13 | OBJECT_14)
  DELAY(32)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "I understand this is sudden and confusing.",
      "However, the world is in grave peril.",
      "Only strong duelists, such as yourselves, can save us",
      "all from ruin before it's too late!"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  WALK_OBJECT_X(4, 24)
  DELAY(32)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "All the Millennium Items have disappeared...",
      "This is most likely due to Reshef's resurrection.",
      "An unknown entity must have commenced a fusion ritual",
      "on the Egyptian God Cards..."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Which re-released Reshef the Dark Being into the world.",
      "The ritual stole the mighty power of the Egyptian God",
      "Cards.",
      "And the cards, now drained of its mystical energies,",
      "transformed into stone.",
      "You must send the Dark Being to its eternal rest before",
      "the world is destroyed.",
      "But in order to accomplish this feat, the Egyptian God",
      "Cards are absolutely essential.",
      "However, since the Egyptian God Cards have been turned",
      "to stone, they no longer have power.",
      "Only the Millennium Items can restore them to their",
      "former glory.",
      "The Items have been scattered all over the",
      "world.",
      "They must be regained to resurrect the Egyptian God",
      "Cards.",
      "And with help from the Egyptian Gods, we may have",
      "a chance of sealing away the Dark Being.",
      "I am counting on you to accomplish this task."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(4, DIRECTION_DOWN, 4, 0)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Please, my powerful duelists...",
      "If left unchecked, the Dark Being's strength will keep",
      "growing.",
      "The world will be shrouded in perpetual darkness.",
      "Please help save the world!"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "What should we do, {PLAYER}?")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42688, map_01_state_01_08E42688, 0x08E42694, 0x08E426D0)
  TEXT("{CARD_1}Defeat the Dark Being\nThat's impossible...{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42694, map_01_state_01_08E42694, 0x08E426A0, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_HAPPY, PORTRAIT_RIGHT,
      "I knew you'd say that.",
      "Besides, I have to find my Millennium Puzzle.",
      "I'll go with you, {PLAYER}."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  DELAY(16)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "Since you said I'm a powerful duelist, how can I",
      "refuse!",
      "I'm coming along, too, {PLAYER}!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426A0, map_01_state_01_08E426A0, 0x08E426AC, 0x08E426B8)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_RIGHT, "I thank you from the bottom of my heart.")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_RIGHT,
      "First, the Millennium Items must be recovered.",
      "As a descendent of a clan of gravekeepers...",
      "I can sense the faint pulses of the Millennium Items.",
      "You must first make your way to the Egypt Exhibition.",
      "If my feelings are correct, the first of the Millennium",
      "Items should be there."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  WALK_OBJECT_X(4, 16)
  DELAY(32)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "I know what I ask is a great imposition.",
      "But I have no one to turn to except for you..."
  )
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "{CARD_1}Leave it to us!\n...{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426AC, map_01_state_01_08E426AC, 0x08E426C4, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_HAPPY, PORTRAIT_RIGHT,
      "Your words have given me hope for the first time in",
      "a long time.",
      "I leave the fate of the world in your hands..."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426C4, map_01_state_01_08E426C4, EVENT_NOP, EVENT_NOP)
  FADE_MUSIC(4)
  MOVE_OBJECT(4, DIRECTION_LEFT, 32, 0)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426B8, map_01_state_01_08E426B8, 0x08E426C4, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "I know this seems like an impossible task...",
      "But I have faith in your spirit that you will save",
      "the world..."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426D0, map_01_state_01_08E426D0, 0x08E42688, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "What? And pretend that this Dark Being doesn't exist?",
      "This doesn't sound like you, {PLAYER}."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426E8, map_01_state_01_08E426E8, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I want to ride the Duel Express...",
      "But at my level, I'll get creamed in seconds."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426F4, map_01_state_01_08E426F4, 0x08E42700, 0x08E42718)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_RED_HAT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42700, map_01_state_01_08E42700, 0x08E4270C, 0x08F0404C)
  TEXT("A street duel? Sure! Let's duel!")
  DUEL(DUELIST_YUGI_001)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4270C, map_01_state_01_08E4270C, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT("Sigh... I knew I needed to be better.")
  SET_FLAG(EVENT_FLAG_DEFEATED_RED_HAT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42718, map_01_state_01_08E42718, EVENT_NOP, EVENT_NOP)
  TEXT("I'll challenge you when I have more experience.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42724, map_01_state_01_08E42724, EVENT_NOP, EVENT_NOP)
  TEXT(
      "Today's the day the Duel Express starts chugging!",
      "The best duelists have entered this tournament,",
      "and when I say the best, I mean the best!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42730, map_01_state_01_08E42730, 0x08E4273C, 0x08E42754)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_STYLISH_HAIR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4273C, map_01_state_01_08E4273C, 0x08E42748, 0x08F0404C)
  TEXT("You must be a bad duelist if you're out here.")
  DUEL(DUELIST_YUGI_002)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42748, map_01_state_01_08E42748, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_CLOCK_TOWER_SQUARE)
  TEXT(
      "I said all the top duelists are aboard the Duel",
      "Express.",
      "...But I may be wrong. You're pretty tough!"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_STYLISH_HAIR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E42754, map_01_state_01_08E42754, EVENT_NOP, EVENT_NOP)
  TEXT("You know I'm no match for you.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E426DC, map_01_state_01_08E426DC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_TEA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "You're going, {PLAYER}?",
      "The Egypt Exhibition is the last stop on the Duel",
      "Express.",
      "I don't think it's left yet, but it will soon! If you",
      "hurry, you can still catch it at the station.",
      "I'll be waiting at Yugi's grandpa's place.",
      "Come see us when you get back, okay?"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(3, DIRECTION_LEFT, 48, 0)
  SET_FLAG(EVENT_FLAG_TEA_LEFT_FOR_THE_SHOP)
  FALLTHROUGH()
END_EVENT_SCRIPT()
