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

EVENT_SCRIPT_REPLACEMENT(0x08E34A0C, map_00_state_02_08E34A0C, 0x08E34A18, EVENT_NOP)
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
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I am glad that you have returned safely.",
      "I see that you have obtained the Millennium Necklace.",
      "Unfortunately, it is not sufficient...",
      "A single Millennium Item does not have enough power.",
      "Not enough to restore the Egyptian God Cards from",
      "stone.",
      "The next Millennium Item..."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_X(2, 96)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_ISHIZU_SURPRISED, PORTRAIT_POSITION_AUTO, "W-what is this presence I'm feeling?")
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
  TALK(PORTRAIT_PUPPETEER_OF_DOOM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "I am the Puppeteer of Doom!",
      "I won't let you meddle with Master Chevalsky's plans!",
      "Duel!"
  )
  DUEL(DUELIST_PUPPETEER_OF_DOOM_155)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A24, map_00_state_02_08E34A24, 0x08E34A30, EVENT_NOP)
  SET_FLAG(EVENT_FLAG_DEFEATED_PUPPETEER_OF_DOOM)
  TALK(PORTRAIT_PUPPETEER_OF_DOOM, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Gah! Don't get all cocky just because you beat me!",
      "This is an invitation for a challenge from Master Sol",
      "Chevalsky!"
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
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "This card... It's a video card.")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Try setting it in your Duel Disk, {PLAYER}.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A30, map_00_state_02_08E34A30, 0x08E34A48, 0x08E34A3C)
  TALK(PORTRAIT_NONE, "{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A48, map_00_state_02_08E34A48, EVENT_NOP, EVENT_NOP)
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
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_POSITION_AUTO,
      "Bravo! I say bravissimo! Congratulations!",
      "I guess that both my agents have failed me!",
      "Hahaha! I had a feeling you guys will be a thorn in my",
      "side!",
      "But why fret when I can make a game out of this!",
      "Here are the rules. Let's see you turn the Egyptian",
      "God Cards back from stone...",
      "And bring them to my castle before time runs out!",
      "If you don't make it in time, I can't vouch for",
      "what happens to the world!",
      "How does that sound? Ahahahahaha!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_289)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_TELEPORT)
  DELAY(64)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "He resurrected Reshef the Dark Being...")
  FADE_SCREEN(8)
  CUTSCENE(1)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTHWEST, 18, 3, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A3C, map_00_state_02_08E34A3C, 0x08E34A30, EVENT_NOP)
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Don't you want to know about this mysterious Sol",
      "Chevalsky?",
      "This card doesn't look dangerous, so let's check",
      "it out!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08F0404C, map_00_state_02_08F0404C, EVENT_NOP, EVENT_NOP)
  RESTORE_LIFE_POINTS()
  WARP(LOCATION_PLAYER_HOUSE_INSIDE, 0, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A84, map_00_state_02_08E34A84, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "In order to imprison the Dark Being resurrected by",
      "Sol Chevalsky...",
      "We need the Egyptian God Cards.",
      "We must restore the Egyptian God Cards from stone.",
      "But in order to do so, we require the Millennium",
      "Items.",
      "The second Millennium Item is aboard a cruise ship.",
      "The ship should be docked at Domino Pier."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A00, map_00_state_02_08E34A00, 0x08E34A0C, 0x08E34A90)
  CHECK_FLAG(EVENT_FLAG_DEFEATED_PUPPETEER_OF_DOOM)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E34A90, map_00_state_02_08E34A90, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Please. Hurry to the cruise ship.",
      "Reshef the Dark Being will soon engulf the world."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
