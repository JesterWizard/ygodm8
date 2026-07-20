#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define PENTACLE_OF_ACE_DRAW_COUNT 1
#define PENTACLE_OF_ACE_LP 500

static void PENTACLE_OF_ACE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 beneficiary;

  Duel_ShowEffectText(PENTACLE_OF_ACE);

  if (IsDuelOver() == TRUE)
    return;

  /* Heads: active draws + LP; Tails: opponent. Same coin convention as cup_of_ace. */
  if (RandRangeU8(0, 1) == 1)
    beneficiary = ACTIVE_DUELIST;
  else
    beneficiary = INACTIVE_DUELIST;

  if (Duel_DrawCards(beneficiary, PENTACLE_OF_ACE_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(beneficiary, PENTACLE_OF_ACE_LP, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectPENTACLE_OF_ACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(PENTACLE_OF_ACE, PENTACLE_OF_ACE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
