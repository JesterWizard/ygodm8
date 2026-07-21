#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "power_filter.h"
#include "spell_effects.h"

u8 PowerFilter_BlocksSpecialSummon(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (Duel_FindBackrowCard(DUEL_PLAYER, POWER_FILTER, TRUE) == NULL
      && Duel_FindBackrowCard(DUEL_OPPONENT, POWER_FILTER, TRUE) == NULL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.atk != 0xFFFF && gCardInfo.atk <= 1000;
}

static void POWER_FILTER_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(POWER_FILTER);
  /* Parent: PowerFilter_BlocksSpecialSummon in Duel_CardCannotBeSpecialSummoned. */
}

APPEND_TEXT void EffectPOWER_FILTER(void)
{
  if (Duel_TryResolveSpellThroughTraps(POWER_FILTER, POWER_FILTER_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
