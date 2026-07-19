#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_22_state_08: map 22 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E8CBB8, map_22_state_08_08E8CBB8, 0x08E8CBC4, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_SETO)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  LOAD_SPRITE(3, SPRITE_PARA)
  LOAD_SPRITE(4, SPRITE_DOX_FLIPPING)
  LOAD_SPRITE(5, SPRITE_ISHIZU)
  LOAD_SPRITE(6, SPRITE_MILLENNIUM_GUARDIAN)
  PLAY_MUSIC(MUSIC_405)
  DELAY(32)
  WALK_OBJECT_X(2, 52)
  DELAY(16)
  TALK(PORTRAIT_MOKUBA,
      "Big brother!",
      "Most of the Neo Ghouls have left the Town of Domino."
  )
  TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Good.")
  TALK(PORTRAIT_MOKUBA,
      "I protected KaibaCorp, just like you told me.",
      "So you don't have to worry about a thing."
  )
  TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Good work, Mokuba.")
  TALK(PORTRAIT_MOKUBA,
      "Heheh, thanks. You know I'll do anything for you.",
      "So, anything new with your Egyptian God Card?"
  )
  TALK(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Somehow, it's back to normal.")
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(32)
  TALK(PORTRAIT_SETO, "I don't know what they did, but...")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBC4, map_22_state_08_08E8CBC4, 0x08E8CBD0, EVENT_NOP)
  PLAY_MUSIC(MUSIC_404)
  WALK_OBJECT_X(4, 48)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SURPRISED, "Urk! S-Seto...")
  HIDE_PORTRAIT()
  DELAY(8)
  SET_OBJECT_POSITION(2, 128, 96, 0)
  PLAY_MUSIC(MUSIC_314)
  LOAD_SPRITE(4, SPRITE_DOX_WITH_MOKUBA)
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  DELAY(8)
  TALK(PORTRAIT_SETO, 6, PORTRAIT_RIGHT, "How dare you... What's the meaning of this?")
  TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY,
      "Seto Kaiba! I have a message from Master Chevalsky!",
      "Come to my castle.",
      "If you want to save your dear brother.",
      "You have no choice but to come to my castle!"
  )
  TALK(PORTRAIT_SETO, 5, PORTRAIT_RIGHT, "You worm!")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
  PLAY_MUSIC(MUSIC_277)
  SLIDE_OBJECT(4, 1, 8)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBD0, map_22_state_08_08E8CBD0, 0x08E8CBDC, EVENT_NOP)
  DELAY(16)
  SET_OBJECT_POSITION(3, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(3, 24)
  WALK_OBJECT_X(3, 80)
  DELAY(16)
  TALK(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT,
      "Younger brother, you have fulfilled your mission!",
      "Master Chevalsky will promote you to a higher",
      "position!"
  )
  TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY,
      "Elder brother, you also have done your job with most",
      "excellence!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(32)
  MOVE_OBJECT(1, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_SETO, 2, PORTRAIT_RIGHT, "You punks! How dare you mock me!")
  TALK(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT, "Fufufufufufu...")
  TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, "Fufufufufufu...")
  TALK(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Master Chevalsky demands your presence, Kaiba!")
  TALK(PORTRAIT_DOX, "Come to Master Chevalsky's castle!")
  TALK(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_RIGHT, "The castle that you...")
  TALK(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, "...Know so well! Fufufu...")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_315)
  SLIDE_OBJECT(3, 1, 96)
  PLAY_MUSIC(MUSIC_315)
  SLIDE_OBJECT(4, 1, 64)
  DELAY(16)
  TALK(PORTRAIT_SETO, 2, PORTRAIT_RIGHT, "Mokuba!")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 4, 0)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBDC, map_22_state_08_08E8CBDC, 0x08E8CBE8, 0x08E8CBF4)
  SET_OBJECT_POSITION(0, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(0, 24)
  WALK_OBJECT_X(0, 82)
  DELAY(16)
  SET_OBJECT_POSITION(13, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(13, 18)
  WALK_OBJECT_X(13, 87)
  DELAY(16)
  SET_OBJECT_POSITION(14, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(14, 30)
  WALK_OBJECT_X(14, 87)
  DELAY(16)
  SET_OBJECT_POSITION(5, 95, 16, 0)
  DELAY(16)
  WALK_OBJECT_Y(5, 24)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  WALK_OBJECT_X(0, 77)
  DELAY(16)
  TEXT("{CARD_1}Let us help!\nLend us your God Card!{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBE8, map_22_state_08_08E8CBE8, 0x08E8CC00, EVENT_NOP)
  TALK(PORTRAIT_ISHIZU,
      "{PLAYER} is right, Kaiba.",
      "Now is the time for teamwork.",
      "The Dark Being must be sealed again..."
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_SETO, 2,
      "Quiet, you!",
      "I'm never going to cooperate with you!",
      "I'll crush Pegasus on my own and get Mokuba back!",
      "How many times do I have to say that I don't have time",
      "for your so-called ancient magic!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CC00, map_22_state_08_08E8CC00, EVENT_NOP, EVENT_NOP)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 0)
  SET_OBJECT_POSITION(1, 128, 96, 0)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU, "We're left with no choice.")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU,
      "We must also go to Sol Chevalsky's... I mean...",
      "We must also go to Pegasus's castle."
  )
  TALK(PORTRAIT_JOEY, "But who knows where the castle is?")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_5 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  PLAY_MUSIC(MUSIC_402)
  WALK_OBJECT_X(6, 48)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_5)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_MILLENIUM_GUADIAN,
      "You have proven yourselves to the Millennium Items.",
      "Trace the flow of time and accept your destiny.",
      "One man knows where you must go.",
      "You must seek out Paradox."
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_MILLENIUM_GUADIAN,
      "Paradox awaits you in China.",
      "He will show you the way."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(6, DIRECTION_LEFT, 64, 0)
  DELAY(32)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_ISHIZU,
      "The Millennium Guard comes from the order that",
      "protects the Millennium Items...",
      "I sensed that he was telling the truth.",
      "{PLAYER}, you must go to China.",
      "As soon as possible."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  WALK_OBJECT_X(5, 0)
  SET_OBJECT_POSITION(5, 128, 96, 0)
  TALK(PORTRAIT_YUGI,
      "I'm worried about Mokuba and Kaiba...",
      "We'd better find Pegasus's castle quickly."
  )
  TALK(PORTRAIT_JOEY,
      "Yugi's right.",
      "If this Parachute guy can help us...",
      "We'd betta find him quick."
  )
  TALK(PORTRAIT_YUGI,
      "That's Paradox, Joey. Not Parachute.",
      "{PLAYER}, let's go! We're off to China!"
  )
  HIDE_PORTRAIT()
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  SET_FLAG(EVENT_FLAG_SAW_MOKUBA_GET_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E8CBF4, map_22_state_08_08E8CBF4, 0x08E8CC00, EVENT_NOP)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_SETO, 2,
      "Don't make me laugh, {PLAYER}!",
      "Reshef the Dark Being... The end of the world...",
      "You've been reading too many fantasy novels!",
      "You guys do what you want!",
      "But I'll get Mokuba back on my own!",
      "And nobody is going to stop me!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
