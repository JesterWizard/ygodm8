#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_26_state_06: map 26 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08EA3CEC, map_26_state_06_08EA3CEC, 0x08EA3CF8, 0x08EA3D04)
  LOAD_SPRITE(1, SPRITE_MAI)
  LOAD_SPRITE(2, SPRITE_ARKANA)
  LOAD_SPRITE(3, SPRITE_NEO_GHOUL)
  LOAD_SPRITE(4, SPRITE_NEO_GHOUL)
  LOAD_SPRITE(5, SPRITE_RICH_HUSBAND)
  LOAD_SPRITE(6, SPRITE_RICHE_WIFE)
  PLAY_MUSIC(MUSIC_407)
  DELAY(16)
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, "Harpie Lady!")
  PLAY_MUSIC(MUSIC_333)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_HARPIE_LADY_SISTERS_FULL_ART)
  DELAY(16)
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, "Harpies' Triangle Ecstasy!")
  PLAY_MUSIC(MUSIC_341)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_HARPIE_LADY_SISTERS_ATTACK)
  DELAY(16)
  PLAY_MUSIC(MUSIC_284)
  SLIDE_OBJECT(3, 1, 8)
  PLAY_MUSIC(MUSIC_282)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_TELEPORT)
  SHOW_OBJECT(3, 128, 96, 0, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_ARCANA,
      "Hyahahahaha! Nice attack...",
      "But how much longer can you keep this up?",
      "Go!"
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
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY, "Grr... There's too many of them...")
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
  TALK(PORTRAIT_ARCANA,
      "Hyahahahaha! How good of you to visit!",
      "What's the fun without a captive audience!",
      "I'll give you two choices.",
      "Do nothing but watch this stunning show as I defeat",
      "this woman...",
      "Or step in and be magically defeated by me!",
      "Hyahahahahaha!",
      "Whichever choice you make, I win!",
      "Hyahahahaha!"
  )
  TALK(PORTRAIT_NONE, "{CARD_1}I'm going to win!\nI'll let you surrender.{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3CF8, map_26_state_06_08EA3CF8, 0x08EA3D10, 0x08F0404C)
  TALK(PORTRAIT_ARCANA,
      "Are you that anxious to be humiliated?!",
      "I will have you begging on your knees before it's",
      "over!",
      "I, Arkana, accept your challenge!"
  )
  DUEL(DUELIST_ARCANA_156)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D10, map_26_state_06_08EA3D10, 0x08EA3D1C, 0x08EA3D28)
  PLAY_MUSIC(MUSIC_407)
  TALK(PORTRAIT_ARCANA, EXPRESSION_ARKANA_DEFEATED,
      "Wh-what? I lost? The great Arkana lost?",
      "Hyahahahaha! This simply cannot be!",
      "This must be a mistake! Hyahahahaha!"
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
  TALK(PORTRAIT_MAI, "You came here to save me?")
  TALK(PORTRAIT_NONE, "{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D1C, map_26_state_06_08EA3D1C, 0x08EA3D34, EVENT_NOP)
  TALK(PORTRAIT_MAI, "Thanks. I couldn't have done it without you.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D34, map_26_state_06_08EA3D34, 0x08EA3D4C, 0x08EA3D40)
  TEXT(
      "So what exactly brings you out here?",
      "Did you want to see me about something?"
  )
  PLAY_MUSIC(MUSIC_332)
  FADE_SCREEN(4)
  PLAY_MUSIC(MUSIC_702)
  TALK(PORTRAIT_MAI, EXPRESSION_MAI_ANGRY,
      "What! Those creeps...",
      "The Neo Ghouls are destroying the city?",
      "I won't let those cheaters get away with it!",
      "All right, I'll help.",
      "We'll show them what a real duelist is all about!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 102)
  WALK_OBJECT_Y(1, 68)
  WALK_OBJECT_X(1, 60)
  WALK_OBJECT_Y(1, 96)
  SET_FLAG(EVENT_FLAG_DEFEATED_ARKANA)
  CONDITION_CHECK(0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D4C, map_26_state_06_08EA3D4C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Okay! Let's go find another ally!")
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D40, map_26_state_06_08EA3D40, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Okay! We should also get back to the Town of Domino!")
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_FOUND_ALL_ALLIES)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D28, map_26_state_06_08EA3D28, 0x08EA3D34, EVENT_NOP)
  TALK(PORTRAIT_MAI,
      "Well, I didn't really need your help, anyway.",
      "I could've beaten the Neo Ghouls by myself!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D04, map_26_state_06_08EA3D04, 0x08EA3D10, 0x08F0404C)
  TALK(PORTRAIT_ARCANA,
      "You must be joking.",
      "You're demanding that I beg you for forgiveness?",
      "Hyahahahaha! Whatever!",
      "You're about to witness my dazzling duel skills!",
      "Prepare for Arkana's most exhilarating performance",
      "yet!"
  )
  DUEL(DUELIST_ARCANA_156)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D58, map_26_state_06_08EA3D58, EVENT_NOP, EVENT_NOP)
  TEXT(
      "The Neo Ghouls are frightening individuals",
      "indeed.",
      "If it weren't for Mai, my rare cards would be gone."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D64, map_26_state_06_08EA3D64, EVENT_NOP, EVENT_NOP)
  TEXT("Oh, no. No more duels for me, thank you kindly.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D70, map_26_state_06_08EA3D70, EVENT_NOP, EVENT_NOP)
  TEXT(
      "How could we be attacked by the Neo Ghouls?",
      "Dear me, this ship's security is not up to",
      "snuff."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EA3D7C, map_26_state_06_08EA3D7C, EVENT_NOP, EVENT_NOP)
  TEXT("I'm sorry, the idea doesn't enthuse me.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
