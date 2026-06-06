#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_31_state_01: map 31 state 1 */

LOAD_SPRITE(1, SPRITE_PARA)
CHECK_FLAG(EVENT_FLAG_TALKED_TO_PARA)
TEXT
(
    "Hiyah! This is a special\n"
    "dish for all, found only at\n\n"
    "the Great Wall!\n\n"
    "It's my Great Wall noodle\n"
    "soup! Eat and slurp!\n\n"
)
SET_FLAG(EVENT_FLAG_TALKED_TO_PARA)

EVENT_SCRIPT_REPLACEMENT(0x08EB4288, map_31_state_01_08EB4288, 0x08F04040, 0x08F04040)
TEXT
  (
      "I'm very busy making\n"
      "noodles, okay?\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4258, map_31_state_01_08EB4258, 0x08F04040, 0x08F04040)
PLAY_MUSIC(MUSIC_706)
  PLAY_MUSIC(MUSIC_380)
  WALK_OBJECT_Y(0, 56)
  SHOW_OBJECT(13, 78, 88, 0, 0, 0)
  WALK_OBJECT_Y(13, 66)
  SHOW_OBJECT(14, 66, 88, 0, 0, 0)
  WALK_OBJECT_Y(14, 66)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_1)
  DELAY(8)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  WALK_OBJECT_X(1, 72)
  WALK_OBJECT_Y(1, 48)
  DELAY(16)
  TEXT
  (
      "Hiyah! This is a special\n"
      "dish for all, found only at\n\n"
      "the Great Wall!\n\n"
      "It's my Great Wall noodle\n"
      "soup! Eat and slurp!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(1, 68)
  WALK_OBJECT_Y(1, 38)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  SET_FLAG(EVENT_FLAG_TALKED_TO_PARA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4270, map_31_state_01_08EB4270, 0x08EB427C, 0x08EB4294)
CHECK_FLAG(EVENT_FLAG_TALKED_TO_PARA)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4294, map_31_state_01_08EB4294, 0x08EB42A0, 0x08EB42D0)
CHECK_FLAG(EVENT_FLAG_JOEY_FOUND_PARA_AND_DOX_SUSPICIOUS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42A0, map_31_state_01_08EB42A0, 0x08F04040, 0x08F04040)
TEXT
  (
      "Hiyah! You want to duel?\n\n"
      "I'm too busy making noodles\n"
      "and gruel. I have no time\n\n"
      "to duel.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42D0, map_31_state_01_08EB42D0, 0x08EB42DC, 0x08F0404C)
PLAY_MUSIC(MUSIC_404)
  PLAY_MUSIC(MUSIC_330)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Grrr! How cleverly you\n"
      "surmise to see through our\n\n"
      "disguise!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(0, 48)
  WALK_OBJECT_X(0, 68)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  WALK_OBJECT_X(13, 52)
  WALK_OBJECT_Y(13, 40)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  WALK_OBJECT_X(14, 84)
  WALK_OBJECT_Y(14, 40)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Very well! You leave us with\n"
      "no choice!\n\n"
      "I challenge you in Master\n"
      "Sol Chevalsky's place!\n\n"
      "We shall duel! Prepare to\n"
      "lose, you fool!\n\n"
  )
  DUEL(DUELIST_PARA_039)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42DC, map_31_state_01_08EB42DC, 0x08EB42E8, 0x08F04040)
