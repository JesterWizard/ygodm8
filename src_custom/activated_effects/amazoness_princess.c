#include "global.h"
#include "amazoness_princess.h"
#include "archlord_kristya.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
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

static u8 FixedDuelistForZone(struct DuelCard *zone)
{
  u8 fixed = GetDuelistForZone(zone);

  if (fixed <= DUEL_OPPONENT)
    return fixed;
  return FixedDuelistForActive();
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsAmazonessMonsterExceptPrincess(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == AMAZONESS_PRINCESS)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_IsAmazonessCard(cardId);
}

static u16 FindAmazonessMonsterInDeck(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAmazonessMonsterExceptPrincess(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }
  return CARD_NONE;
}

static u8 HandHasSendableCard(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i)->id != CARD_NONE)
      return TRUE;
  }
  return FALSE;
}

static struct DuelCard *FindOtherFieldSendTarget(struct DuelCard *attacker, u8 fixedDuelist)
{
  u8 monRow = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 backRow = fixedDuelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[monRow][col];

    if (zone == NULL || zone == attacker || zone->id == CARD_NONE)
      continue;
    return zone;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backRow][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    return zone;
  }
  return NULL;
}

static u8 SendCostForPrincessAttack(struct DuelCard *attacker, u8 turnDuelist, u8 fixedDuelist,
                                    u8 preferFieldMonster)
{
  struct DuelCard *fieldCost;

  if (!preferFieldMonster && HandHasSendableCard(turnDuelist))
    return Duel_DiscardFromHand(turnDuelist, 1, NULL, TRUE) == DUEL_ACTION_OK;

  fieldCost = FindOtherFieldSendTarget(attacker, fixedDuelist);
  if (preferFieldMonster) {
    if (fieldCost == NULL || GetTypeGroup(fieldCost->id) != TYPE_GROUP_MONSTER)
      return FALSE;
  } else if (fieldCost == NULL) {
    return FALSE;
  }

  if (Duel_DestroyZone(fieldCost, turnDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  NotifyDynamicEquipFieldChanged();
  return TRUE;
}

void TryAmazonessPrincessOnAttackDeclared(struct DuelCard *attacker, struct DuelCard *defender)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u8 turnMonRow;
  u16 cardId;
  struct DuelCard *fieldCost;
  struct DuelSummonOpts opts;
  u8 preferFieldMonster;

  (void)defender;

  if (gHideEffectText || attacker == NULL || attacker->id != AMAZONESS_PRINCESS)
    return;

  fixedDuelist = FixedDuelistForZone(attacker);
  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  turnMonRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                             : INACTIVE_DUELIST_MONSTER_ROW;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  cardId = FindAmazonessMonsterInDeck(fixedDuelist);
  if (cardId == CARD_NONE)
    return;

  fieldCost = FindOtherFieldSendTarget(attacker, fixedDuelist);
  if (!HandHasSendableCard(turnDuelist) && fieldCost == NULL)
    return;

  preferFieldMonster = FirstEmptyZoneInRow(gTurnZones[turnMonRow]) < 0;
  if (preferFieldMonster) {
    if (fieldCost == NULL || GetTypeGroup(fieldCost->id) != TYPE_GROUP_MONSTER)
      return;
  }

  Duel_ShowEffectTextTyped(AMAZONESS_PRINCESS, 3);

  if (!SendCostForPrincessAttack(attacker, turnDuelist, fixedDuelist, preferFieldMonster))
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (FirstEmptyZoneInRow(gTurnZones[turnMonRow]) < 0)
    return;

  cardId = FindAmazonessMonsterInDeck(fixedDuelist);
  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
}

static u8 IsAmazonessSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAmazonessName);
}

static u16 FindAmazonessSpellTrapInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAmazonessSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAMAZONESS_PRINCESS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_PRINCESS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_PRINCESS)
    return FALSE;

  /* On-Summon search via TryAmazonessPrincessOnMonsterPlacement; name=Queen via
   * AmazonessPrincess_TreatsNameAsQueen + Duel_ZoneEffectCardId.
   * Attack-declare send→SS via TryAmazonessPrincessOnAttackDeclared. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindAmazonessSpellTrapInDeck() != CARD_NONE;
}

void ActivateAMAZONESS_PRINCESSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(AMAZONESS_PRINCESS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindAmazonessSpellTrapInDeck();
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
