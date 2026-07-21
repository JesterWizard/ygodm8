#include "global.h"
#include "common-chax.h"
#include "chicken_game.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "spell_effects.h"

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

static u8 sChickenGameIgnitionNoResponse APPEND_DATA = {0};

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

u8 ChickenGame_FaceUpOnField(void)
{
  return Duel_FindBackrowCard(DUEL_PLAYER, CHICKEN_GAME, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, CHICKEN_GAME, TRUE) != NULL;
}

u8 ChickenGame_PlayerHasLowestLifePoints(u8 fixedDuelist)
{
  u8 other = fixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (gDuelLifePoints[fixedDuelist] < gDuelLifePoints[other])
    return TRUE;

  if (gDuelLifePoints[fixedDuelist] == gDuelLifePoints[other])
    return TRUE;

  return FALSE;
}

u8 ChickenGame_ShouldBlockBattleDamage(u8 damagedFixedDuelist)
{
  if (!ChickenGame_FaceUpOnField())
    return FALSE;

  return ChickenGame_PlayerHasLowestLifePoints(damagedFixedDuelist);
}

u8 ChickenGame_ShouldSkipTrapChain(void)
{
  return sChickenGameIgnitionNoResponse;
}

void ChickenGame_BeginIgnitionNoResponse(void)
{
  sChickenGameIgnitionNoResponse = TRUE;
}

void ChickenGame_EndIgnitionNoResponse(void)
{
  sChickenGameIgnitionNoResponse = FALSE;
}

static u8 CanPayChickenGameCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= CHICKEN_GAME_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= CHICKEN_GAME_LP_COST;
}

u8 ChickenGame_CanActivateIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != CHICKEN_GAME || zone->isFaceUp == FALSE)
    return FALSE;

  if (EffectOpt_IsUsed(CHICKEN_GAME))
    return FALSE;

  return CanPayChickenGameCost();
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

static void ResolveChickenGameIgnition(struct DuelCard *zone)
{
  u8 mode;

  if (!ChickenGame_CanActivateIgnition(zone))
    return;

  ChickenGame_BeginIgnitionNoResponse();

  Duel_ShowEffectText(CHICKEN_GAME);

  if (IsDuelOver() == TRUE) {
    ChickenGame_EndIgnitionNoResponse();
    return;
  }

  if (Duel_ChangeLp(ACTIVE_DUELIST, -CHICKEN_GAME_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER) {
    ChickenGame_EndIgnitionNoResponse();
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    mode = PlayerChoosesChickenGameMode();
  else
    mode = CHICKEN_GAME_DRAW;

  EffectOpt_MarkUsed(CHICKEN_GAME);

  if (mode == CHICKEN_GAME_DRAW) {
    Duel_DrawCards(ACTIVE_DUELIST, CHICKEN_GAME_DRAW_COUNT, TRUE);
    ChickenGame_EndIgnitionNoResponse();
    return;
  }

  if (mode == CHICKEN_GAME_DESTROY_GAIN) {
    Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);
    ChickenGame_EndIgnitionNoResponse();
    if (IsDuelOver() == TRUE)
      return;

    Duel_ChangeLp(ACTIVE_DUELIST, CHICKEN_GAME_LP_GAIN, TRUE);
    return;
  }

  ChickenGame_EndIgnitionNoResponse();
  Duel_ChangeLp(INACTIVE_DUELIST, CHICKEN_GAME_LP_GAIN, TRUE);
}

static void CHICKEN_GAME_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (zone != NULL && zone->isLocked) {
    if (!ChickenGame_CanActivateIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveChickenGameIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(CHICKEN_GAME);

  if (ChickenGame_CanActivateIgnition(zone))
    ResolveChickenGameIgnition(zone);
}

APPEND_TEXT void EffectCHICKEN_GAME(void)
{
  /* ponytail: OPT ignition no-response — parent skips TryResolveSpellThroughTraps
   * when ChickenGame_ShouldSkipTrapChain() during face-up re-activation. */
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
  if (ChickenGame_ShouldBlockBattleDamage(DUEL_PLAYER)
      && !ChickenGame_FaceUpOnField())
    while (1)
      ;
}
#endif
