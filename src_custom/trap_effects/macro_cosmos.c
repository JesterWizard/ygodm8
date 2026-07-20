#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectMACRO_COSMOS(void)
{
  struct DuelCard *trapZone;
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(MACRO_COSMOS, gTrapEffectData.originCardId);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (trapZone != NULL)
    Duel_ActivateContinuousZone(trapZone);

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, HELIOS_THE_PRIMORDIAL_SUN, NULL, opts)
        != DUEL_ACTION_OK)
      Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, HELIOS_THE_PRIMORDIAL_SUN, opts);
  }

  UpdateDuelGfxExceptField();

  /* ponytail: any card sent to GY is banished instead needs GY-send redirect
   * while face-up MACRO_COSMOS. Ceiling: continuous + optional Helios SS. */
}
