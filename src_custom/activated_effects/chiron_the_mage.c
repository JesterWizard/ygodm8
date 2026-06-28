#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "chiron_the_mage.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void ActivateChironTheMageEffect(void)
{
  s8 col;
  struct DuelCard *target;

  if (NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
      >= MAX_ZONES_IN_ROW)
    goto show_text;

  col = HighestAtkMonInRowExceptGodCards(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);
  if (col < 0 || col >= MAX_ZONES_IN_ROW)
    goto show_text;

  target = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
  if (target == NULL || target->id == CARD_NONE)
    goto show_text;

  if (!Duel_TryNegateMonsterEffectOnZone(CHIRON_THE_MAGE, target))
    ClearZoneAndSendMonToGraveyard(target, INACTIVE_DUELIST);

show_text:
  if (gHideEffectText)
    return;

  if (gChaosCommandMagicianBlockedOriginMonsterEffectId == CHIRON_THE_MAGE)
    return;

  ResetCardEffectTextData();
  gCardEffectTextData.cardId = CHIRON_THE_MAGE;
  ActivateCardEffectText();
}
