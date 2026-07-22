#include "global.h"
#include "common-chax.h"
#include "cannot_attack_this_turn.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "morphtronic_magnen_bar.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOtherFaceUpAtkMonster(struct DuelCard *zone, struct DuelCard *self)
{
  if (zone == NULL || zone == self || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!IsCardFaceUp(zone) && zone->isDefending != FALSE)
    return FALSE;

  return zone->isDefending == FALSE;
}

static u8 CountOtherFaceUpAtk(struct DuelCard *self)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOtherFaceUpAtkMonster(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col], self))
      count++;
  }

  return count;
}

static u32 SumOtherFaceUpAtk(struct DuelCard *self)
{
  u8 col;
  u32 total = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOtherFaceUpAtkMonster(zone, self))
      continue;

    total += Duel_GetZoneFinalAtk(zone);
  }

  return total;
}

static u8 RowHasDefMagnenBar(u8 fixedMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedMonsterRow][col];

    if (zone != NULL && zone->id == MORPHTRONIC_MAGNEN_BAR && zone->isDefending
        && IsCardFaceUp(zone))
      return TRUE;
  }

  return FALSE;
}

u8 MorphtronicMagnenBar_CanDeclareAttack(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  if ((zone->unk4 & MORPHTRONIC_MAGNEN_BAR_NO_ATTACK_MARK) != 0)
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return TRUE;

  return !RowHasDefMagnenBar(fixedRow);
}

void MorphtronicMagnenBar_ClearAttackMarksAtEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      zone->unk4 &= (u8)~MORPHTRONIC_MAGNEN_BAR_NO_ATTACK_MARK;
    }
  }
}

static void MarkOtherAtkMonstersNoAttack(struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOtherFaceUpAtkMonster(zone, self))
      continue;

    zone->unk4 |= MORPHTRONIC_MAGNEN_BAR_NO_ATTACK_MARK;
  }
}

unsigned char CanActivateMORPHTRONIC_MAGNEN_BAR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_MAGNEN_BAR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_MAGNEN_BAR)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->isDefending)
    return FALSE;

  return CountOtherFaceUpAtk(zone) == 2 && SumOtherFaceUpAtk(zone) > 0;
}

void ActivateMORPHTRONIC_MAGNEN_BAREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u32 totalAtk;
  s8 stages;

  Duel_ShowEffectTextTyped(MORPHTRONIC_MAGNEN_BAR, 2);

  if (self == NULL || IsDuelOver() == TRUE || self->isDefending != FALSE)
    return;

  if (CountOtherFaceUpAtk(self) != 2)
    return;

  totalAtk = SumOtherFaceUpAtk(self);
  if (totalAtk == 0)
    return;

  if (totalAtk > 127u * 500u)
    totalAtk = 127u * 500u;

  stages = (s8)((totalAtk + 499) / 500);
  if (stages < 0)
    stages = 0;

  self->tempStage = stages;
  MarkOtherAtkMonstersNoAttack(self);
  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MorphtronicMagnenBar_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = MORPHTRONIC_MAGNEN_BAR;
  zone.unk4 = MORPHTRONIC_MAGNEN_BAR_NO_ATTACK_MARK;
  if (MorphtronicMagnenBar_CanDeclareAttack(&zone) != FALSE)
    __builtin_trap();
}
#endif
