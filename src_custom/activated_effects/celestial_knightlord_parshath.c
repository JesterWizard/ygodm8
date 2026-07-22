#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sSanctuaryName[] APPEND_RODATA = "Sanctuary in the Sky";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSanctuaryOrMentions(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == THE_SANCTUARY_IN_THE_SKY)
    return TRUE;

  return Duel_CardNameContains(cardId, sSanctuaryName);
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FAIRY);
}

static u16 FindSanctuarySearchInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY) >= 0)
    return THE_SANCTUARY_IN_THE_SKY;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSanctuaryOrMentions(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindFairyInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFairyMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanDiscardSearchPath(void)
{
  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 1)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    return FindFairyInDeck() != CARD_NONE;

  return FindSanctuarySearchInDeck() != CARD_NONE;
}

unsigned char CanActivateCELESTIAL_KNIGHTLORD_PARSHATH(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CELESTIAL_KNIGHTLORD_PARSHATH)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CELESTIAL_KNIGHTLORD_PARSHATH)
    return FALSE;

  /* Ceiling: Link material + GY banish Fairy → SS Fairy need send/banish hooks.
   * OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanDiscardSearchPath();
}

void ActivateCELESTIAL_KNIGHTLORD_PARSHATHEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 addId;

  Duel_ShowEffectTextTyped(CELESTIAL_KNIGHTLORD_PARSHATH, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!CanDiscardSearchPath())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    addId = FindFairyInDeck();
  else
    addId = FindSanctuarySearchInDeck();

  if (addId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, addId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
