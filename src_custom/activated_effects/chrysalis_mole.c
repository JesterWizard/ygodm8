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

unsigned char CanActivateCHRYSALIS_MOLE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CHRYSALIS_MOLE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CHRYSALIS_MOLE)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || !NeoSpaceOnField())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Need room after tributing self (+1 empty). */
  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) + 1 > 0;
}

void ActivateCHRYSALIS_MOLEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(CHRYSALIS_MOLE, 2);

  if (self == NULL || !NeoSpaceOnField() || IsDuelOver() == TRUE)
    return;

  /* Tribute self, then SS Neo-Spacian Grand Mole from hand or Deck. */
  ClearZone(self);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, NEO_SPACIAN_GRAND_MOLE, NULL, opts) != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, NEO_SPACIAN_GRAND_MOLE, opts);

  UpdateDuelGfxExceptField();
}