PLAY_MUSIC(MUSIC_404)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "That was cruel! I concede\n"
      "defeat in this duel!\n\n"
      "But our true skill is in tag\n"
      "duels!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "Younger brother, let us take\n"
      "them down together!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 0, 0)
  DELAY(8)
  WALK_OBJECT_X(2, 92)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_14)
  SLIDE_OBJECT(14, 0, 6)
  MOVE_OBJECT(14, DIRECTION_UP, 0, 0)
  WALK_OBJECT_X(2, 76)
  LOAD_SPRITE(2, SPRITE_DOX)
  DELAY(8)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, OBJECT_14)
  DELAY(8)
  MOVE_OBJECT(14, DIRECTION_RIGHT, 8, 0)
  MOVE_OBJECT(14, DIRECTION_UP, 6, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  DELAY(8)
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Elder brother! I am here to\n"
      "help!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "In a tag duel, defeating the\n"
      "likes of you...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_HAPPY, PORTRAIT_LEFT)
  TEXT
  (
      "...Would be so simple I\n"
      "already bid you adieu!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42E8, map_31_state_01_08EB42E8, 0x08EB42F4, 0x08EB4300)
WALK_OBJECT_Y(5, 64)
  WALK_OBJECT_Y(6, 64)
  DELAY(16)
  PLAY_MUSIC(MUSIC_405)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "I can't believe you're\n"
      "struggling against these\n\n"
      "amateurs!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0 | OBJECT_1 | OBJECT_2 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Kaiba!\n\n"
  )
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "My big brother's here to\n"
      "take you down\n\n"
      "Because you work for Sol\n"
      "Chevalsky.\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "The only duelist worthy of\n"
      "the Egyptian God Cards...\n\n"
      "Is me!\n\n"
      "I'll show no mercy, even\n"
      "against miserable duelists\n\n"
      "like you!\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER}! Today's your lucky\n"
      "day!\n\n"
      "I'll help you! Choose which\n"
      "sissy to duel!\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Para\n"
      "Dox{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB42F4, map_31_state_01_08EB42F4, 0x08EB430C, 0x08F0404C)
HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  MOVE_OBJECT(5, DIRECTION_UP, 8, 0)
  WALK_OBJECT_X(5, 76)
  WALK_OBJECT_Y(5, 48)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(6, DIRECTION_RIGHT, 16, 0)
  WALK_OBJECT_Y(6, 48)
  MOVE_OBJECT(6, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  DUEL(DUELIST_SETO_040)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB430C, map_31_state_01_08EB430C, 0x08EB4318, 0x08F04040)
PLAY_MUSIC(MUSIC_405)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "Come forth, Blue-Eyes White\n"
      "Dragon!\n\n"
  )
  PLAY_MUSIC(MUSIC_333)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_BLUE_EYES_WHITE_DRAGON_FULL_ART)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "White Lightning!\n\n"
  )
  PLAY_MUSIC(MUSIC_338)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_BLUE_EYES_ATTACK_UP_ALT)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4318, map_31_state_01_08EB4318, 0x08EB4324, 0x08F04040)
SLIDE_OBJECT(1, 2, 4)
  DELAY(8)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_DEFEATED, PORTRAIT_LEFT)
  TEXT
  (
      "M-Master Sol Chevalsky...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  SLIDE_OBJECT(2, 2, 4)
  DELAY(8)
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_DEFEATED, PORTRAIT_LEFT)
  TEXT
  (
      "...W-we have failed you...\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_LEFT)
  TEXT
  (
      "Run to Sol Chevalsky and\n"
      "tell him.\n\n"
      "That as long as Seto Kaiba\n"
      "lives...\n\n"
      "All his plans are doomed to\n"
      "fail! Wahahahahahaha!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4324, map_31_state_01_08EB4324, 0x08EB4330, 0x08F04040)
HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
  WALK_OBJECT_Y(1, 96)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 8, 0)
  WALK_OBJECT_Y(2, 96)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4330, map_31_state_01_08EB4330, 0x08EB436C, 0x08F04040)
