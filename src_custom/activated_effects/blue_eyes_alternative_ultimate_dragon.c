#include "global.h"
#include "common-chax.h"
#include "blue_eyes_alternative_ultimate_dragon.h"
#include "cannot_attack_this_turn.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOppFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FieldHasOppCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppFieldCard(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  /* Cannot-attack-this-turn via CannotAttackThisTurn_CanDeclareAttack (unk4 mark). */
  self->unk4 |= DUEL_CANNOT_ATTACK_THIS_TURN_MARK;
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void DestroyUpToOppCards(u8 maxCount)
{
  u8 destroyed = 0;
  u8 row;
  u8 col;
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW && destroyed < maxCount; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW && destroyed < maxCount; col++) {
      struct DuelCard *zone;

      if (!IsOppFieldCard(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (zone == NULL)
        continue;

      if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      NotifyDynamicEquipFieldChanged();
      destroyed++;
    }
  }

  if (self == NULL || destroyed == 0)
    return;

  self->unk4 |= DUEL_CANNOT_ATTACK_THIS_TURN_MARK;
  MarkMonsterEffectUsed(self);
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
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppFieldCard(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 BlueEyesAlternativeUltimateDragon_PreventsDestroy(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON || !zone->isFaceUp)
    return FALSE;

  return TRUE;
}

u8 BlueEyesAlternativeUltimateDragon_IsTargetImmune(const struct DuelCard *zone)
{
  return BlueEyesAlternativeUltimateDragon_PreventsDestroy(zone);
}

void BlueEyesAlternativeUltimateDragon_OnFusionSummoned(struct DuelCard *zone,
                                                         const u16 *materialIds,
                                                         u8 materialCount)
{
  u8 i;

  if (zone == NULL || zone->id != BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON)
    return;

  zone->permStage = 0;
  if (materialIds == NULL)
    return;

  for (i = 0; i < materialCount; i++) {
    if (materialIds[i] == BLUE_EYES_ALTERNATIVE_WHITE_DRAGON) {
      zone->permStage = 1;
      break;
    }
  }
}

unsigned char CanActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON)
    return FALSE;

  /* Target/destroy protect via BlueEyesAlternativeUltimateDragon_*; Alt material
   * up-to-3 destroy via permStage + OnFusionSummoned. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppCard();
}

void ActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 maxDestroy;

  Duel_ShowEffectTextTyped(BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  maxDestroy = (self->permStage >= 1) ? 3 : 1;
  if (maxDestroy > 1) {
    DestroyUpToOppCards(maxDestroy);
    return;
  }

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppFieldCard, ResolveDestroyTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
