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

static u8 IsGladiatorBeastCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u16 FindDeckGladiatorBeastCard(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastCard(cardId) && cardId != TEST_PANTHER)
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindOtherGladiatorBeastInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return cardId;
  }

  return CARD_NONE;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 IsFaceUpGladiatorTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != gMonEffect.row)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->isFaceUp && IsGladiatorBeastMonster(zone->id);
}

static u8 HasFaceUpGladiatorTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpGladiatorTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSearch(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckGladiatorBeastCard() != CARD_NONE;
}

static u8 CanBounceSs(void)
{
  if (!HasFaceUpGladiatorTarget())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindOtherGladiatorBeastInDeck(CARD_NONE) != CARD_NONE;
}

static void ResolveBounceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;
  struct DuelSummonOpts opts;
  u16 tagId;

  if (!IsFaceUpGladiatorTarget(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  cardId = target->id;
  ClearZone(target);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  tagId = FindOtherGladiatorBeastInDeck(cardId);
  if (tagId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, tagId, opts);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickGladiatorTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpGladiatorTarget(gMonEffect.row, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateTEST_PANTHER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TEST_PANTHER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TEST_PANTHER)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT search GB from Deck, else bounce GB → SS different GB. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSearch() || CanBounceSs();
}

void ActivateTEST_PANTHEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(TEST_PANTHER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanSearch()) {
    cardId = FindDeckGladiatorBeastCard();
    if (cardId == CARD_NONE)
      return;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanBounceSs())
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  Duel_SetupPickZone(IsFaceUpGladiatorTarget, ResolveBounceTarget, CancelTargeting,
                     AiPickGladiatorTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
