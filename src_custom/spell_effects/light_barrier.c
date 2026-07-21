#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

static u8 sLightBarrierNegated[2] APPEND_DATA = {FALSE, FALSE};
static const char sArcanaForceArchetypeName[] APPEND_RODATA = "Arcana Force";

/* ponytail: EffectEvent battle-destroy payloads expose the destroyed monster,
 * not its attacker. Ceiling: LP gain needs a battle parent that supplies both
 * zones to LightBarrier_GetArcanaForceBattleDestroyLp; upgrade: add attacker
 * data to the event payload. */

u8 LightBarrier_IsActiveForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return Duel_FindBackrowCard(fixedDuelist, LIGHT_BARRIER, TRUE) != NULL;
}

u8 LightBarrier_IsNegatedForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return sLightBarrierNegated[fixedDuelist];
}

void LightBarrier_ResolveStandbyCoin(u8 fixedDuelist, u8 heads)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return;

  sLightBarrierNegated[fixedDuelist] =
      LightBarrier_IsActiveForDuelist(fixedDuelist) && !heads;
}

u8 LightBarrier_AllowsArcanaForceCoinChoice(u8 fixedDuelist)
{
  return LightBarrier_IsActiveForDuelist(fixedDuelist)
      && !LightBarrier_IsNegatedForDuelist(fixedDuelist);
}

u16 LightBarrier_GetArcanaForceBattleDestroyLp(u8 fixedDuelist,
                                                const struct DuelCard *attacker,
                                                const struct DuelCard *destroyed)
{
  if (!LightBarrier_AllowsArcanaForceCoinChoice(fixedDuelist)
      || attacker == NULL || destroyed == NULL
      || destroyed->id >= NUM_TOTAL_CARDS
      || !Duel_CardNameContains(attacker->id, sArcanaForceArchetypeName))
    return 0;

  return gCardData_NEW[destroyed->id].atk;
}

APPEND_TEXT void EffectLIGHT_BARRIER(void)
{
  const struct EffectScript *script = EffectScript_Find(LIGHT_BARRIER, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
