#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

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

static u8 AnyMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

APPEND_TEXT void EffectDRAMATIC_RESCUE(void)
{
  struct DuelCard *targeted;
  s8 handZone;
  s8 empty;
  u16 returnedId;
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(DRAMATIC_RESCUE, gTrapEffectData.originCardId);

  /* ponytail: printed trigger is card targeting an Amazoness.
   * Ceiling: bounce origin-row monster if Amazoness + SS other from hand;
   * upgrade: target-chain hook when target passes Duel_IsAmazonessCard. */

  targeted = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (targeted != NULL && Duel_IsAmazonessCard(targeted->id)) {
    returnedId = targeted->id;
    empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
    ClearZone(targeted);
    if (empty >= 0)
      InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], returnedId);

    if (!ArchlordKristya_IsSpecialSummonLocked()
        && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
      if (WhoseTurn() == DUEL_PLAYER)
        handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], AnyMonster);
      else {
        u8 i;

        handZone = -1;
        for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
          if (AnyMonster(gTurnHands[INACTIVE_DUELIST][i]->id)
              && gTurnHands[INACTIVE_DUELIST][i]->id != returnedId) {
            handZone = (s8)i;
            break;
          }
        }
      }

      if (handZone >= 0) {
        opts = Duel_DefaultSpecialSummonOpts(TRUE);
        Duel_SpecialSummonFromHandZone(INACTIVE_DUELIST, handZone, opts);
      }
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
