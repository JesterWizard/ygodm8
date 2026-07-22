#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAncientGearGolem(u16 cardId)
{
  return cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM;
}

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_COMMANDER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static struct DuelCard *FindGolemHand(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsAncientGearGolem(slot->id))
      return slot;
  }

  return NULL;
}

static struct DuelCard *FindGolemFieldNotSelf(struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;

    if (zone->isFaceUp && IsAncientGearGolem(zone->id))
      return zone;
  }

  return NULL;
}

static u8 SendGolemCost(struct DuelCard *self)
{
  struct DuelCard *golem;
  u8 fixedDuelist = FixedDuelistForActive();
  s16 deckIndex;

  golem = FindGolemHand();
  if (golem != NULL) {
    if (Duel_DestroyZone(golem, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;
    return TRUE;
  }

  golem = FindGolemFieldNotSelf(self);
  if (golem != NULL) {
    ClearZoneAndSendMonToGraveyard2(golem, fixedDuelist);
    return TRUE;
  }

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM);
  if (deckIndex < 0)
    deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM_ULTIMATE_POUND);
  if (deckIndex < 0)
    deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, ULTIMATE_ANCIENT_GEAR_GOLEM);
  if (deckIndex < 0)
    return FALSE;

  {
    u16 cardId = gDuelDecks[fixedDuelist].cards[deckIndex];

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
      return FALSE;

    Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  }

  return TRUE;
}

static u8 CanPayGolemCost(struct DuelCard *self)
{
  if (FindGolemHand() != NULL)
    return TRUE;

  if (FindGolemFieldNotSelf(self) != NULL)
    return TRUE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM) >= 0
      || Duel_FindDeckCardIndex(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM_ULTIMATE_POUND) >= 0
      || Duel_FindDeckCardIndex(ACTIVE_DUELIST, ULTIMATE_ANCIENT_GEAR_GOLEM) >= 0;
}

static s8 FindAncientGearHandZone(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsAncientGearMonster(slot->id)
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindAncientGearInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAncientGearMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSsAncientGear(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (FindAncientGearHandZone() >= 0)
    return TRUE;

  return FindAncientGearInDeck() != CARD_NONE;
}

static u8 SpecialSummonAncientGear(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;
  u16 deckId;

  handZone = FindAncientGearHandZone();
  if (handZone >= 0)
    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)handZone, opts) == DUEL_ACTION_OK;

  deckId = FindAncientGearInDeck();
  if (deckId == CARD_NONE)
    return FALSE;

  return Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, deckId, opts) == DUEL_ACTION_OK;
}

unsigned char CanActivateANCIENT_GEAR_COMMANDER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_COMMANDER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_COMMANDER)
    return FALSE;

  /* Ceiling: OPT send AG Golem hand/field/Deck → SS AG hand/Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanPayGolemCost(zone) && CanSsAncientGear();
}

void ActivateANCIENT_GEAR_COMMANDEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_COMMANDER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!SendGolemCost(self) || IsDuelOver() == TRUE)
    return;

  if (!SpecialSummonAncientGear())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
