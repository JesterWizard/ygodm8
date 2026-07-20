#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 DeckHasTwoDifferentGladiatorBeasts(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u16 first = CARD_NONE;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsGladiatorBeastMonster(cardId) || cardId == excludeId)
      continue;

    if (first == CARD_NONE) {
      first = cardId;
      continue;
    }

    if (cardId != first)
      return TRUE;
  }

  return FALSE;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void SpecialSummonTwoGladiatorBeastsFromDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 first = CARD_NONE;
  u16 second = CARD_NONE;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsGladiatorBeastMonster(cardId) || cardId == excludeId)
      continue;

    if (first == CARD_NONE) {
      first = cardId;
      continue;
    }

    if (cardId != first) {
      second = cardId;
      break;
    }
  }

  if (first != CARD_NONE)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, first, opts);

  if (IsDuelOver() == TRUE)
    return;

  if (second != CARD_NONE)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, second, opts);
}

static u8 MonsterRowHasRoomForTwoTagOuts(void)
{
  u8 col;
  u8 empty = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id == CARD_NONE)
      empty++;
  }

  return empty >= 1;
}

static u8 CanTagOut(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!MonsterRowHasRoomForTwoTagOuts())
    return FALSE;

  return DeckHasTwoDifferentGladiatorBeasts(GLADIATOR_BEAST_DRAGASES);
}

static void ShuffleSelfTagOut(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonTwoGladiatorBeastsFromDeck(GLADIATOR_BEAST_DRAGASES);
}

unsigned char CanActivateGLADIATOR_BEAST_DRAGASES(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_DRAGASES)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_DRAGASES)
    return FALSE;

  /* ponytail: battle indestruct + opp chain block + end-of-BP battled gate need
   * battle hooks. Ceiling: OPT GB tag-out → SS 2 different from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanTagOut();
}

void ActivateGLADIATOR_BEAST_DRAGASESEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_DRAGASES, 2);

  if (self == NULL || IsDuelOver() == TRUE || !CanTagOut())
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfTagOut(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
