#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void MillTopN(u8 turnDuelist, u8 n)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 i;

  for (i = 0; i < n; i++) {
    u16 cardId;

    if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist))
      break;
    cardId = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];
    gDuelDecks[fixedDuelist].cardsDrawn++;
    GraveyardExpand_PushTurn(turnDuelist, cardId);
  }
}

APPEND_TEXT void EffectSIXTH_SENSE(void)
{
  u8 declareA = 2;
  u8 declareB = 5;
  u8 roll;
  u8 hit;

  Duel_ShowTrapResponseText(SIXTH_SENSE, gTrapEffectData.originCardId);

  /* ponytail: no declare-2-numbers UI — fixed guess 2+5.
   * Ceiling: AI/player always declare 2 and 5; upgrade: D-Pad number picker. */
  roll = RandRangeU8(1, 6);
  hit = (roll == declareA || roll == declareB);

  if (hit) {
    if (Duel_DrawCards(INACTIVE_DUELIST, roll, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    MillTopN(INACTIVE_DUELIST, roll);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
