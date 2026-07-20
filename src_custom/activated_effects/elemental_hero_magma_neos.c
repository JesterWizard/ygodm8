#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 CountFieldCards(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
        count++;
    }
  }

  return count;
}

unsigned char CanActivateELEMENTAL_HERO_MAGMA_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_MAGMA_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_MAGMA_NEOS)
    return FALSE;

  /* ponytail: continuous 400/field + EP shuffle/bounce field need permanent/EP
   * hooks. Ceiling: OPT refresh tempStage from field card count. */
  return CanUseMonsterEffect(zone);
}

void ActivateELEMENTAL_HERO_MAGMA_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fieldCount;
  s8 stages;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_MAGMA_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  fieldCount = CountFieldCards();
  stages = (s8)fieldCount;
  if (stages > 126)
    stages = 126;
  else if (stages < -126)
    stages = -126;

  self->tempStage = stages;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
