#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "chaos_greed.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define CHAOS_GREED_DRAW_COUNT 2

static u8 FieldRowHasCardsExceptChaosGreed(u8 turnRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnZones[turnRow][i]->id;

    if (cardId == CARD_NONE || cardId == CHAOS_GREED)
      continue;

    return TRUE;
  }

  return FALSE;
}

u8 CanActivateChaosGreed(void)
{
  u16 graveyard = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

  if (graveyard != CARD_NONE && graveyard != CHAOS_GREED)
    return FALSE;

  if (FieldRowHasCardsExceptChaosGreed(ACTIVE_DUELIST_MONSTER_ROW))
    return FALSE;

  if (FieldRowHasCardsExceptChaosGreed(ACTIVE_DUELIST_BACKROW))
    return FALSE;

  return TRUE;
}

APPEND_TEXT void EffectChaosGreed(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivateChaosGreed())
    return;

  ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);

  if (Duel_DrawCards(ACTIVE_DUELIST, CHAOS_GREED_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(CHAOS_GREED);
}
