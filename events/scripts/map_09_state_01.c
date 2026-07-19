#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_09_state_01 — Joey's house, morning of the Duel Express.
 *
 * Linear cutscene. Each string arg = one textbox page (auto word-wrap).
 * TALK(portrait[, expr[, pos]], "page", ...) — defaults NEUTRAL + LEFT.
 */

#define LOCALID_YUGI 13
#define LOCALID_JOEY 14

EVENT_SCRIPT_REPLACEMENT(0x08E62160, map_09_state_01)

  /* --- Setup ----------------------------------------------------------- */
  LOAD_SPRITE(1, SPRITE_INVISIBLE)
  /* Slots 2–12: unused placeholders (vanilla object table). */
  LOAD_SPRITE(2, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(3, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(4, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(5, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(6, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(7, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(8, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(9, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(10, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(11, SPRITE_YUGI_UNUSED)
  LOAD_SPRITE(12, SPRITE_YUGI_UNUSED)
  PLAY_MUSIC(MUSIC_KAIBACORP)
  SET_FLAG(EVENT_FLAG_SAW_INTRO_CUTSCENE)
  DELAY(32)
  LOAD_SPRITE(LOCALID_YUGI, SPRITE_YUGI)
  LOAD_SPRITE(LOCALID_JOEY, SPRITE_JOEY)

  /* --- Joey shows off his deck ----------------------------------------- */
  TALK(PORTRAIT_JOEY,
      "I put dis Monsta Card in here, like so...",
      "And voila! I'm good to go!")
  HIDE_PORTRAIT()
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_LEFT, 0, 0)
  DELAY(16)

  /* --- Joey inspects the player's deck --------------------------------- */
  TALK(PORTRAIT_JOEY,
      "{PLAYER}, how's adjustin' your deck comin' along?")
  HIDE_PORTRAIT()
  TALK(PORTRAIT_PLAYER,
      "I think I'm doing alright.")
  HIDE_PORTRAIT()
  TALK(PORTRAIT_JOEY,
      "You sure about dat? Let the expert, the one-and-only Joey Wheeler, check it out!")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_272)
  REACTION(REACTION_ELLIPSIS, SPRITE_JOEY)
  DELAY(16)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP,
      "Uh... It's cool to be confident about your skills.",
      "But you still have lots of work to do on this Deck before it's any good.")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_274)
  REACTION(REACTION_SWEATDROP, OBJECT_LOCALID(SLOT_PLAYER))
  DELAY(16)
  TALK(PORTRAIT_PLAYER,
      "Thanks for the vote of confidence man...")
  HIDE_PORTRAIT()
  TALK(PORTRAIT_JOEY,
      "Hey, don't feel bad. I know you can construct an awesome deck, {PLAYER}.")

  /* --- Hype for the tournament ----------------------------------------- */
  TEXT(
      "Alright guys, I'm gonna totally rock with this deck today!",
      "Man, I can't wait for the Duel Express train to come!",
      "It's been too long since I've dueled in a tournament!",
      "{PLAYER} and Yugi and I are gonna own this tourney!")
  TALK(PORTRAIT_JOEY,
      "Huh, what's wrong? Oh yeah! Where the heck's Yugi?")

  /* --- Joey panics: Yugi is late --------------------------------------- */
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_LEFT, 32, 0)
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_RIGHT, 32, 0)
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  PLAY_MUSIC(MUSIC_293)
  OBJECT_EFFECT(SPRITE_JOEY, OBJECT_EFFECT_JUMPING)
  DELAY(8)
  TALK(PORTRAIT_JOEY,
      "Oh man, this stinks! Look at the time already!")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_275)
  REACTION(REACTION_ANGRY, SPRITE_JOEY)
  DELAY(8)
  TALK(PORTRAIT_JOEY, EXPRESSION_JOEY_SWEATDROP,
      "He's late!",
      "C'mon Yugi... How can ya even think about being late on a day like this!",
      "If he doesn't get here soon, we'll miss the Duel Express!",
      "And he was the one who promised dat the three of us were gonna take the train together!",
      "Man, dat Yugi! Arrrrgh!",
      "If he doesn't get here, he can give me all his rare cards and I still won't forgive him!")

  /* --- Yugi arrives: Puzzle is gone ------------------------------------ */
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_212)
  SHOW_OBJECT(SPRITE_YUGI, 50, 74, 0, 0, 0)
  MOVE_OBJECT(SPRITE_YUGI, DIRECTION_UP, 2, 0)
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_LOCALID(SLOT_PLAYER))
  DELAY(8)
  MOVE_OBJECT(SLOT_PLAYER, DIRECTION_LEFT, 0, 0)
  DELAY(16)
  /* Sting between portrait and line — cannot fold into TALK. */
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_RIGHT)
  PLAY_MUSIC(MUSIC_400)
  TEXT("{PLAYER}, everything's horrible!")
  HIDE_PORTRAIT()
  DELAY(16)
  PLAY_MUSIC(MUSIC_270)
  REACTION(REACTION_QUESTION_MARK, OBJECT_LOCALID(SLOT_PLAYER))
  DELAY(16)
  WALK_OBJECT_Y(SPRITE_YUGI, 62)
  MOVE_OBJECT(SPRITE_YUGI, DIRECTION_RIGHT, 8, 0)
  DELAY(16)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SURPRISED, PORTRAIT_RIGHT,
      "My other self... The Millennium Puzzle...",
      "My Puzzle is gone, along with the spirit inside!")
  HIDE_PORTRAIT()
  DELAY(8)
  PLAY_MUSIC(MUSIC_271)
  REACTION(REACTION_EXCLAMATION_MARK, OBJECT_LOCALID(SLOT_PLAYER) | SPRITE_JOEY)
  DELAY(8)
  TALK(PORTRAIT_YUGI, EXPRESSION_YUGI_SAD, PORTRAIT_RIGHT,
      "When I woke up this morning, it was gone...",
      "I... I... What am I supposed to do?")

  /* --- Decide to look for the Puzzle ----------------------------------- */
  HIDE_PORTRAIT()
  DELAY(64)
  WALK_OBJECT_Y(SPRITE_JOEY, 56)
  WALK_OBJECT_X(SPRITE_JOEY, 58)
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_DOWN, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_JOEY,
      "Hey, we can't waste time standin' here and talkin'!",
      "What should we do, {PLAYER}?")
  HIDE_PORTRAIT()
  DELAY(16)
  TALK(PORTRAIT_PLAYER,
      "First order of business is to retrace your steps.",
      "Let's meet up with the gang at the clock tower.",
      "The more hand we have on this, the better.")
  HIDE_PORTRAIT()
  DELAY(16)
  MOVE_OBJECT(SPRITE_JOEY, DIRECTION_RIGHT, 0, 0)
  DELAY(16)
  TALK(PORTRAIT_JOEY,
      "Okay! Then that's what we're gonna do! You got it, Yugi?")

  /* --- Yugi's promise → clock tower ------------------------------------ */
  TALK(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_RIGHT,
      "I won't stop until I find my dearest friend...",
      "I promise!",
      "I'm counting on you, {PLAYER}.")
  HIDE_PORTRAIT()
  FADE_MUSIC(4)
  FADE_SCREEN(4)
  WARP(LOCATION_CLOCK_TOWER_SQUARE_NORTH, 1, 4, 0)
END_EVENT_SCRIPT()

/* Separate entry: intro cutscene → player house (not part of the scene above). */
EVENT_SCRIPT_REPLACEMENT(0x08E62154, map_09_state_01_intro_cutscene)
  PLAY_MUSIC(SOUND_NONE)
  CUTSCENE(8)
  WARP(LOCATION_PLAYER_HOUSE_INSIDE, 2, 0, 0)
END_EVENT_SCRIPT()
