#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 HandHasTheCreator(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i] != NULL
        && gTurnHands[ACTIVE_DUELIST][i]->id == THE_CREATOR)
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateTHE_CREATOR_INCARNATE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_CREATOR_INCARNATE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_CREATOR_INCARNATE)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HandHasTheCreator()
      && (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) + 1 > 0);
}

void ActivateTHE_CREATOR_INCARNATEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(THE_CREATOR_INCARNATE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  ClearZone(self);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromHand(ACTIVE_DUELIST, THE_CREATOR, NULL, opts);
  UpdateDuelGfxExceptField();
}
