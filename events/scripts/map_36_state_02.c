#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_36_state_02: map 36 state 2 */


END()
EVENT_SCRIPT_REPLACEMENT(0x08EC9C54, map_36_state_02_08EC9C54, 0x08EC9C60, 0x08EC9C6C)
  LOAD_SPRITE(1, SPRITE_REX)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_REX3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C60, map_36_state_02_08EC9C60, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Looks like we can't get rid of each other.",
      "You're not here to watch them dig up fossils, am I",
      "right?",
      "I can tell from the looks on your faces."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C6C, map_36_state_02_08EC9C6C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You're planning to fight someone as powerful as a",
      "T-Rex.",
      "It was obvious from the way you dueled.",
      "It must be tough to keep your skills sharp."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C78, map_36_state_02_08EC9C78, 0x08EC9C84, 0x08EC9C9C)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_REX3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C84, map_36_state_02_08EC9C84, 0x08EC9C90, 0x08F0404C)
  WALK_OBJECT_X(0, 76)
  WALK_OBJECT_Y(0, 56)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "It sounds crazy, but I guess we're connected to each",
      "other.",
      "I wonder why..."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "There must be a bond between duelists.")
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Alright, enough talk.",
      "Because action speaks louder than words.",
      "Let's duel!"
  )
  DUEL(DUELIST_REX_102)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C90, map_36_state_02_08EC9C90, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_245)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "That's it! You win!",
      "{PLAYER}, you've grown pretty strong.",
      "Don't you dare lose to anyone!",
      "I don't want anyone to think that you're weak.",
      "Not after you've beaten me!",
      "All right, take this card.",
      "It's Two-Headed King Rex.",
      "The card that best represents me is Red-Eyes",
      "B. Dragon...",
      "...Is what I'd like to say, but it's now Wheeler's",
      "card.",
      "Since the day he won it from me, I realized something.",
      "Are expensive rare cards really good for me?",
      "The more I thought about it, this card I have right now",
      "is perfect for me.",
      "It's a common card, but it embodies my spirit!"
  )
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Received Two-Headed King Rex.")
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PLAY_MUSIC(MUSIC_245)
  PAGE_BREAK()
  ADD_CARD(32)
  SET_FLAG(EVENT_FLAG_DEFEATED_REX3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C9C, map_36_state_02_08EC9C9C, 0x08EC9CA8, 0x08F0404C)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I don't know if it's worth dueling me.",
      "Especially considering what you're facing.",
      "But maybe I'll teach you something!",
      "I'll duel using all my techniques.",
      "If it means helping you, {PLAYER}, I'll do it!"
  )
  DUEL(DUELIST_REX_149)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9CA8, map_36_state_02_08EC9CA8, EVENT_NOP, EVENT_NOP)
  PLAY_MUSIC(MUSIC_245)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Well, how was I?",
      "Did dueling me help you?"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
