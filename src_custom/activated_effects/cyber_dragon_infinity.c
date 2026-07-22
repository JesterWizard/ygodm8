#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cyber_dragon_infinity.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpAtkMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone == self || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  if (zone->isDefending)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Ceiling: ATK summons keep isFaceUp=0 until EOT flip. */
  return TRUE;
}

static u8 FieldHasFaceUpAtkTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpAtkMonster(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveAbsorb(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpAtkMonster(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  /* Ceiling: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage. */
  ClearZone(zone);
  NotifyDynamicEquipFieldChanged();

  if (self->tempStage < 127)
    self->tempStage = (s8)(self->tempStage + 1);

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

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpAtkMonster(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

#define CYBER_INFINITY_BASE_ATK 2100
#define CYBER_INFINITY_ATK_PER_MATERIAL 200

u8 CyberDragonInfinity_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 materials;
  u16 atk;

  if (zone == NULL || zone->id != CYBER_DRAGON_INFINITY)
    return FALSE;

  SetCardInfo(zone->id);
  materials = zone->tempStage > 0 ? (u8)zone->tempStage : 0;
  atk = Duel_ClampStat((u32)CYBER_INFINITY_BASE_ATK
                       + (u32)materials * CYBER_INFINITY_ATK_PER_MATERIAL);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateCYBER_DRAGON_INFINITY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CYBER_DRAGON_INFINITY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CYBER_DRAGON_INFINITY)
    return FALSE;

  /* ATK overlay via CyberDragonInfinity_ApplyDynamicZoneStats (+200 per tempStage).
   * Ceiling: Xyz attach / negate FALSE. OPT ClearZone absorb + tempStage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpAtkTarget();
}

void ActivateCYBER_DRAGON_INFINITYEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_DRAGON_INFINITY, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpAtkMonster, ResolveAbsorb, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
