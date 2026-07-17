#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 GraveyardHasMonster(u8 turnDuelist)
{
  u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 CanReturnGraveyardMonsterToHand(u8 turnDuelist)
{
  if (!GraveyardHasMonster(turnDuelist))
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
}

static u8 ReturnGraveyardMonsterToHand(u8 turnDuelist)
{
  u16 cardId;
  s8 handZone;
  struct DuelCard *handSlot;

  if (!CanReturnGraveyardMonsterToHand(turnDuelist))
    return FALSE;

  cardId = GetGraveCardAndClearGrave(turnDuelist);
  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0 || cardId == CARD_NONE)
    return FALSE;

  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)(handZone));
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
  return TRUE;
}

unsigned char ShouldActivateDesFeralImp(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != DES_FERAL_IMP)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return CanReturnGraveyardMonsterToHand(duelist);
}

void ActivateDesFeralImp(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(DES_FERAL_IMP, 8);
  ReturnGraveyardMonsterToHand(duelist);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
