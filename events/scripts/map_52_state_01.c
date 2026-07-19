#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_52_state_01: map 52 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08EE62A0, map_52_state_01_08EE62A0, 0x08EE62AC, 0x08EE62D0)
  LOAD_SPRITE(1, SPRITE_INVISIBLE)
  LOAD_SPRITE(2, SPRITE_SHADI)
  CHECK_FLAG(EVENT_FLAG_TALKED_TO_SHADIS_PORTRAIT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62AC, map_52_state_01_08EE62AC, 0x08EE62B8, 0x08EE62C4)
  SET_FLAG(EVENT_FLAG_TALKED_TO_SHADIS_PORTRAIT)
  PLAY_MUSIC(MUSIC_406)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_0)
  HIDE_PORTRAIT()
  DELAY(8)
  WALK_OBJECT_Y(0, 44)
  WALK_OBJECT_X(0, 72)
  MOVE_OBJECT(0, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_280)
  SHOW_OBJECT(2, 60, 44, 0, 1, 0)
  DELAY(16)
  MOVE_OBJECT(2, DIRECTION_RIGHT, 0, 0)
  DELAY(32)
  TALK(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You have traveled far... There is but a little more",
      "to go.",
      "I implore that you save Pegasus...",
      "Or Sol Chevalsky, as he now calls himself."
  )
  PORTRAIT(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_0)
  DELAY(16)
  TALK(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "My tale is long. Will you hear me out?")
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "{CARD_1}Yes\nNo{CARD_2}")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62B8, map_52_state_01_08EE62B8, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "To learn the truth takes courage...",
      "Hear my tale of the tragedy of Pegasus.",
      "Time passed since Duelist Kingdom...",
      "Pegasus awoke from his long dream...",
      "He wandered the globe, drawn by an unseen power.",
      "He visited many ancient ruins until his journey led",
      "him to Egypt.",
      "By chance, he found a stone tablet.",
      "Sealed within it was Reshef the Dark Being.",
      "And thus began Pegasus's tragedy.",
      "He slowly deciphered the stone tablet...",
      "And realized the calamity it could unleash.",
      "It could bring eternal darkness to the world...",
      "So Pegasus was determined to prevent Reshef's escape.",
      "As he further studied the stone tablet...",
      "He was unaware that he was falling under Reshef's",
      "spell...",
      "The Egyptian God Cards are needed to seal the stone",
      "tablet...",
      "But they can also be used to resurrect Reshef.",
      "Pegasus sought the Egyptian God Cards to seal Reshef",
      "forever...",
      "But, under Reshef's spell, he did the exact opposite.",
      "He used the Egyptian God Cards in a resurrection",
      "ritual...",
      "Which freed Reshef and turned the Egyptian God",
      "Cards to stone.",
      "The Millennium Items were also scattered across the",
      "globe.",
      "Pegasus is now fully under Reshef's control.",
      "{PLAYER}, you must not hate Pegasus.",
      "Hatred makes your spirit as tainted as Reshef's.",
      "You must enter the final battle with a pure spirit."
  )
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_TELEPORT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62C4, map_52_state_01_08EE62C4, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_SHADI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "I understand you are in a hurry. So be it.")
  HIDE_PORTRAIT()
  DELAY(32)
  PLAY_MUSIC(MUSIC_281)
  OBJECT_EFFECT(OBJECT_2, OBJECT_EFFECT_TELEPORT)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EE62D0, map_52_state_01_08EE62D0, EVENT_NOP, EVENT_NOP)
  TEXT("Shadi no longer appears...")
  FALLTHROUGH()
END_EVENT_SCRIPT()
