#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_01: map 14 state 1 */

#define LOCALID_STATION_GUARD_1  1
#define LOCALID_STATION_GUARD_2  2
#define LOCALID_STATION_GUARD_3  3

LOAD_SPRITE(LOCALID_STATION_GUARD_1, SPRITE_DOMINO_STATION_GUARD)
LOAD_SPRITE(LOCALID_STATION_GUARD_2, SPRITE_DOMINO_STATION_GUARD)
LOAD_SPRITE(LOCALID_STATION_GUARD_3, SPRITE_DOMINO_STATION_GUARD)
LOAD_SPRITE(4, SPRITE_FENG_LONG)
LOAD_SPRITE(5, SPRITE_NIBBLES)
LOAD_SPRITE(6, SPRITE_PANIK)
CHECK_FLAG(EVENT_FLAG_DEFEATED_DOMINO_STATION_GUARD)
PLAY_MUSIC(MUSIC_230)
DELAY(16)
WALK_OBJECT_Y(LOCALID_STATION_GUARD_3, 32)
DELAY(16)
TEXT
(
    "You're duelists?\n\n"
)
WALK_OBJECT_Y(0, 44)
WALK_OBJECT_Y(13, 54)
WALK_OBJECT_Y(14, 54)
DELAY(16)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_LOCALID(LOCALID_STATION_GUARD_3), OBJECT_EFFECT_JUMPING)
DELAY(8)
TEXT
(
    "Ah, you are? Then please!\n"
    "Step on board!\n\n"
    "Just kidding! It's never\n"
    "that easy.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_Y(LOCALID_STATION_GUARD_2, 32)
DELAY(8)
TEXT
(
    "If you wish to board the\n"
    "Duel Express...\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_LOCALID(LOCALID_STATION_GUARD_3), OBJECT_EFFECT_JUMPING)
DELAY(8)
TEXT
(
    "You'll have to get by us\n"
    "first.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_LOCALID(LOCALID_STATION_GUARD_2), OBJECT_EFFECT_JUMPING)
DELAY(8)
TEXT
(
    "Winning this tag duel is\n"
    "your boarding pass!\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I wasn't expectin' things to\n"
    "be a cakewalk...\n\n"
    "But who woulda imagined a\n"
    "tag duel to test our\n\n"
    "skills?\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(13, DIRECTION_LEFT, 0, 0)
DELAY(16)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Well, I don't think we have\n"
    "a choice.\n\n"
    "There's no way every duelist\n"
    "in the world can fit into\n\n"
    "the train.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
DELAY(16)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I guess dat's true... But in\n"
    "a tag duel, you'll need a\n\n"
    "partner!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
DELAY(16)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "{PLAYER}, who do you want to\n"
    "team up with? Me or Yugi?\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
DELAY(16)
MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
DELAY(16)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Okay! You can count on me,\n"
    "{PLAYER}!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(13, DIRECTION_UP, 4, 0)
WALK_OBJECT_X(13, 43)
WALK_OBJECT_Y(13, 44)
DELAY(16)
MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
DELAY(16)
DUEL(DUELIST_YUGI_159)
PLAY_MUSIC(MUSIC_230)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Gotta hand it to you, Yugi.\n"
    "That duel lasted barely a\n\n"
    "second!\n\n"
    "On the other hand...\n\n"
)
TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP, PORTRAIT_RIGHT,
    "{PLAYER}, you had me\n"
    "worried!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
DELAY(16)
PLAY_MUSIC(MUSIC_274)
REACTION(REACTION_SWEATDROP, OBJECT_0)
DELAY(16)
MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
DELAY(16)
TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I... I couldn't afford to\n"
    "waste any time.\n\n"
    "I have to find the spirit\n"
    "right away!\n\n"
    "But {PLAYER}'s duel was\n"
    "pretty impressive.\n\n"
    "Let's keep this up, guys!\n\n"
)
SET_FLAG(EVENT_FLAG_CHOSE_TO_FIGHT_THE_RIGHT_DOMINO_STATION_GUARD)
HIDE_PORTRAIT()
DELAY(16)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_LOCALID(LOCALID_STATION_GUARD_2), OBJECT_EFFECT_JUMPING)
DELAY(8)
TEXT
(
    "Bravo!\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
MOVE_OBJECT(13, DIRECTION_UP, 0, 0)
MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
DELAY(16)
PLAY_MUSIC(MUSIC_293)
OBJECT_EFFECT(OBJECT_LOCALID(LOCALID_STATION_GUARD_3), OBJECT_EFFECT_JUMPING)
DELAY(8)
TEXT
(
    "Please feel free to board\n"
    "the train.\n\n"
)
HIDE_PORTRAIT()
DELAY(16)
WALK_OBJECT_X(LOCALID_STATION_GUARD_3, 68)
MOVE_OBJECT(LOCALID_STATION_GUARD_3, DIRECTION_LEFT, 0, 0)
WALK_OBJECT_Y(LOCALID_STATION_GUARD_2, 26)
MOVE_OBJECT(LOCALID_STATION_GUARD_2, DIRECTION_DOWN, 0, 0)
SET_FLAG(EVENT_FLAG_DEFEATED_DOMINO_STATION_GUARD)

EVENT_SCRIPT_REPLACEMENT(0x08E77540, map_14_state_01_08E77540, 0x08E7754C, 0x08F0404C)
TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Okay! That was a wise\n"
    "decision, {PLAYER}!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(14, 43)
  WALK_OBJECT_Y(14, 44)
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(16)
  DUEL(DUELIST_YUGI_159)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7754C, map_14_state_01_08E7754C, 0x08E77558, 0x08F04040)
PLAY_MUSIC(MUSIC_230)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "What took ya so long,\n"
    "{PLAYER}!\n\n"
    "If you're having trouble\n"
    "against these guys...\n\n"
    "Well, I'd hate to think\n"
    "what'd happen against some\n\n"
    "real competition.\n\n"
    "Hurry and catch up to my\n"
    "level!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  SET_FLAG(EVENT_FLAG_TAG_DUELED_WITH_JOEY_AGAINST_THE_DOMINO_STATIONS_GUARDS)
  SET_FLAG(EVENT_FLAG_CHOSE_TO_FIGHT_THE_RIGHT_DOMINO_STATION_GUARD)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7757C, map_14_state_01_08E7757C, 0x08F04040, 0x08F04040)
