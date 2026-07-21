#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAmazonessName[] APPEND_RODATA = "Amazoness";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsOtherAmazonessMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == AMAZONESS_AUGUSTA)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAmazonessName)
      || Duel_IsAmazonessCard(cardId);
}

static u16 FindAmazonessInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsOtherAmazonessMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAMAZONESS_AUGUSTA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_AUGUSTA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_AUGUSTA)
    return FALSE;

  /* Battle protect for other Amazoness is live via AmazonessQueen_PreventsBattleDestroy.
   * Ceiling: OPT SS Amazoness from Deck (Fusion Summon trigger stand-in); second attack FALSE. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindAmazonessInDeck() != CARD_NONE;
}

void ActivateAMAZONESS_AUGUSTAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(AMAZONESS_AUGUSTA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindAmazonessInDeck();
  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
