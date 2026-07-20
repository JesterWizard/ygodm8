#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsSpellcasterCard(u16 cardId)
{
  return Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER);
}

static u8 ControlsSpellcaster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id;

    if (IsSpellcasterCard(cardId))
      return TRUE;
  }

  return FALSE;
}

static u8 HandHasSpellcaster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsSpellcasterCard(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidMagicalDimensionTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasMagicalDimensionTribute(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMagicalDimensionTributeZone(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsValidMagicalDimensionDestroyZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasMagicalDimensionDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidMagicalDimensionDestroyZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateMAGICAL_DIMENSION(void)
{
  if (!ControlsSpellcaster())
    return FALSE;

  if (!HasMagicalDimensionTribute())
    return FALSE;

  return HandHasSpellcaster();
}

static void DestroyMagicalDimensionSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == MAGICAL_DIMENSION)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static s8 PickAiSpellcasterHandZone(void)
{
  u8 i;
  s8 chosen = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;

    if (!IsSpellcasterCard(cardId))
      continue;

    SetCardInfo(cardId);
    if (chosen < 0 || gCardInfo.atk > bestAtk) {
      chosen = i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosen;
}

static void SpecialSummonSpellcasterFromHand(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!HandHasSpellcaster())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsSpellcasterCard, opts);
    return;
  }

  {
    s8 handZone = PickAiSpellcasterHandZone();

    if (handZone >= 0)
      Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
  }
}

static void CancelOptionalDestroy(void)
{
  PlayMusic(SFX_CANCEL);
  /* Optional destroy skipped — tribute + SS already resolved. */
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;
  u8 inactiveRow = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  /* Prefer opponent monsters; fall back to any valid target. */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidMagicalDimensionDestroyZone(inactiveRow, col))
      continue;

    zone = gFixedZones[inactiveRow][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = inactiveRow;
      *outCol = col;
    }
  }

  if (found)
    return TRUE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidMagicalDimensionDestroyZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveOptionalDestroy(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!IsValidMagicalDimensionDestroyZone(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(fixedRow), FALSE);
  NotifyDynamicEquipFieldChanged();
}

static void BeginOptionalDestroyPick(void)
{
  if (!HasMagicalDimensionDestroyTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMagicalDimensionDestroyZone, ResolveOptionalDestroy,
                     CancelOptionalDestroy, AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void FinishMagicalDimension(u8 tributeRow, u8 tributeCol)
{
  struct DuelCard *tributeZone;

  if (!IsValidMagicalDimensionTributeZone(tributeRow, tributeCol) || !HandHasSpellcaster()) {
    DestroyMagicalDimensionSpellZone();
    return;
  }

  tributeZone = gFixedZones[tributeRow][tributeCol];

  DestroyMagicalDimensionSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonSpellcasterFromHand();

  if (IsDuelOver() == TRUE)
    return;

  BeginOptionalDestroyPick();
}

static void CancelTributeTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyMagicalDimensionSpellZone();
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidMagicalDimensionTributeZone(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveTributeTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidMagicalDimensionTributeZone(fixedRow, fixedCol))
    return;

  FinishMagicalDimension(fixedRow, fixedCol);
}

static void MAGICAL_DIMENSION_ResolveBody(void)
{
  Duel_ShowEffectText(MAGICAL_DIMENSION);

  if (IsDuelOver() == TRUE || !CanActivateMAGICAL_DIMENSION())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMagicalDimensionTributeZone, ResolveTributeTarget,
                     CancelTributeTargeting, AiPickTributeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMAGICAL_DIMENSION(void)
{
  if (!CanActivateMAGICAL_DIMENSION()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MAGICAL_DIMENSION, MAGICAL_DIMENSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MAGICAL_DIMENSION_SelfCheck(void)
{
  if (!IsSpellcasterCard(DARK_MAGICIAN))
    while (1)
      ;

  if (IsSpellcasterCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
