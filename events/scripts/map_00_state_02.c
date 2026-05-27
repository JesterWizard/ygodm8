#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_02: map 0 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08E349F4, map_00_state_02_08E349F4, 0x08E34A0C, 0x08E34A84)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_PUPPETEER_OF_DOOM)
  LOAD_SPRITE(3, SPRITE_PEGASUS)
  LOAD_SPRITE(4, SPRITE_VIDEO_CARD)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_PUPPETEER_OF_DOOM)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A0C, map_00_state_02_08E34A0C, 0x08E34A18, 0x08F04040)
  WALK_OBJECT_Y(0, 29)
  WALK_OBJECT_X(0, 48)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_Y(13, 39)
  WALK_OBJECT_X(13, 54)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 39)
  WALK_OBJECT_X(14, 42)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A18, map_00_state_02_08E34A18, 0x08E34A24, 0x08F0404C)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_ISHIZU_ISHTAR)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I am glad that you have\n"
      "returned safely.\n\n"
      "I see that you have obtained\n"
      "the Millennium Necklace.\n\n"
      "Unfortunately, it is not\n"
      "sufficient...\n\n"
      "A single Millennium Item\n"
      "does not have enough power.\n\n"
      "Not enough to restore the\n"
      "Egyptian God Cards from\n\n"
      "stone.\n\n"
      "The next Millennium Item...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_X(2, 96)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_SURPRISED, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "W-what is this presence I'm\n"
      "feeling?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  WALK_OBJECT_Y(2, 29)
  WALK_OBJECT_X(2, 68)
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_403)
  PORTRAIT(PORTRAIT_PUPPETEER_OF_DOOM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I am the Puppeteer of Doom!\n\n"
      "I won't let you meddle with\n"
      "Master Chevalsky's plans!\n\n"
      "Duel!\n\n"
  )
  DUEL(DUELIST_PUPPETEER_OF_DOOM_155)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A24, map_00_state_02_08E34A24, 0x08E34A30, 0x08F04040)
  SET_FLAG(EVENT_FLAG_DEFEATED_PUPPETEER_OF_DOOM)
  PORTRAIT(PORTRAIT_PUPPETEER_OF_DOOM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Gah! Don't get all cocky\n"
      "just because you beat me!\n\n"
      "This is an invitation for a\n"
      "challenge from Master Sol\n\n"
      "Chevalsky!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_285)
  SHOW_OBJECT(4, 64, 30, 0, 0, 0)
  DELAY(32)
  PLAY_MUSIC(MUSIC_286)
  SLIDE_OBJECT(4, 1, 12)
  DELAY(16)
  WALK_OBJECT_X(2, 96)
  WALK_OBJECT_Y(2, 40)
  WALK_OBJECT_X(2, 128)
  DELAY(16)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "This card... It's a video\n"
      "card.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Try setting it in your Duel\n"
      "Disk, {PLAYER}.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A30, map_00_state_02_08E34A30, 0x08E34A48, 0x08E34A3C)
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A48, map_00_state_02_08E34A48, 0x08F04040, 0x08F04040)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  SHOW_OBJECT(4, 128, 96, 0, 0, 0)
  PLAY_MUSIC(MUSIC_287)
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  DELAY(64)
  PLAY_MUSIC(MUSIC_288)
  SHOW_OBJECT(3, 62, 29, 0, 1, 0)
  PLAY_MUSIC(MUSIC_413)
  PORTRAIT(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Bravo! I say bravissimo!\n"
      "Congratulations!\n\n"
      "I guess that both my agents\n"
      "have failed me!\n\n"
      "Hahaha! I had a feeling you\n"
      "guys will be a thorn in my\n\n"
      "side!\n\n"
      "But why fret when I can make\n"
      "a game out of this!\n\n"
      "Here are the rules. Let's\n"
      "see you turn the Egyptian\n\n"
      "God Cards back from stone...\n\n"
      "And bring them to my castle\n"
      "before time runs out!\n\n"
      "If you don't make it in\n"
      "time, I can't vouch for\n\n"
      "what happens to the world!\n\n"
      "How does that sound?\n"
      "Ahahahahaha!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_289)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_TELEPORT)
  DELAY(64)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "He resurrected Reshef the\n"
      "Dark Being...\n\n"
  )
  FADE_SCREEN(8)
  CUTSCENE(1)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTHWEST, 18, 3, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A3C, map_00_state_02_08E34A3C, 0x08E34A30, 0x08F04040)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Don't you want to know about\n"
      "this mysterious Sol\n\n"
      "Chevalsky?\n\n"
      "This card doesn't look\n"
      "dangerous, so let's check\n\n"
      "it out!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F0404C, map_00_state_02_08F0404C, 0x08F04040, 0x08F04040)
  RESTORE_LIFE_POINTS()
  WARP(LOCATION_PLAYER_HOUSE_INSIDE, 0, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A84, map_00_state_02_08E34A84, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "In order to imprison the\n"
      "Dark Being resurrected by\n\n"
      "Sol Chevalsky...\n\n"
      "We need the Egyptian God\n"
      "Cards.\n\n"
      "We must restore the Egyptian\n"
      "God Cards from stone.\n\n"
      "But in order to do so, we\n"
      "require the Millennium\n\n"
      "Items.\n\n"
      "The second Millennium Item\n"
      "is aboard a cruise ship.\n\n"
      "The ship should be docked at\n"
      "Domino Pier.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A00, map_00_state_02_08E34A00, 0x08E34A0C, 0x08E34A90)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_PUPPETEER_OF_DOOM)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A90, map_00_state_02_08E34A90, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Please. Hurry to the cruise\n"
      "ship.\n\n"
      "Reshef the Dark Being will\n"
      "soon engulf the world.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
