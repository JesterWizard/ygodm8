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

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static void ActivateAMAZONESS_HALLZone(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;
  u16 cardId = CARD_NONE;
  s8 empty;

  if (Duel_ActivateContinuousTrapPreamble(zone, AMAZONESS_HALL) == DUEL_ACTION_DUEL_OVER)
    return;

  /* On activate: add 1 Amazoness from GY to hand.
   * Extra Deck / Pendulum place + opp SS gain LP need hooks. */

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (Duel_IsAmazonessCard(id) && GetTypeGroup(id) == TYPE_GROUP_MONSTER) {
        cardId = id;
        GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
        break;
      }
    }
  }

  if (cardId != CARD_NONE)
    InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);

  UpdateDuelGfxExceptField();
}

void TryActivateAMAZONESS_HALLOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(AMAZONESS_HALL, ActivateAMAZONESS_HALLZone);
}

