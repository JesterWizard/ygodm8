#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAromaPlantMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sAromaName))
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_PLANT);
}

static u16 FindDeckAromaPlant(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAromaPlantMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAROMASERAPHY_SWEET_MARJORAM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMASERAPHY_SWEET_MARJORAM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMASERAPHY_SWEET_MARJORAM)
    return FALSE;

  /* ponytail: LP-higher Plant untargetable + Synchro Winds search + LP-gain
   * destroy need continuous/summon/LP hooks. Ceiling: OPT search Aroma Plant. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckAromaPlant() != CARD_NONE;
}

void ActivateAROMASERAPHY_SWEET_MARJORAMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(AROMASERAPHY_SWEET_MARJORAM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckAromaPlant();
  if (cardId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
