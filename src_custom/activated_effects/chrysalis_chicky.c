#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 NeoSpaceOnField(void)
{
  return Duel_IsBackrowCardOnField(NEO_SPACE, TRUE);
}

unsigned char CanActivateCHRYSALIS_CHICKY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CHRYSALIS_CHICKY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CHRYSALIS_CHICKY)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || !NeoSpaceOnField())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) + 1 > 0;
}

void ActivateCHRYSALIS_CHICKYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(CHRYSALIS_CHICKY, 2);

  if (self == NULL || !NeoSpaceOnField() || IsDuelOver() == TRUE)
    return;

  ClearZone(self);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, NEO_SPACIAN_AIR_HUMMINGBIRD, NULL, opts)
      != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, NEO_SPACIAN_AIR_HUMMINGBIRD, opts);

  UpdateDuelGfxExceptField();
}
