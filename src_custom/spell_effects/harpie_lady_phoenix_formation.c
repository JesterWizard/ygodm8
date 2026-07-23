#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "harpie_lady_phoenix_formation.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 sPhoenixMaxTargets APPEND_DATA = {0};
static u8 sPhoenixDestroyed APPEND_DATA = {0};
static u16 sPhoenixHighestAtk APPEND_DATA = {0};
static u8 sPhoenixPicking APPEND_DATA = {0};

static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  return cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == HARPIE_LADY_SISTERS
      || cardId == CYBER_SLASH_HARPIE_LADY || cardId == CYBER_SLASH_HARPY_LADY
      || cardId == HARPIE_PERFUMER || cardId == HARPIE_QUEEN || cardId == HARPIE_DANCER
      || cardId == HARPIE_ORACLE || cardId == HARPIE_CONDUCTOR || cardId == HARPIE_CHANNELER
      || cardId == HARPIE_HARPIST;
}

static u8 CountHarpieLadyOrSisters(void)
{
  u8 count = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsHarpieLadyOrSisters(zone->id))
      count++;
  }

  return count;
}

static u8 OppMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 IsPhoenixDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OppMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return Duel_SpellMayTargetMonsterZone(zone);
}

static u8 FieldHasPhoenixTarget(void)
{
  u8 col;
  u8 row = OppMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsPhoenixDestroyTarget(row, col))
      return TRUE;
  }
  return FALSE;
}

u8 CanActivateHARPIE_LADY_PHOENIX_FORMATION(void)
{
  if (EffectOpt_IsUsed(HARPIE_LADY_PHOENIX_FORMATION))
    return FALSE;
  if (CountHarpieLadyOrSisters() < 3)
    return FALSE;

  return FieldHasPhoenixTarget();
}

u8 HarpieLadyPhoenixFormation_CannotSpecialSummonFromMainOrExtraDeck(void)
{
  return EffectOpt_IsUsed(HARPIE_LADY_PHOENIX_FORMATION);
}

u8 HarpieLadyPhoenixFormation_CannotConductBattlePhase(void)
{
  return EffectOpt_IsUsed(HARPIE_LADY_PHOENIX_FORMATION);
}

static void FinishPhoenixFormation(void)
{
  sPhoenixPicking = FALSE;

  if (sPhoenixDestroyed > 0 && sPhoenixHighestAtk > 0) {
    if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)sPhoenixHighestAtk, TRUE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }

  if (sPhoenixDestroyed > 0)
    EffectOpt_MarkUsed(HARPIE_LADY_PHOENIX_FORMATION);

  UpdateDuelGfxExceptField();
}

static void ContinuePhoenixPick(void);

static void ResolvePhoenixTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u16 atk;

  if (!IsPhoenixDestroyTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  SetCardInfo(zone->id);
  atk = gCardInfo.atk;
  if (atk > sPhoenixHighestAtk)
    sPhoenixHighestAtk = atk;

  Duel_DestroyZone(zone, Duel_FixedDuelistForMonsterRow(fixedRow), FALSE);
  sPhoenixDestroyed++;

  if (IsDuelOver() == TRUE) {
    sPhoenixPicking = FALSE;
    return;
  }

  if (sPhoenixDestroyed >= sPhoenixMaxTargets || !FieldHasPhoenixTarget()) {
    FinishPhoenixFormation();
    return;
  }

  ContinuePhoenixPick();
}

static void CancelPhoenixTargeting(void)
{
  /* Optional: stop early after destroying some (still burn). */
  if (sPhoenixDestroyed > 0)
    FinishPhoenixFormation();
  else {
    sPhoenixPicking = FALSE;
    PlayMusic(SFX_CANCEL);
  }
}

static u8 AiPickPhoenixTarget(u8 *outRow, u8 *outCol)
{
  u8 row = OppMonsterFixedRow();
  u8 col;
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!IsPhoenixDestroyTarget(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    if (bestCol == 0xFF || gCardInfo.atk > bestAtk) {
      bestAtk = gCardInfo.atk;
      bestCol = col;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = row;
  *outCol = bestCol;
  return TRUE;
}

static void ContinuePhoenixPick(void)
{
  gDuelCursor.destY = OppMonsterFixedRow();
  gDuelCursor.destX = 0;
  Duel_SetupPickZone(IsPhoenixDestroyTarget, ResolvePhoenixTarget, CancelPhoenixTargeting,
                     AiPickPhoenixTarget);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    Duel_EnterPickZoneTargeting();
  else {
    /* AI: destroy up to max, highest ATK first each pick. */
    while (sPhoenixDestroyed < sPhoenixMaxTargets && FieldHasPhoenixTarget()) {
      u8 row;
      u8 col;

      if (!AiPickPhoenixTarget(&row, &col))
        break;
      ResolvePhoenixTarget(row, col);
      if (IsDuelOver() == TRUE || !sPhoenixPicking)
        return;
    }
    if (sPhoenixPicking)
      FinishPhoenixFormation();
  }
}

static void HARPIE_LADY_PHOENIX_FORMATION_ResolveBody(void)
{
  if (!CanActivateHARPIE_LADY_PHOENIX_FORMATION()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(HARPIE_LADY_PHOENIX_FORMATION);
  if (IsDuelOver() == TRUE)
    return;

  sPhoenixMaxTargets = CountHarpieLadyOrSisters();
  sPhoenixDestroyed = 0;
  sPhoenixHighestAtk = 0;
  sPhoenixPicking = TRUE;
  ContinuePhoenixPick();
}

APPEND_TEXT void EffectHARPIE_LADY_PHOENIX_FORMATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(HARPIE_LADY_PHOENIX_FORMATION,
                                       HARPIE_LADY_PHOENIX_FORMATION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
