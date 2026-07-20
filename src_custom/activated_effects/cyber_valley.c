#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOtherFaceUpMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone == self || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return zone->isFaceUp || zone->isDefending == FALSE;
}

static u8 FieldHasOtherFaceUpMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOtherFaceUpMonster(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveBanishBothDraw2(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsOtherFaceUpMonster(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  MarkMonsterEffectUsed(self);

  if (Duel_BanishZone(self, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_BanishZone(target, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickMonsterTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOtherFaceUpMonster(gMonEffect.row, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void BanishSelfDraw1(struct DuelCard *self)
{
  MarkMonsterEffectUsed(self);

  if (Duel_BanishZone(self, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  /* ponytail: end Battle Phase needs phase hook; draw 1 is attack-target stand-in. */
  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateCYBER_VALLEY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CYBER_VALLEY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CYBER_VALLEY)
    return FALSE;

  /* ponytail: attack-target banish + GY place-on-deck need battle/GY hooks.
   * Ceiling: OPT banish self+1 face-up monster → draw 2; else banish self → draw 1. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateCYBER_VALLEYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CYBER_VALLEY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (FieldHasOtherFaceUpMonster()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    Duel_SetupPickZone(IsOtherFaceUpMonster, ResolveBanishBothDraw2, CancelTargeting,
                       AiPickMonsterTarget);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  BanishSelfDraw1(self);
}
