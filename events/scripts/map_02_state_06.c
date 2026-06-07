#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_02_state_06: map 2 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E47860, map_02_state_06_08E47860, 0x08E47878, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_BLUE_JACKET)
  LOAD_SPRITE(2, SPRITE_GREENDALE_ZOMPIRE)
  LOAD_SPRITE(3, SPRITE_NEO_GHOUL)
  WALK_OBJECT_Y(SPRITE_GREENDALE_ZOMPIRE, 24)
  TEXT
  (
      "S-stop picking on the weak!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, SPRITE_NEO_GHOUL)
  DELAY(8)
  MOVE_OBJECT(SPRITE_NEO_GHOUL, DIRECTION_UP, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Wh-who are you?\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I-I'm t-the Greendale Zom...\n\n"
    "Y-you bad guys don't deserve\n"
    "to know my name!\n\n"
)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Little twerp! I'll make you\n"
    "regret facing me!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(SPRITE_NEO_GHOUL, 40)
  SLIDE_OBJECT(SPRITE_GREENDALE_ZOMPIRE, 0, 12)
  PLAY_MUSIC(MUSIC_277)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Graaaaaaaaah!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_284)
  SLIDE_OBJECT(SPRITE_NEO_GHOUL, 0, 16)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, SPRITE_GREENDALE_ZOMPIRE)
  DELAY(8)
  TEXT
  (
      "Th-there!\n"
      "Th-that serves you right!\n\n"
  )
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "...Come on, you didn't think\n"
    "that actually hurt me?\n\n"
    "Time to put this wannabe\n"
    "superhero to sleep!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(SPRITE_NEO_GHOUL, 48)
  DELAY(16)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Hand over your rare cards\n"
    "right now!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  SLIDE_OBJECT(SPRITE_GREENDALE_ZOMPIRE, 2, 4)
  DELAY(8)
  TEXT
  (
      "I-I c-can't win...\n\n"
      "Maybe I should run away...\n\n"
      "...No!\n\n"
      "A superhero never flies from\n"
      "danger!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_361)
  LOAD_SPRITE(2, SPRITE_LINT)
  DELAY(32)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I will not flee!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(SPRITE_LINT, 40)
  DELAY(8)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You persistent pest! You're\n"
    "annoying me...\n\n"
    "I'll let someone else deal\n"
    "with this fool...\n\n"
    "I can't waste time playing\n"
    "with kids.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(SPRITE_NEO_GHOUL, 96)
  SHOW_OBJECT(SPRITE_NEO_GHOUL, 128, 96, 0, 0, 0)
  DELAY(16)
  TEXT
  (
      "I wasn't cool like the\n"
      "actual Zompire...\n\n"
      "But I beat the villain...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_205)
  OBJECT_EFFECT(SPRITE_LINT, OBJECT_EFFECT_DISAPPEAR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47878, map_02_state_06_08E47878, 0x08F04040, 0x08F04040)
  WALK_OBJECT_Y(0, 66)
  SHOW_OBJECT(13, 66, 96, 0, 0, 0)
  WALK_OBJECT_Y(13, 76)
  SHOW_OBJECT(14, 54, 96, 0, 0, 0)
  WALK_OBJECT_Y(14, 76)
  SET_FLAG(EVENT_FLAG_LINT_FAINTED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E4786C, map_02_state_06_08E4786C, 0x08E47884, 0x08F04040)
  WALK_OBJECT_Y(2, 24)
  TEXT
  (
      "S-stop picking on the weak!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_3)
  DELAY(8)
  MOVE_OBJECT(3, DIRECTION_UP, 0, 0)
  DELAY(8)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Wh-who are you?\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I-I'm t-the Greendale Zom...\n\n"
    "Y-you bad guys don't deserve\n"
    "to know my name!\n\n"
)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Little twerp! I'll make you\n"
    "regret facing me!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(3, 40)
  SLIDE_OBJECT(2, 0, 12)
  PLAY_MUSIC(MUSIC_277)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Graaaaaaaaah!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_284)
  SLIDE_OBJECT(3, 0, 16)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_2)
  DELAY(8)
  TEXT
  (
      "Th-there!\n"
      "Th-that serves you right!\n\n"
  )
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "...Come on, you didn't think\n"
    "that actually hurt me?\n\n"
    "Time to put this wannabe\n"
    "superhero to sleep!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(3, 48)
  DELAY(16)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Hand over your rare cards\n"
    "right now!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  SLIDE_OBJECT(2, 2, 4)
  DELAY(8)
  TEXT
  (
      "I-I c-can't win...\n\n"
      "Maybe I should run away...\n\n"
      "...No!\n\n"
      "A superhero never flies from\n"
      "danger!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_361)
  LOAD_SPRITE(2, SPRITE_LINT)
  DELAY(32)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I will not flee!\n\n"
)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(SPRITE_LINT, 40)
  DELAY(8)
  TALK(PORTRAIT_NEO_GHOUL, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You persistent pest! You're\n"
    "annoying me...\n\n"
    "I'll let someone else deal\n"
    "with this fool...\n\n"
    "I can't waste time playing\n"
    "with kids.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(3, 96)
  SHOW_OBJECT(3, 128, 96, 0, 0, 0)
  DELAY(16)
  TEXT
  (
      "I wasn't cool like the\n"
      "actual Zompire...\n\n"
      "But I beat the villain...\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_205)
  OBJECT_EFFECT(SPRITE_LINT, OBJECT_EFFECT_DISAPPEAR)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E47884, map_02_state_06_08E47884, 0x08F04040, 0x08F04040)
  WALK_OBJECT_X(0, 8)
  SHOW_OBJECT(13, 0, 54, 0, 0, 0)
  SHOW_OBJECT(14, 0, 42, 0, 0, 0)
  SET_FLAG(EVENT_FLAG_LINT_FAINTED)
  FALLTHROUGH()
END_EVENT_SCRIPT()
