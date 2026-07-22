#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsMachineMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
      && Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static struct DuelCard *FindHandMachine(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *zone = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (zone != NULL && IsMachineMonster(zone->id))
      return zone;
  }

  return NULL;
}

static struct DuelCard *FindFieldMachineNotSelf(struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;

    if (zone->isFaceUp && IsMachineMonster(zone->id))
      return zone;
  }

  return NULL;
}

static u8 SendAncientGearGolemFromDeck(void)
{
  s16 deckIndex;
  u16 cardId = ANCIENT_GEAR_GOLEM;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  return TRUE;
}

static u8 CanPaySendCost(struct DuelCard *self)
{
  if (FindHandMachine() != NULL)
    return TRUE;

  if (FindFieldMachineNotSelf(self) != NULL)
    return TRUE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM) >= 0;
}

static u8 PaySendCost(struct DuelCard *self)
{
  struct DuelCard *machine;
  u8 fixedDuelist = FixedDuelistForActive();

  machine = FindHandMachine();
  if (machine != NULL) {
    if (Duel_DestroyZone(machine, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;
    return TRUE;
  }

  machine = FindFieldMachineNotSelf(self);
  if (machine != NULL) {
    ClearZoneAndSendMonToGraveyard2(machine, fixedDuelist);
    return TRUE;
  }

  return SendAncientGearGolemFromDeck();
}

unsigned char CanActivateANCIENT_GEAR_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_DRAGON)
    return FALSE;

  /* OPT send Machine hand/field or AG Golem from Deck to GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanPaySendCost(zone);
}

void ActivateANCIENT_GEAR_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!PaySendCost(self) || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
