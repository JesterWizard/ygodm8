#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_woodsman.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

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

static s8 FindPolymerizationGraveyardIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == POLYMERIZATION)
      return (s8)i;
  }

  return -1;
}

static u8 CanAddPolymerizationToHand(u8 turnDuelist)
{
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(turnDuelist, POLYMERIZATION) >= 0)
    return TRUE;

  return FindPolymerizationGraveyardIndex(turnDuelist) >= 0;
}

static u8 AddDeckPolymerizationToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s16 deckIndex;
  s8 handZone;
  u16 cardId;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, POLYMERIZATION);
  if (deckIndex < 0)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(gTurnHands[turnDuelist][handZone], cardId);
  return TRUE;
}

static u8 AddGraveyardPolymerizationToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 graveyardIndex;
  u16 cardId;
  s8 handZone;

  graveyardIndex = FindPolymerizationGraveyardIndex(turnDuelist);
  if (graveyardIndex < 0)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (GraveyardExpand_IsEnabled())
    cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, (u8)graveyardIndex);
  else
    cardId = GetGraveCardAndClearGrave(fixedDuelist);

  if (cardId != POLYMERIZATION)
    return FALSE;

  InitHandSlotFromCard(gTurnHands[turnDuelist][handZone], cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

unsigned char CanActivateElementalHeroWoodsman(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanAddPolymerizationToHand(ACTIVE_DUELIST);
}

void ActivateElementalHeroWoodsmanEffect(void)
{
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_WOODSMAN, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0) {
    if (!AddDeckPolymerizationToHand(ACTIVE_DUELIST))
      return;
  } else if (!AddGraveyardPolymerizationToHand(ACTIVE_DUELIST)) {
    return;
  }

  UpdateDuelGfxExceptField();
}

#if !defined(__GNUC__)
unsigned char CanActivateElementalHeroWoodsman(void);
void ActivateElementalHeroWoodsmanEffect(void);
#endif
