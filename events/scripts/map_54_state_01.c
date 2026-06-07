#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_54_state_01: map 54 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EE9C24, map_54_state_01_08EE9C24, 0x08EE9C30, 0x08EE9C3C)
  LOAD_SPRITE(1, SPRITE_SETO)
  LOAD_SPRITE(2, SPRITE_ISHIZU)
  LOAD_SPRITE(3, SPRITE_MOKUBA)
  LOAD_SPRITE(4, SPRITE_CHEVALIER)
  LOAD_SPRITE(5, SPRITE_VIDEO_CARD)
  PLAY_MUSIC(MUSIC_INSIDE_PEGASUS_CASTLE)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Go, Blue-Eyes White Dragon!\n\n"
  )
  PLAY_MUSIC(MUSIC_333)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_BLUE_EYES_WHITE_DRAGON_FULL_ART)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "White Lightning Attack!\n\n"
  )
  PLAY_MUSIC(MUSIC_338)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_BLUE_EYES_ATTACK_BOTTOM_MIDDLE)
  DELAY(16)
  PLAY_MUSIC(MUSIC_284)
  SLIDE_OBJECT(4, 2, 16)
  PLAY_MUSIC(MUSIC_282)
  OBJECT_EFFECT(OBJECT_4, OBJECT_EFFECT_TELEPORT)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Humph. So you finally showed\n"
      "up. But you're too late.\n\n"
      "That Pegasus... I will crush\n"
      "him myself!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(2, 72)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Kaiba... You cannot win\n"
      "alone... One Egyptian God\n\n"
      "Card isn't enough.\n\n"
      "You have no chance.\n\n"
      "Not against Pegasus and\n"
      "Reshef the Dark Being.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My deck is perfect!\n\n"
      "Whoever the opponent may be,\n"
      "defeat isn't in the cards!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  SHOW_OBJECT(3, 60, 18, 0, 0, 0)
  WALK_OBJECT_Y(3, 32)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_1 | OBJECT_2)
  DELAY(8)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_POSSESSED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Then duel me, big brother,\n"
      "with your perfect deck.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 6, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Wh-what? Mokuba? Wh-what are\n"
      "you saying?\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_POSSESSED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Reshef is going to rule this\n"
      "world anyway.\n\n"
      "It's better to quit fighting\n"
      "and accept fate.\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Mokuba's spirit is under\n"
      "control...\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Pegasus! How dare you!\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_POSSESSED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Big brother, will you join\n"
      "me?\n\n"
      "Or would you like to duel?\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 3, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Mokuba...\n\n"
      "I... I can't duel against\n"
      "Mokuba...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(32)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_2)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{PLAYER}, you must duel in\n"
      "Kaiba's place.\n\n"
      "That is the only way to\n"
      "break the mind control over\n\n"
      "Mokuba.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C30, map_54_state_01_08EE9C30, 0x08EE9C48, 0x08F0404C)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_3)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_POSSESSED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Huh? {PLAYER} wants to duel\n"
      "me?\n\n"
      "Sure. You have to ante your\n"
      "Egyptian God Card.\n\n"
      "I don't care who I have to\n"
      "duel as long as I can get\n\n"
      "an Egyptian God Card.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Grr... Mokuba...\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_POSSESSED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Big brother, there's no need\n"
      "to be sad.\n\n"
      "After {PLAYER}, you're next!\n\n"
      "Ahahahahahaha!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_1)
  DELAY(16)
  WALK_OBJECT_Y(0, 52)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_3)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_POSSESSED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't give me that look!\n\n"
      "I'll show you how it feels\n"
      "to lose!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 37)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  WALK_OBJECT_Y(0, 63)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(2, DIRECTION_UP, 0, 0)
  DELAY(16)
  WALK_OBJECT_Y(3, 42)
  DELAY(16)
  DUEL(DUELIST_MOKUBA_119)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C48, map_54_state_01_08EE9C48, 0x08EE9C54, 0x08F0404C)
  PLAY_MUSIC(MUSIC_369)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Arrggh! M-my head! Seto, it\n"
      "hurts!\n\n"
      "Help me, Seto!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, 6, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Mokuba!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(1, 54)
  WALK_OBJECT_X(1, 60)
  WALK_OBJECT_Y(1, 50)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Mokuba, have you regained\n"
      "your senses?\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Seto... I... I...\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't say another word. It's\n"
      "over, Mokuba.\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Big brother...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 34)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  WALK_OBJECT_Y(3, 37)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  WALK_OBJECT_X(3, 68)
  MOVE_OBJECT(3, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_405)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I hate to say this, but I\n"
      "owe you one.\n\n"
      "You have to duel Pegasus\n"
      "next...\n\n"
      "You need my Egyptian God\n"
      "Card, don't you?\n\n"
      "Fine... I could just hand it\n"
      "to you....\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_2)
  DELAY(8)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Kaiba...\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But you and I are duelists.\n\n"
      "Therefore, the only way you\n"
      "can get my card is in a\n\n"
      "duel!\n\n"
      "That's all that needs to be\n"
      "said.\n\n"
      "Now, come on, {PLAYER}.\n\n"
      "My strongest monster will\n"
      "annhilate you!\n\n"
      "Obelisk the Tormentor will\n"
      "decide the outcome!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(1, 42)
  DELAY(32)
  DUEL(DUELIST_SETO_120)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C54, map_54_state_01_08EE9C54, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Urrrgh...\n\n"
  )
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Your powers were evenly\n"
      "matched...\n\n"
      "But {PLAYER}'s pure spirit\n"
      "won the duel.\n\n"
      "He also received the help of\n"
      "his fellow duelists...\n\n"
      "Perhaps his pure spirit can\n"
      "counter the Dark Being.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "There's nothing for me to\n"
      "say.\n\n"
      "You earned this card.\n\n"
      "I don't care if you duel\n"
      "Pegasus or Reshef...\n\n"
      "Just don't lose using my\n"
      "best card!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(5, 60, 46, 0, 0, 0)
  DELAY(32)
  PLAY_MUSIC(MUSIC_286)
  SLIDE_OBJECT(5, 0, 16)
  DELAY(32)
  SHOW_OBJECT(5, 128, 96, 0, 0, 0)
  DELAY(32)
  TEXT
  (
      "Received Obelisk the\n"
      "Tormentor!"
  )
  PLAY_MUSIC(MUSIC_701)
  DELAY(240)
  DELAY(80)
  PAGE_BREAK()
  ADD_CARD(234)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Come, {PLAYER}, we must go.\n\n"
      "The time has come to seal\n"
      "Reshef the Dark Being.\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_DEFEATED_KAIBA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C3C, map_54_state_01_08EE9C3C, 0x08EE9C30, 0x08EE9C3C)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But... If you refuse...\n\n"
      "Reshef the Dark Being will\n"
      "rule the world.\n\n"
      "Please, {PLAYER}!\n\n"
      "You must duel in Kaiba's\n"
      "place!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C60, map_54_state_01_08EE9C60, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hurry up and beat Pegasus.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C78, map_54_state_01_08EE9C78, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Come, {PLAYER}, we must go.\n\n"
      "The time has come to seal\n"
      "Reshef the Dark Being.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE9C6C, map_54_state_01_08EE9C6C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
