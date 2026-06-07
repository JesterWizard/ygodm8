#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_29_state_04: map 29 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EAC984, map_29_state_04_08EAC984, 0x08EAC9A8, 0x08EAC990)
  LOAD_SPRITE(1, SPRITE_BONZ)
  LOAD_SPRITE(2, SPRITE_FORTUNE_TABLE)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Do you want your fortune\n"
    "told?\n\n"
)
  TALK(PORTRAIT_NONE, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "{CARD_1}Yes\n"
    "No{CARD_2}\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC9A8, map_29_state_04_08EAC9A8, 0x08EAC9C0, 0x08EAC9B4)
  CHECK_FLAG(EVENT_FLAG_BONZ_PREDICTED_PLAYER_PAST_LIFE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC9C0, map_29_state_04_08EAC9C0, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I may not look it, but I'm\n"
    "an expert fortuneteller.\n\n"
    "I'll peer into your previous\n"
    "life, {PLAYER}.\n\n"
)
  PLAY_MUSIC(MUSIC_368)
  TEXT
  (
      "Hmm... Yes, I can see it!\n"
      "I can feeeeeeeeeeeel it!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_1, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I can see your past very\n"
    "clearly!\n\n"
    "^5{BYTE_02}!\n\n"
    "That's what you were in your\n"
    "previous life.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Hahahaha!\n\n"
    "^5{BYTE_02}?\n\n"
    "That's what {PLAYER} was\n"
    "in a past life?\n\n"
    "Hahahaha, I can see the\n"
    "similarities!\n\n"
)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "In the past, you played\n"
    "^5{BYTE_05}...\n\n"
    "With the past incarnation of\n"
    "^5{BYTE_04}.\n\n"
    "This was\n"
    "^5{BYTE_03}.\n\n"
    "My fortunes are never wrong.\n\n"
)
  SET_FLAG(EVENT_FLAG_BONZ_PREDICTED_PLAYER_PAST_LIFE)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC9B4, map_29_state_04_08EAC9B4, 0x08EAC9CC, 0x08EAC9D8)
  CHECK_FLAG(EVENT_FLAG_BONZ_PREDICTED_PLAYER_ROMANTIC_MATCH)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC9CC, map_29_state_04_08EAC9CC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Fortunetelling is my\n"
    "specialty.\n\n"
    "I'll predict your perfect\n"
    "romantic match, {PLAYER}.\n\n"
)
  PLAY_MUSIC(MUSIC_368)
  TEXT
  (
      "Hmm... I can see it!\n"
      "I can feeeeeeeeeeeel it!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_1, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Ah, I can see this person!\n\n"
    "Your partner's initials are\n"
    "{BYTE_8168}^5{BYTE_06} ^5{BYTE_07}{BYTE_8168}.\n\n"
    "If you want to get closer to\n"
    "that person...\n\n"
    "Play ^5{BYTE_0B}\n"
    "^5{BYTE_0A}.\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_14, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Whoa, whoa, whoa!\n"
    "Who's {BYTE_8168}^5{BYTE_06} ^5{BYTE_07}{BYTE_8168}?\n\n"
    "Wait a sec,\n\n"
    "you can't be talking about\n"
    "THAT person?!?\n\n"
)
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_13)
  SET_FLAG(EVENT_FLAG_BONZ_PREDICTED_PLAYER_ROMANTIC_MATCH)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC9D8, map_29_state_04_08EAC9D8, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "I've been fortunetelling all\n"
    "my life.\n\n"
    "I even perfected my spooky\n"
    "voice!\n\n"
    "I'll look into your future,\n"
    "{PLAYER}.\n\n"
)
  PLAY_MUSIC(MUSIC_368)
  TEXT
  (
      "Hmm... I can see it!\n"
      "I can feeeeeeeeeeeel it!\n\n"
  )
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, OBJECT_0 | OBJECT_13 | OBJECT_14)
  DELAY(8)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(OBJECT_1, OBJECT_EFFECT_JUMPING)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Your future is clear!\n\n"
    "^5{BYTE_08},\n\n"
    "{PLAYER} will duel\n"
    "against...\n\n"
    "^5{BYTE_09}\n"
    "for\n\n"
    "^5{BYTE_0C}.\n\n"
    "To win, {PLAYER} must train\n"
    "with ^5{BYTE_0E}...\n\n"
    "The training will take place\n"
    "^5{BYTE_0D}.\n\n"
)
  CLEAR_FLAG(235)
  CLEAR_FLAG(236)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC990, map_29_state_04_08EAC990, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Oh... That's disappointing.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08EAC99C, map_29_state_04_08EAC99C, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_BONZ, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "My fortunetelling tells me\n"
    "that I can't win.\n\n"
    "So I won't duel right now..\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
