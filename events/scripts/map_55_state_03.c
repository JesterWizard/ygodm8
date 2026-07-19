#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_55_state_03: map 55 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08EF057C, map_55_state_03_08EF057C, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PEGASUS)
  LOAD_SPRITE(2, SPRITE_CHEVALIER)
  LOAD_SPRITE(3, SPRITE_CHEVALIER)
  LOAD_SPRITE(4, SPRITE_CHEVALIER)
  LOAD_SPRITE(5, SPRITE_CHEVALIER)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Fufufu... You've finally arrived.",
      "Duelists of pure hearts and spirits, I was hoping you",
      "would come.",
      "Why? Because your defeats will make the best",
      "offerings for the reborn Reshef!"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(1, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Now! Go, my disciples!",
      "Go forth and defeat them!"
  )
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_260)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_CHEVALIER, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT, "Gawry nida!")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_260)
  OBJECT_EFFECT(OBJECT_3, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_CHEVALIER, "Gawry nida!")
  HIDE_PORTRAIT()
  DELAY(16)
  WALK_OBJECT_Y(5, 96)
  WALK_OBJECT_Y(4, 96)
  WALK_OBJECT_Y(3, 96)
  WALK_OBJECT_Y(2, 96)
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Reshef the Dark Being created my disciples.",
      "These duelists have neither emotion nor mercy.",
      "Crush them, my minions!"
  )
  TALK(PORTRAIT_SOL_CHEVELSKY, EXPRESSION_SOL_CHEVALSKY_HAPPY, PORTRAIT_POSITION_AUTO, "Ahahahahaha!")
  FADE_SCREEN(8)
  WARP(LOCATION_PEGASUS_ISLAND_DUNGEON_ENTRANCE, 3, 4, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
