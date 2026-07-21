#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void PlaceCardOnDeckTop(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

APPEND_TEXT void EffectLIGHTSWORN_JUDGEMENT(void)
{
  struct DuelCard *trapZone =
      gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  Duel_ShowTrapResponseText(LIGHTSWORN_JUDGEMENT, gTrapEffectData.originCardId);

  /* Activate: place this card on top of the Deck. */
  if (trapZone != NULL && trapZone->id == LIGHTSWORN_JUDGEMENT) {
    PlaceCardOnDeckTop(INACTIVE_DUELIST, LIGHTSWORN_JUDGEMENT);
    ClearZone(trapZone);
  }

  UpdateDuelGfxExceptField();
}
