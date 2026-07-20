#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

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

static u8 IsDestinyHeroLvOrLess(u16 cardId, u8 maxLevel)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sDestinyHeroName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0 && gCardInfo.level <= maxLevel;
}

APPEND_TEXT void EffectD_TIME(void)
{
  u8 maxLevel = 4;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 cardId = CARD_NONE;
  u8 deckIndex = 0;
  s8 empty;

  Duel_ShowTrapResponseText(D_TIME, gTrapEffectData.originCardId);

  /* ponytail: when face-up E-HERO leaves field. Ceiling: when Effect runs,
   * search Destiny HERO Lv ≤ origin level (or 4); upgrade: leave-field hook
   * when Duel_IsElementalHeroCard. */

  if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
    SetCardInfo(gTrapEffectData.originCardId);
    if (gCardInfo.level > 0)
      maxLevel = gCardInfo.level;
  }

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty >= 0) {
    for (i = top; i < deckSize; i++) {
      if (IsDestinyHeroLvOrLess(gDuelDecks[fixedDuelist].cards[i], maxLevel)) {
        cardId = gDuelDecks[fixedDuelist].cards[i];
        deckIndex = i;
        break;
      }
    }
    if (cardId != CARD_NONE
        && Duel_RemoveDeckCardAt(INACTIVE_DUELIST, deckIndex, FALSE) == DUEL_ACTION_OK)
      InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
