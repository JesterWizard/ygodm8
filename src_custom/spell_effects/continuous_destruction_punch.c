#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void CONTINUOUS_DESTRUCTION_PUNCH_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(CONTINUOUS_DESTRUCTION_PUNCH);
  /* Battle: ApplyContinuousDestructionPunchBattleEffect (DEF > ATK → destroy attacker). */
}

APPEND_TEXT void EffectCONTINUOUS_DESTRUCTION_PUNCH(void)
{
  if (Duel_TryResolveSpellThroughTraps(CONTINUOUS_DESTRUCTION_PUNCH,
                                       CONTINUOUS_DESTRUCTION_PUNCH_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
