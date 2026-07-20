#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
  Duel_ShuffleDeckFromDrawn(turnDuelist);
}

APPEND_TEXT void EffectTRAP_DUSTSHOOT(void)
{
  u8 i;
  s8 monsterZone = -1;
  struct DuelCard *slot;
  u16 cardId;

  Duel_ShowTrapResponseText(TRAP_DUSTSHOOT, gTrapEffectData.originCardId);

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 4) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    slot = ExpandedHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);
    if (slot != NULL && GetTypeGroup(slot->id) == TYPE_GROUP_MONSTER) {
      monsterZone = (s8)i;
      break;
    }
  }

  if (monsterZone >= 0) {
    slot = ExpandedHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)monsterZone);
    cardId = slot->id;
    ClearZone(slot);
    ReturnCardToDeck(ACTIVE_DUELIST, cardId);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: look at full hand + choose monster UI; trapEffect wire.
   * Ceiling: auto first monster in opp hand → Deck shuffle. */
}
