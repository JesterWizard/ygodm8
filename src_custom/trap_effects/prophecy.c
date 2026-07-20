#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_card_hand.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

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

APPEND_TEXT void EffectPROPHECY(void)
{
  s8 handZone;
  struct DuelCard *slot;
  u16 cardId;
  u16 atk;
  u8 predictHigher;
  u8 correct;
  s8 empty;

  Duel_ShowTrapResponseText(PROPHECY, gTrapEffectData.originCardId);

  handZone = Duel_PickRandomHandZone(ACTIVE_DUELIST);
  if (handZone < 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  slot = ExpandedHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone);
  cardId = slot->id;
  SetCardInfo(cardId);
  atk = (GetTypeGroup(cardId) == TYPE_GROUP_MONSTER) ? gCardInfo.atk : 0;

  /* Predict: AI guesses randomly; player always "higher" as default. */
  predictHigher = (WhoseTurn() == DUEL_PLAYER) ? TRUE : RandRangeU8(0, 1);
  correct = predictHigher ? (atk > 2000) : (atk < 2000);
  if (atk == 2000)
    correct = FALSE;

  if (correct) {
    empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
    if (empty >= 0) {
      InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
      ClearZone(slot);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: player predict UI (bigger/smaller) + trapEffect wire.
   * Ceiling: random opp hand card; AI random guess / player always higher. */
}
