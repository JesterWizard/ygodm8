#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void SUIT_OF_SWORD_X_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  enum DuelActionResult destroyResult;

  Duel_ShowEffectText(SUIT_OF_SWORD_X);

  if (IsDuelOver() == TRUE)
    return;

  /* Heads: destroy all opponent monsters; Tails: destroy all your monsters.
   * Same coin convention as cup_of_ace / ace_of_sword (1 = heads). */
  if (RandRangeU8(0, 1) == 1)
    destroyResult = Duel_DestroyAllMonstersMatching(INACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE);
  else
    destroyResult = Duel_DestroyAllMonstersMatching(ACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE);

  if (destroyResult == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectSUIT_OF_SWORD_X(void)
{
  if (Duel_TryResolveSpellThroughTraps(SUIT_OF_SWORD_X, SUIT_OF_SWORD_X_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
