#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

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

static u8 IsMorphtronicCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static void SearchMorphtronic(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 empty;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (IsMorphtronicCard(gDuelDecks[fixedDuelist].cards[i])) {
      cardId = gDuelDecks[fixedDuelist].cards[i];
      deckIndex = i;
      break;
    }
  }

  if (cardId == CARD_NONE)
    return;

  if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
}

APPEND_TEXT void EffectMORPHTRONIC_FORCEFIELD(void)
{
  struct DuelCard *origin;

  Duel_ShowTrapResponseText(MORPHTRONIC_FORCEFIELD, gTrapEffectData.originCardId);

  origin = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (origin != NULL
      && (GetTypeGroup(origin->id) == TYPE_GROUP_SPELL
          || GetTypeGroup(origin->id) == TYPE_GROUP_TRAP))
    Duel_DestroyZone(origin, ACTIVE_DUELIST, FALSE);

  SearchMorphtronic();

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
