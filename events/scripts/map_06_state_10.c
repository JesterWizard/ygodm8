#include "event_macros.h"
#include "overworld.h"

/* map_06_state_10: map 6 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E5CD80, map_06_state_10_08E5CD80, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_DUKE_TEETH_GRITTED, 8)
  LANGUAGE_TEXT(0, "...And that's what happened.\n\n")
  END_LANGUAGE_TEXT()
  PLAY_MUSIC(272)
  REACTION(REACTION_ELLIPSIS, 24577)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, 8)
  LANGUAGE_TEXT(0, "Big brother... I saw this\nlook on Tristan's face...\n\nIt was as if he was saying\nthat he didn't want anyone\n\nto follow him.\n\nI wonder if he's going to be\nokay...\n\n")
  END_LANGUAGE_TEXT()
  PORTRAIT(PORTRAIT_JOEY, EXPRESSION_JOEY_ANGRY, 8)
  LANGUAGE_TEXT(0, "Don't worry about a thing,\nSerenity.\n\nTristan's our friend.\nThere's no way we'll\n\nabandon him!\n\nWe'll look for him, but I\nwant you to stay here,\n\nSerenity. Just in case he\ncomes back.\n\n")
  END_LANGUAGE_TEXT()
  SET_FLAG(EVENT_FLAG_SEARCHING_FOR_ROBOT_TRISTAN)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD98, map_06_state_10_08E5CD98, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_DUKE, EXPRESSION_NEUTRAL, 8)
  LANGUAGE_TEXT(0, "I bet Tristan ran off on\npurpose!\n\nThat's the only way Serenity\nwould pay attention to him\n\ninstead of me!\n\n...N-no, he wouldn't do\nthat. He's not that type of\n\nguy.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E5CD8C, map_06_state_10_08E5CD8C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_SERENITY, EXPRESSION_SERENITY_SAD, 8)
  LANGUAGE_TEXT(0, "Where could Tristan have\ngone?\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