TEXT
  (
      "There's a chartered express\n"
      "train reserved exclusively\n\n"
      "for duelists.\n\n"
      "If you're not a duelist, I'm\n"
      "sorry, but you are not\n\n"
      "allowed to enter.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(LOCALID_STATION_GUARD_3, 26)
  MOVE_OBJECT(LOCALID_STATION_GUARD_3, DIRECTION_DOWN, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E774E0, map_14_state_01_08E774E0, 0x08E77360, 0x08F04040)
CHECK_FLAG(EVENT_FLAG_SAW_PANIK_ENTER_DOMINO_STATION)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77360, map_14_state_01_08E77360, 0x08F04040, 0x08F04040)
WALK_OBJECT_X(13, 56)
  WALK_OBJECT_Y(13, 0)
  WALK_OBJECT_X(14, 56)
  WALK_OBJECT_Y(14, 0)
  DELAY(64)
  WALK_OBJECT_Y(6, 48)
  DELAY(16)
  PLAY_MUSIC(SOUND_NONE)
  PLAY_MUSIC(MUSIC_414)
  TALK(PORTRAIT_PANICK, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Hee hee hee... I've found\n"
    "them...\n\n"
)
  WALK_OBJECT_Y(6, 0)
  SET_FLAG(EVENT_FLAG_SAW_PANIK_ENTER_DOMINO_STATION)
  WARP(LOCATION_DOMINO_STATION_TRAIN_STATION, 1, 1, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E773E4, map_14_state_01_08E773E4, 0x08F04040, 0x08F04040)
TEXT
  (
      "KaibaCorp is amazing.\n\n"
      "They chartered an entire\n"
      "express train just for a\n\n"
      "duel tournament...\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77564, map_14_state_01_08E77564, 0x08F04040, 0x08F04040)
TEXT
  (
      "All aboard! Duel Express\n"
      "will soon depart!\n\n"
      "The next and only stop is\n"
      "the Egypt Exhibition!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77570, map_14_state_01_08E77570, 0x08F04040, 0x08F04040)
TEXT
  (
      "The Duel Express is only\n"
      "running for duelists today.\n\n"
      "Non-duelists are not allowed\n"
      "to ride.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7736C, map_14_state_01_08E7736C, 0x08F04040, 0x08F04040)
TEXT
  (
      "If you win this tournament,\n"
      "you get a lot of ante\n\n"
      "cards!\n\n"
      "With these high stakes, it's\n"
      "more exciting than any\n\n"
      "street fight, hiyah!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77378, map_14_state_01_08E77378, 0x08E77384, 0x08E7739C)
CHECK_FLAG(EVENT_FLAG_DEFEATED_FENG_LONG)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77384, map_14_state_01_08E77384, 0x08E77390, 0x08F0404C)
TEXT
  (
      "Heheh! I'll take you on!\n"
      "Feel the heat! Hiyah!\n\n"
  )
  DUEL(DUELIST_PANICK_016)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77390, map_14_state_01_08E77390, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_230)
  TEXT
  (
      "Quit rubbing it in!\n\n"
      "I'm never playing you again!\n"
      "Hiyah!\n\n"
  )
  SET_FLAG(EVENT_FLAG_DEFEATED_FENG_LONG)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7739C, map_14_state_01_08E7739C, 0x08F04040, 0x08F04040)
TEXT
  (
      "I said I'm never playing you\n"
      "again! Hiyah!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E773A8, map_14_state_01_08E773A8, 0x08F04040, 0x08F04040)
TEXT
  (
      "Dueling is stupid.\n\n"
      "Haven't you heard?\n\n"
      "There are a bunch of bad\n"
      "guys who rip off rare cards\n\n"
      "in duels.\n\n"
      "You would think dueling is\n"
      "stupid too if you ran into\n\n"
      "them!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E773B4, map_14_state_01_08E773B4, 0x08F04040, 0x08F04040)
TEXT
  (
      "No way! Forget it!\n\n"
      "I don't even want to look at\n"
      "any cards!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
