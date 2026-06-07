#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_12: map 12 state 12 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F138, map_12_state_12_08E6F138, 0x08E6F144, 0x08E6F150)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  LOAD_SPRITE(3, SPRITE_SETO)
  LOAD_SPRITE(4, SPRITE_REBECCA)
  LOAD_SPRITE(5, SPRITE_TEDDY)
  PLAY_MUSIC(MUSIC_HAPPY_CUTSCENE)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 8, 0)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 8, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 8, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_4, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You're Seto Kaiba, aren't\n"
      "you?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_13)
  DELAY(8)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Who are you? You're not very\n"
      "polite.\n\n"
  )
  PORTRAIT(PORTRAIT_REBECCA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'm Rebecca.\n\n"
      "And this is my friend Teddy.\n\n"
  )
  HIDE_PORTRAIT()
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "A stuffed animal is your\n"
      "friend?\n\n"
  )
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Be quiet! Teddy's not a\n"
      "stuffed animal!\n\n"
      "Teddy is the best bear in\n"
      "the galaxy! Growl!\n\n"
      "And we know a secret, don't\n"
      "we, Teddy?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(5, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "You're the one who tore up\n"
      "Solomon Muto's card.\n\n"
      "You tore up his Blue-Eyes\n"
      "White Dragon.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "...\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_SAD, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "H-how did you know...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(32)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(32)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My grandfather gave Mr. Muto\n"
      "that card.\n\n"
      "That Blue-Eyes White Dragon\n"
      "was a symbol of their\n\n"
      "friendship, but you tore it\n"
      "up!\n\n"
      "You're not going to get away\n"
      "with that! Right, Teddy?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(5, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "So what do you want me to\n"
      "do?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_MOKUBA_ANGRY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Seto, just ignore her...\n\n"
  )
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I challenge you to a duel!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'll wipe that smirk off\n"
      "your face.\n\n"
      "Because you're facing the\n"
      "United States champion!\n\n"
      "Right, Teddy?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(5, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "U.S. champ? That's it?\n\n"
      "At your duelist level, I can\n"
      "defeat you blindfolded.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, OBJECT_4)
  DELAY(8)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "At my level?! Are you making\n"
      "fun of me?!\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "No, I'm just telling the\n"
      "truth.\n\n"
      "Your skills are nothing but\n"
      "a joke.\n\n"
      "But if you still insist on\n"
      "challenging me...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_3)
  DELAY(8)
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I have a better idea. Duel\n"
      "against {PLAYER}.\n\n"
      "If you can beat him, I'll\n"
      "duel you.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_4 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(5, DIRECTION_DOWN, 0, 0)
  DELAY(8)
  WALK_OBJECT_X(13, 24)
  WALK_OBJECT_Y(13, 48)
  MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  DELAY(48)
  WALK_OBJECT_Y(13, 44)
  WALK_OBJECT_X(13, 30)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(0, 54)
  WALK_OBJECT_X(0, 40)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(14, 54)
  WALK_OBJECT_X(14, 20)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Rebecca, I know you're\n"
      "upset, but there's no point\n\n"
      "attacking Kaiba.\n\n"
  )
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yugi...\n\n"
      "I'm not challenging Kaiba\n"
      "because I'm angry.\n\n"
      "I want to duel him to test\n"
      "my skills.\n\n"
      "Right, Teddy?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(5, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Rebecca...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 2, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_372)
  SHOW_OBJECT(5, 128, 96, 0, 0, 0)
  DELAY(8)
  WALK_OBJECT_X(4, 40)
  WALK_OBJECT_Y(4, 40)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_372)
  SHOW_OBJECT(5, 48, 40, 0, 0, 0)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  DELAY(8)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REBECCA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Hmm... Are you really that\n"
      "strong of a duelist?\n\n"
      "You sure don't look it.\n"
      "Teddy doesn't think so,\n\n"
      "either.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(5, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REBECCA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But I'm still dueling you!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "{CARD_1}Yes\n"
      "No{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F144, map_12_state_12_08E6F144, 0x08E6F15C, 0x08F0404C)
  DUEL(DUELIST_REBECCA_130)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F15C, map_12_state_12_08E6F15C, 0x08F04040, 0x08F04040)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I... I lost?\n\n"
      "Did I really lose? Teddy?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(5, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Humph. That duel was a joke.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(5, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "If you want your revenge,\n"
      "come back when you actually\n\n"
      "pose a challenge.\n\n"
      "You know where to find me!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(3, 0)
  MOVE_OBJECT(3, DIRECTION_LEFT, 16, 0)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Just to let you know, my\n"
      "brother would have finished\n\n"
      "you off in half the number\n"
      "of turns!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(2, 0)
  MOVE_OBJECT(2, DIRECTION_LEFT, 16, 0)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, OBJECT_14)
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_4)
  DELAY(16)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Rebecca...\n\n"
      "I know Kaiba is arrogant and\n"
      "says terrible things, but\n\n"
      "he is a different person.\n\n"
      "The Kaiba you saw today\n"
      "isn't like the Kaiba of\n\n"
      "old.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(64)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I don't care...\n\n"
      "Kaiba's right. Without\n"
      "Pegasus and Bandit Keith,\n\n"
      "America doesn't have the top\n"
      "duelists anymore.\n\n"
      "That's why I came here. To\n"
      "prove that we're still\n\n"
      "pretty good!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(5, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_REBECCA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "But losing to {PLAYER}...\n"
      "That was an eye-opener.\n\n"
      "I should have been training\n"
      "than complaining.\n\n"
      "I'm turning over a new leaf.\n"
      "I'm going to raise my\n\n"
      "duelist level so that I can\n"
      "put the United States back\n\n"
      "on the map!\n\n"
      "Just you wait. I'll beat\n"
      "Kaiba, Yugi, and you.\n\n"
      "Right, Teddy?\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_TEDDY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  DELAY(96)
  HIDE_PORTRAIT()
  DELAY(8)
  MOVE_OBJECT(4, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_HAPPY, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "Yup! And I'll also train so\n"
      "that I won't lose!\n\n"
  )
  PORTRAIT(PORTRAIT_REBECCA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "I'm going home to practice!\n\n"
      "Say bye to Solomon Muto for\n"
      "me!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(4, DIRECTION_RIGHT, 2, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_372)
  SHOW_OBJECT(5, 128, 96, 0, 0, 0)
  DELAY(8)
  WALK_OBJECT_X(4, 0)
  MOVE_OBJECT(4, DIRECTION_LEFT, 16, 0)
  DELAY(16)
  SET_FLAG(EVENT_FLAG_DEFEATED_REBECCA)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F150, map_12_state_12_08E6F150, 0x08E6F15C, 0x08F0404C)
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_4, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TALK(PORTRAIT_REBECCA, 5, PORTRAIT_POSITION_AUTO,
    "Even if you don't want to\n"
    "duel, I do!\n\n"
    "Come on! Or are you chicken!\n\n"
)
  DUEL(DUELIST_REBECCA_130)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F1C8, map_12_state_12_08E6F1C8, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "That girl is no match for\n"
      "Master Seto, but in ten\n\n"
      "years, she will be ready to\n"
      "take on the world.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
