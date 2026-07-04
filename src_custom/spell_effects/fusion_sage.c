#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 CanActivateFusionSage(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0;
}

static void FusionSage_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(FUSION_SAGE);

  if (IsDuelOver() == TRUE || !CanActivateFusionSage())
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, POLYMERIZATION, FALSE) != DUEL_ACTION_OK)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectFusionSage(void)
{
  if (!CanActivateFusionSage()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FUSION_SAGE, FusionSage_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
