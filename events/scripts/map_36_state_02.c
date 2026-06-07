#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_36_state_02: map 36 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EC9C54, map_36_state_02_08EC9C54, 0x08EC9C60, 0x08EC9C6C)
  LOAD_SPRITE(1, SPRITE_REX)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_REX3)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C60, map_36_state_02_08EC9C60, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Looks like we can't get rid\n"
    "of each other.\n\n"
    "You're not here to watch\n"
    "them dig up fossils, am I\n\n"
    "right?\n\n"
    "I can tell from the looks on\n"
    "your faces.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C6C, map_36_state_02_08EC9C6C, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You're planning to fight\n"
    "someone as powerful as a\n\n"
    "T-Rex.\n\n"
    "It was obvious from the way\n"
    "you dueled.\n\n"
    "It must be tough to keep\n"
    "your skills sharp.\n\n"
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
    "It sounds crazy, but I guess\n"
    "we're connected to each\n\n"
    "other.\n\n"
    "I wonder why...\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "There must be a bond between\n"
    "duelists.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Alright, enough talk.\n\n"
    "Because action speaks louder\n"
    "than words.\n\n"
    "Let's duel!\n\n"
)
  DUEL(DUELIST_REX_102)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9C90, map_36_state_02_08EC9C90, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_245)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "That's it! You win!\n\n"
    "{PLAYER}, you've grown\n"
    "pretty strong.\n\n"
    "Don't you dare lose to\n"
    "anyone!\n\n"
    "I don't want anyone to think\n"
    "that you're weak.\n\n"
    "Not after you've beaten me!\n\n"
    "All right, take this card.\n\n"
    "It's Two-Headed King Rex.\n\n"
    "The card that best\n"
    "represents me is Red-Eyes\n\n"
    "B. Dragon...\n\n"
    "...Is what I'd like to say,\n"
    "but it's now Wheeler's\n\n"
    "card.\n\n"
    "Since the day he won it from\n"
    "me, I realized something.\n\n"
    "Are expensive rare cards\n"
    "really good for me?\n\n"
    "The more I thought about it,\n"
    "this card I have right now\n\n"
    "is perfect for me.\n\n"
    "It's a common card, but it\n"
    "embodies my spirit!\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Received Two-Headed King\n"
    "Rex."
)
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
    "I don't know if it's worth\n"
    "dueling me.\n\n"
    "Especially considering what\n"
    "you're facing.\n\n"
    "But maybe I'll teach you\n"
    "something!\n\n"
    "I'll duel using all my\n"
    "techniques.\n\n"
    "If it means helping you,\n"
    "{PLAYER}, I'll do it!\n\n"
)
  DUEL(DUELIST_REX_149)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EC9CA8, map_36_state_02_08EC9CA8, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_245)
  TALK(PORTRAIT_REX, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Well, how was I?\n\n"
    "Did dueling me help you?\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
