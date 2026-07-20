#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void ALLURING_MIRROR_SPLIT_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(ALLURING_MIRROR_SPLIT);

  /* ponytail: battle-destroy of Harpie Lady / Sisters → SS different-name Harpie
   * from Deck needs a battle-destroy listener + OPT bit outside this file.
   * Ceiling: continuous face-up only; upgrade: after battle destroy → if face-up
   * ALLURING_MIRROR_SPLIT and destroyed is Harpie Lady / Sisters then Deck SS
   * Harpie with original name != destroyed. */

  /* ponytail: when this card is destroyed by a Harpie effect or opponent's effect
   * → SS 1 Harpie from GY needs a destroy-reason hook outside this file.
   * Ceiling: no floating on leave; upgrade: ClearZoneAndSendMonToGraveyard /
   * destroy path → if id was ALLURING_MIRROR_SPLIT and reason matches, PickZone
   * GY Harpie → Duel_SpecialSummonFromGrave. */
}

APPEND_TEXT void EffectALLURING_MIRROR_SPLIT(void)
{
  if (Duel_TryResolveSpellThroughTraps(ALLURING_MIRROR_SPLIT,
                                       ALLURING_MIRROR_SPLIT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
static const char sHarpieName[] APPEND_RODATA = "Harpie";
static const char sHarpieLadySistersName[] APPEND_RODATA = "Harpie Lady Sisters";

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  if (cardId == HARPIE_LADY || cardId == HARPIE_LADY_SISTERS)
    return TRUE;

  return Duel_CardNameContains(cardId, sHarpieLadySistersName);
}

void ALLURING_MIRROR_SPLIT_SelfCheck(void)
{
  if (!IsHarpieMonster(HARPIE_LADY))
    while (1)
      ;
  if (!IsHarpieLadyOrSisters(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (IsHarpieMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
