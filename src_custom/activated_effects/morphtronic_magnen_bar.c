#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

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

static u32 SumOtherFaceUpAtk(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
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

unsigned char CanActivateMORPHTRONIC_MAGNEN_BAR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_MAGNEN_BAR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_MAGNEN_BAR)
    return FALSE;

  /* ponytail: exactly-2-other ATK gate + DEF cannot-attack need battle hooks.
   * Ceiling: ATK Position OPT refresh tempStage from other ATK/500. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return zone->isDefending == FALSE && SumOtherFaceUpAtk() > 0;
}

void ActivateMORPHTRONIC_MAGNEN_BAREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u32 totalAtk;
  s8 stages;

  Duel_ShowEffectTextTyped(MORPHTRONIC_MAGNEN_BAR, 2);

  if (self == NULL || IsDuelOver() == TRUE || self->isDefending != FALSE)
    return;

  totalAtk = SumOtherFaceUpAtk();
  if (totalAtk == 0)
    return;

  /* Cap at 127 so tempStage (s8) stays in range. */
  if (totalAtk > 127u * 500u)
    totalAtk = 127u * 500u;

  stages = (s8)((totalAtk + 499) / 500);
  if (stages < 0)
    stages = 0;

  self->tempStage = stages;
  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
