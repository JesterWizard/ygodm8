#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define CHICKEN_GAME_LP_COST 1000
#define CHICKEN_GAME_LP_GAIN 1000
#define CHICKEN_GAME_DRAW_COUNT 1

enum ChickenGameMode {
  CHICKEN_GAME_DRAW = 0,
  CHICKEN_GAME_DESTROY_GAIN,
  CHICKEN_GAME_OPP_GAIN,
};

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Nested A/B: A = draw; B then A = destroy+gain; B then B = opp gains 1000. */
static u8 PlayerChoosesChickenGameMode(void)
{
  /* ponytail: no dedicated 3-way choice UI — nested A/B unlabeled.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return CHICKEN_GAME_DRAW;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      break;
    }

    WaitForVBlank();
  }

  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return CHICKEN_GAME_DESTROY_GAIN;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return CHICKEN_GAME_OPP_GAIN;
    }

    WaitForVBlank();
  }
}

static u8 CanPayChickenGameCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= CHICKEN_GAME_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= CHICKEN_GAME_LP_COST;
}

static u8 CanActivateChickenGameIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != CHICKEN_GAME || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  return CanPayChickenGameCost();
}

static void ResolveChickenGameIgnition(struct DuelCard *zone)
{
  u8 mode;

  if (!CanActivateChickenGameIgnition(zone))
    return;

  Duel_ShowEffectText(CHICKEN_GAME);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -CHICKEN_GAME_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    mode = PlayerChoosesChickenGameMode();
  else
    mode = CHICKEN_GAME_DRAW; /* AI prefers draw */

  zone->effectUsedThisTurn = TRUE;

  if (mode == CHICKEN_GAME_DRAW) {
    Duel_DrawCards(ACTIVE_DUELIST, CHICKEN_GAME_DRAW_COUNT, TRUE);
    return;
  }

  if (mode == CHICKEN_GAME_DESTROY_GAIN) {
    Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);
    if (IsDuelOver() == TRUE)
      return;

    Duel_ChangeLp(ACTIVE_DUELIST, CHICKEN_GAME_LP_GAIN, TRUE);
    return;
  }

  /* CHICKEN_GAME_OPP_GAIN */
  Duel_ChangeLp(INACTIVE_DUELIST, CHICKEN_GAME_LP_GAIN, TRUE);
}

static void CHICKEN_GAME_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up Field (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateChickenGameIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveChickenGameIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(CHICKEN_GAME);

  /* ponytail: lowest-LP player takes no damage needs an LP/damage gate outside
   * this file (no damage-immunity helper keyed to field spell).
   * Ceiling: continuous face-up + OPT pay/draw/destroy/opp-gain only; upgrade:
   * ChangeLp / battle-damage hook → if face-up CHICKEN_GAME and target has
   * strictly lower LP (or tied-lowest), skip damage. */

  /* ponytail: "neither player can activate cards/effects in response" needs a
   * response-block flag outside this file. Ceiling: normal trap chain still
   * possible on Effect entry; upgrade: skip TryResolveSpellThroughTraps for
   * ignition / set activation-protect flag. */

  /* ponytail: not in GetSpellType NORMAL/FIELD override — face-up OPT
   * re-activation may need card_hooks GetSpellType + CHICKEN_GAME listed
   * (same as CALL_OF_THE_MUMMY / WATERHAZARD). */

  if (CanActivateChickenGameIgnition(zone))
    ResolveChickenGameIgnition(zone);
}

APPEND_TEXT void EffectCHICKEN_GAME(void)
{
  if (Duel_TryResolveSpellThroughTraps(CHICKEN_GAME, CHICKEN_GAME_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CHICKEN_GAME_SelfCheck(void)
{
  if (CHICKEN_GAME_LP_COST != 1000)
    while (1)
      ;
  if (CHICKEN_GAME_LP_GAIN != 1000)
    while (1)
      ;
  if (CHICKEN_GAME_DRAW_COUNT != 1)
    while (1)
      ;
}
#endif
