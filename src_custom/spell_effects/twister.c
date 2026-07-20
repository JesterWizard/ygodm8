#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define TWISTER_LP_COST 500

void UpdateDuelGfxExceptField(void);

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsSameFixedZone(u8 rowA, u8 colA, u8 rowB, u8 colB)
{
  return rowA == rowB && colA == colB;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 ActiveDuelistHasLpForCost(void)
{
  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= TWISTER_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= TWISTER_LP_COST;
}

static u8 IsValidTwisterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  if (IsSameFixedZone(fixedRow, fixedCol, originRow, originCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || !IsSpellOrTrapCard(zone->id))
    return FALSE;

  return zone->isFaceUp == TRUE;
}

static u8 HasTwisterTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTwisterTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroyTwisterSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == TWISTER)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveTwisterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidTwisterTarget(fixedRow, fixedCol))
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  DestroyTwisterSpellZone();
}

static void CancelTwisterTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  /* Cost already paid past traps — send the spell to GY. */
  DestroyTwisterSpellZone();
}

static u8 AiPickTwisterTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidTwisterTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateTWISTER(void)
{
  u8 savedDestY = gDuelCursor.destY;
  u8 savedDestX = gDuelCursor.destX;
  u8 ok;

  if (!ActiveDuelistHasLpForCost())
    return FALSE;

  /* Exclude self: spell-effect origin after ActivateSpellEffect, else cursor (gate). */
  if (gSpellEffectData.id == TWISTER) {
    gDuelCursor.destY = gSpellEffectData.row1;
    gDuelCursor.destX = gSpellEffectData.col1;
  } else {
    gDuelCursor.destY = gDuelCursor.currentY;
    gDuelCursor.destX = gDuelCursor.currentX;
  }

  ok = HasTwisterTarget();
  gDuelCursor.destY = savedDestY;
  gDuelCursor.destX = savedDestX;
  return ok;
}

static void TWISTER_ResolveBody(void)
{
  Duel_ShowEffectText(TWISTER);

  if (IsDuelOver() == TRUE || !CanActivateTWISTER())
    return;

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -TWISTER_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidTwisterTarget, ResolveTwisterTarget, CancelTwisterTargeting,
                     AiPickTwisterTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectTWISTER(void)
{
  if (!CanActivateTWISTER()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(TWISTER, TWISTER_LP_COST, TWISTER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TWISTER_SelfCheck(void)
{
  if (TWISTER_LP_COST != 500)
    while (1)
      ;
  if (!IsSpellOrTrapCard(MYSTICAL_SPACE_TYPHOON))
    while (1)
      ;
  if (IsSpellOrTrapCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
