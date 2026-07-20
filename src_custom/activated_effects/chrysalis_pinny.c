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

unsigned char CanActivateCHRYSALIS_PINNY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CHRYSALIS_PINNY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CHRYSALIS_PINNY)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || !NeoSpaceOnField())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Need room after tributing self (+1 empty). */
  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) + 1 > 0;
}

void ActivateCHRYSALIS_PINNYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(CHRYSALIS_PINNY, 2);

  if (self == NULL || !NeoSpaceOnField() || IsDuelOver() == TRUE)
    return;

  /* Tribute self, then SS Neo-Spacian Glow Moss from hand or Deck. */
  ClearZone(self);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, NEO_SPACIAN_GLOW_MOSS, NULL, opts) != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, NEO_SPACIAN_GLOW_MOSS, opts);

  UpdateDuelGfxExceptField();
}