MOVE_OBJECT(5, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER}, you only won\n"
      "because you had my help.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "Listen, {PLAYER}.\n\n"
      "I walk my own road.\n\n"
      "I don't know if you'll win\n"
      "or fail on your journey...\n\n"
      "But try not to disappoint\n"
      "me.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_LEFT)
  TEXT
  (
      "Now go and look for your\n"
      "mystical trinkets.\n\n"
      "While you play scavenger\n"
      "hunt, I'll save the world.\n\n"
      "Wahahahahaha!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB436C, map_31_state_01_08EB436C, 0x08EB4378, 0x08F04040)
HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(5, 96)
  MOVE_OBJECT(0, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(13, DIRECTION_DOWN, 0, 0)
  MOVE_OBJECT(14, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4378, map_31_state_01_08EB4378, 0x08EB4384, 0x08EB4390)
WALK_OBJECT_Y(6, 56)
  WALK_OBJECT_X(6, 72)
  MOVE_OBJECT(6, DIRECTION_UP, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "You better hurry up and find\n"
      "the Millennium Items.\n\n"
      "We heard that the Neo Ghouls\n"
      "are hunting for them, too.\n\n"
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{CARD_1}Is that true?\n"
      "So it was true...{CARD_2}\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4384, map_31_state_01_08EB4384, 0x08EB439C, 0x08F04040)
PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "You can thank KaibaCorp's\n"
      "information network.\n\n"
      "That's why Seto's here, to\n"
      "give you this info...\n\n"
      "Oops, he told me not tell\n"
      "you that.\n\n"
      "Well, see ya!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB439C, map_31_state_01_08EB439C, 0x08F04040, 0x08F04040)
HIDE_PORTRAIT()
  TEXT_FRAGMENT("{BYTE_8168}")
  WALK_OBJECT_Y(6, 96)
  HIDE_PORTRAIT()
  FADE_MUSIC(2)
  DELAY(32)
  SET_FLAG(EVENT_FLAG_DEFEATED_PARA_AND_DOX)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4390, map_31_state_01_08EB4390, 0x08EB439C, 0x08F04040)
PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "Oh, you knew already?\n\n"
      "To think that we came all\n"
      "the way out here...\n\n"
      "Just because Seto wanted you\n"
      "to have this info...\n\n"
      "Oops, that's supposed to be\n"
      "a secret! Don't let Seto\n\n"
      "know that I told you!\n\n"
      "Well, see ya!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4300, map_31_state_01_08EB4300, 0x08EB433C, 0x08F0404C)
HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_X(0, 76)
  MOVE_OBJECT(0, DIRECTION_UP, 0, 0)
  WALK_OBJECT_Y(5, 48)
  MOVE_OBJECT(13, DIRECTION_RIGHT, 0, 0)
  MOVE_OBJECT(14, DIRECTION_LEFT, 0, 0)
  MOVE_OBJECT(6, DIRECTION_LEFT, 24, 0)
  WALK_OBJECT_Y(6, 48)
  MOVE_OBJECT(6, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  DUEL(DUELIST_MOKUBA_041)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB433C, map_31_state_01_08EB433C, 0x08EB4348, 0x08F04040)
PLAY_MUSIC(MUSIC_405)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "Come forth, Blue-Eyes White\n"
      "Dragon!\n\n"
  )
  PLAY_MUSIC(MUSIC_333)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_BLUE_EYES_WHITE_DRAGON_FULL_ART)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "White Lightning!\n\n"
  )
  PLAY_MUSIC(MUSIC_338)
  SHOW_OVERWORLD_GRAPHIC(GRAPHIC_BLUE_EYES_ATTACK_UP)
  DELAY(16)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4348, map_31_state_01_08EB4348, 0x08EB4354, 0x08F04040)
SLIDE_OBJECT(1, 2, 4)
  DELAY(8)
  PORTRAIT(PORTRAIT_PARA, EXPRESSION_PARA_DEFEATED, PORTRAIT_LEFT)
  TEXT
  (
      "M-Master Sol Chevalsky...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  SLIDE_OBJECT(2, 2, 4)
  DELAY(8)
  PORTRAIT(PORTRAIT_DOX, EXPRESSION_DOX_DEFEATED, PORTRAIT_LEFT)
  TEXT
  (
      "...W-we have failed you...\n\n"
  )
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_LEFT)
  TEXT
  (
      "Run to Sol Chevalsky and\n"
      "tell him.\n\n"
      "That as long as Seto Kaiba\n"
      "lives...\n\n"
      "All his plans are doomed to\n"
      "fail! Wahahahahahaha!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4354, map_31_state_01_08EB4354, 0x08EB4360, 0x08F04040)
HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_LEFT, 8, 0)
  WALK_OBJECT_Y(1, 96)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 8, 0)
  WALK_OBJECT_Y(2, 96)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EB4360, map_31_state_01_08EB4360, 0x08EB436C, 0x08F04040)
MOVE_OBJECT(5, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  TEXT
  (
      "{PLAYER}, you only won\n"
      "because you had my help.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 2, PORTRAIT_LEFT)
  TEXT
  (
      "Listen, {PLAYER}.\n\n"
      "I walk my own road.\n\n"
      "I don't know if you'll win\n"
      "or fail on your journey...\n\n"
      "But try not to disappoint\n"
      "me.\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0)
  DELAY(16)
  PORTRAIT(PORTRAIT_SETO, 1, PORTRAIT_LEFT)
  TEXT
  (
      "Now go and look for your\n"
      "mystical trinkets.\n\n"
      "While you play scavenger\n"
      "hunt, I'll save the world.\n\n"
      "Wahahahahaha!\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
