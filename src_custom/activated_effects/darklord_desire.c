#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsFaceUpOppMonsterTarget(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  return IsFaceUpOppMonsterTarget(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  /* -2 tempStage (~1000 ATK, not exact); until EP via ResetTempStagesForAllCards. */
  if (self->tempStage > -126)
    self->tempStage = (s8)(self->tempStage - 2);

  if (Duel_DestroyZone(target, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = OPPONENT_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidTarget(*outRow, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol < 0 || atk > bestAtk) {
      bestCol = (s8)col;
      bestAtk = atk;
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateDARKLORD_DESIRE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARKLORD_DESIRE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARKLORD_DESIRE)
    return FALSE;

  /* Ceiling: Fairy-only Tribute Summon + cannot SS need summon hooks. Ceiling:
   * OPT -1000 ATK (tempStage) → send 1 opp monster to GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateDARKLORD_DESIREEffect(void)
{
  Duel_ShowEffectTextTyped(DARKLORD_DESIRE, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
