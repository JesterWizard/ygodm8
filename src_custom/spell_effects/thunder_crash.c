#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define THUNDER_CRASH_DAMAGE_PER_MONSTER 300

static void ThunderCrash_ResolveBody(void)
{
  u8 monstersBefore = Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW);
  u8 monstersDestroyed;
  enum DuelActionResult destroyResult;

  Duel_ShowEffectText(THUNDER_CRASH);

  destroyResult = Duel_DestroyAllMonstersMatching(ACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE);
  if (destroyResult == DUEL_ACTION_DUEL_OVER)
    return;

  monstersDestroyed = monstersBefore - Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW);

  if (monstersDestroyed > 0) {
    if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)monstersDestroyed * THUNDER_CRASH_DAMAGE_PER_MONSTER,
                      FALSE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectThunderCrash(void)
{
  if (Duel_TryResolveSpellThroughTraps(THUNDER_CRASH, ThunderCrash_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
