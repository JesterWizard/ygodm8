#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanAddFirstGraveyardCardToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard != CARD_NONE;

  return GraveyardExpand_GetCount(fixedDuelist) > 0;
}

static u8 AddFirstGraveyardCardToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (cardId == CARD_NONE)
      return FALSE;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    if (GraveyardExpand_GetCount(fixedDuelist) == 0)
      return FALSE;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, 0);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);
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

unsigned char ShouldActivateARCANA_FORCE_EX_THE_LIGHT_RULER(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != ARCANA_FORCE_EX_THE_LIGHT_RULER)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* Tails negate FALSE; Heads only when GY→hand legal. */
  return CanAddFirstGraveyardCardToHand(duelist);
}

void ActivateARCANA_FORCE_EX_THE_LIGHT_RULER(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u8 heads;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(ARCANA_FORCE_EX_THE_LIGHT_RULER, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = 1;

  if (heads)
    AddFirstGraveyardCardToHand(duelist);
  /* Tails Quick negate + battle add need chain/battle hooks. */

  UpdateDuelGfxExceptField();
}
