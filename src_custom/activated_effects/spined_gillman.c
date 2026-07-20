#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static u8 IsFishSeaAqua(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FISH)
      || Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT)
      || Duel_CardHasMonsterType(cardId, TYPE_AQUA);
}

unsigned char CanActivateSPINED_GILLMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SPINED_GILLMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SPINED_GILLMAN)
    return FALSE;

  /* ponytail: continuous +400 ATK needs permanent overlay.
   * Ceiling: OPT +1 stage (~500) to each Fish/SS/Aqua you control. */
  return CanUseMonsterEffect(zone);
}

void ActivateSPINED_GILLMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 col;
  u8 row = gMonEffect.row;

  Duel_ShowEffectTextTyped(SPINED_GILLMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone != NULL && IsFishSeaAqua(zone->id))
      IncrementPermStage(zone);
  }

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
