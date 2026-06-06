#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_06: map 26 state 6 */

LOAD_SPRITE(1, SPRITE_MAI)
LOAD_SPRITE(2, SPRITE_ARKANA)
LOAD_SPRITE(3, SPRITE_NEO_GHOUL)
LOAD_SPRITE(4, SPRITE_NEO_GHOUL)
LOAD_SPRITE(5, SPRITE_RICH_HUSBAND)
LOAD_SPRITE(6, SPRITE_RICHE_WIFE)
PLAY_MUSIC(MUSIC_407)
DELAY(16)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, PORTRAIT_LEFT)
TEXT
(
    "Harpie Lady!\n\n"
)
PLAY_MUSIC(MUSIC_333)
SHOW_OVERWORLD_GRAPHIC(GRAPHIC_HARPIE_LADY_SISTERS_FULL_ART)
DELAY(16)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, PORTRAIT_LEFT)
TEXT
(
    "Harpies' Triangle Ecstasy!\n\n"
)
PLAY_MUSIC(MUSIC_341)
SHOW_OVERWORLD_GRAPHIC(GRAPHIC_HARPIE_LADY_SISTERS_ATTACK)
DELAY(16)
PLAY_MUSIC(MUSIC_284)
SLIDE_OBJECT(3, 1, 8)
PLAY_MUSIC(MUSIC_282)
OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_TELEPORT)
SHOW_OBJECT(3, 128, 96, 0, 0, 0)
DELAY(16)
PORTRAIT(PORTRAIT_ARCANA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Hyahahahaha! Nice attack...\n\n"
    "But how much longer can you\n"
    "keep this up?\n\n"
    "Go!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_Y(4, 24)
MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
SET_OBJECT_POSITION(3, 0, 52, 0)
WALK_OBJECT_X(3, 24)
WALK_OBJECT_Y(3, 32)
WALK_OBJECT_X(3, 84)
DELAY(16)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, PORTRAIT_LEFT)
TEXT
(
    "Grr... There's too many of\n"
    "them...\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_Y(0, 70)
WALK_OBJECT_X(0, 21)
WALK_OBJECT_Y(0, 30)
WALK_OBJECT_X(0, 40)
WALK_OBJECT_Y(13, 70)
WALK_OBJECT_X(13, 21)
WALK_OBJECT_Y(13, 36)
WALK_OBJECT_X(13, 30)
WALK_OBJECT_Y(14, 70)
WALK_OBJECT_X(14, 21)
WALK_OBJECT_Y(14, 36)
WALK_OBJECT_X(14, 30)
WALK_OBJECT_Y(14, 24)
WALK_OBJECT_X(14, 30)
DELAY(8)
PLAY_MUSIC(MUSIC_271)
REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2)
DELAY(8)
PLAY_MUSIC(MUSIC_407)
MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
MOVE_OBJECT(3, DIRECTION_LEFT, 0, 0)
MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
DELAY(16)
PORTRAIT(PORTRAIT_ARCANA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Hyahahahaha! How good of you\n"
    "to visit!\n\n"
    "What's the fun without a\n"
    "captive audience!\n\n"
    "I'll give you two choices.\n\n"
    "Do nothing but watch this\n"
    "stunning show as I defeat\n\n"
    "this woman...\n\n"
    "Or step in and be magically\n"
    "defeated by me!\n\n"
    "Hyahahahahaha!\n\n"
    "Whichever choice you make,\n"
    "I win!\n\n"
    "Hyahahahaha!\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
PORTRAIT(PORTRAIT_ARCANA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Are you that anxious to be\n"
    "humiliated?!\n\n"
    "I will have you begging on\n"
    "your knees before it's\n\n"
    "over!\n\n"
    "I, Arkana, accept your\n"
    "challenge!\n\n"
)
DUEL(DUELIST_ARCANA_156)
PLAY_MUSIC(MUSIC_407)
PORTRAIT(PORTRAIT_ARCANA, EXPRESSION_ARKANA_DEFEATED, PORTRAIT_LEFT)
TEXT
(
    "Wh-what? I lost? The great\n"
    "Arkana lost?\n\n"
    "Hyahahahaha! This simply\n"
    "cannot be!\n\n"
    "This must be a mistake!\n"
    "Hyahahahaha!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(2, 102)
WALK_OBJECT_Y(2, 68)
WALK_OBJECT_X(2, 60)
WALK_OBJECT_Y(2, 96)
WALK_OBJECT_X(3, 102)
WALK_OBJECT_Y(3, 68)
WALK_OBJECT_X(3, 60)
WALK_OBJECT_Y(3, 96)
WALK_OBJECT_Y(4, 32)
WALK_OBJECT_X(4, 102)
WALK_OBJECT_Y(4, 68)
WALK_OBJECT_X(4, 60)
WALK_OBJECT_Y(4, 96)
HIDE_PORTRAIT()
FADE_MUSIC(2)
DELAY(32)
WALK_OBJECT_Y(1, 32)
WALK_OBJECT_X(1, 72)
DELAY(16)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "You came here to save me?\n\n"
)
PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT
(
    "Thanks. I couldn't have done\n"
    "it without you.\n\n"
)
TEXT
(
    "So what exactly brings you\n"
    "out here?\n\n"
    "Did you want to see me about\n"
    "something?\n\n"
)
PLAY_MUSIC(MUSIC_332)
FADE_SCREEN(4)
PLAY_MUSIC(MUSIC_702)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, PORTRAIT_LEFT)
TEXT
(
    "What! Those creeps...\n\n"
    "The Neo Ghouls are\n"
    "destroying the city?\n\n"
    "I won't let those cheaters\n"
    "get away with it!\n\n"
    "All right, I'll help.\n\n"
    "We'll show them what a\n"
    "real duelist is all about!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(1, 102)
WALK_OBJECT_Y(1, 68)
WALK_OBJECT_X(1, 60)
WALK_OBJECT_Y(1, 96)
SET_FLAG(EVENT_FLAG_DEFEATED_ARKANA)
CONDITION_CHECK(0)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
TEXT
(
    "Okay! Let's go find another\n"
    "ally!\n\n"
)
HIDE_PORTRAIT()
FADE_MUSIC(2)
DELAY(32)

EVENT_SCRIPT_REPLACEMENT(0x08EA3D40, map_26_state_06_08EA3D40, 0x08F04040, 0x08F04040)
PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT)
  TEXT
  (
      "Okay! We should also get\n"
      "back to the Town of Domino!\n\n"
  )
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_FOUND_ALL_ALLIES)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D28, map_26_state_06_08EA3D28, 0x08EA3D34, 0x08F04040)
PORTRAIT(PORTRAIT_MAI, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Well, I didn't really need\n"
      "your help, anyway.\n\n"
      "I could've beaten the Neo\n"
      "Ghouls by myself!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D04, map_26_state_06_08EA3D04, 0x08EA3D10, 0x08F0404C)
PORTRAIT(PORTRAIT_ARCANA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "You must be joking.\n\n"
      "You're demanding that I beg\n"
      "you for forgiveness?\n\n"
      "Hyahahahaha! Whatever!\n\n"
      "You're about to witness my\n"
      "dazzling duel skills!\n\n"
      "Prepare for Arkana's most\n"
      "exhilarating performance\n\n"
      "yet!\n\n"
  )
  DUEL(DUELIST_ARCANA_156)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D58, map_26_state_06_08EA3D58, 0x08F04040, 0x08F04040)
TEXT
  (
      "The Neo Ghouls are\n"
      "frightening individuals\n\n"
      "indeed.\n\n"
      "If it weren't for Mai, my\n"
      "rare cards would be gone.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D64, map_26_state_06_08EA3D64, 0x08F04040, 0x08F04040)
TEXT
  (
      "Oh, no. No more duels for\n"
      "me, thank you kindly.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D70, map_26_state_06_08EA3D70, 0x08F04040, 0x08F04040)
TEXT
  (
      "How could we be attacked by\n"
      "the Neo Ghouls?\n\n"
      "Dear me, this ship's\n"
      "security is not up to\n\n"
      "snuff.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D7C, map_26_state_06_08EA3D7C, 0x08F04040, 0x08F04040)
TEXT
  (
      "I'm sorry, the idea doesn't\n"
      "enthuse me.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
