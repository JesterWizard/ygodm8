#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

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

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 CardLevel(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].level;
}

static u8 GyHasMorphtronic(u8 *outIndex, u8 *outLevel)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (!IsMorphtronicMonster(cardId))
      return FALSE;

    *outIndex = 0;
    *outLevel = CardLevel(cardId);
    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsMorphtronicMonster(cardId))
      continue;

    *outIndex = i;
    *outLevel = CardLevel(cardId);
    return TRUE;
  }

  return FALSE;
}

static u16 BanishMorphtronicFromGy(u8 gyIndex, u8 *outLevel)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsMorphtronicMonster(cardId))
      return CARD_NONE;

    *outLevel = CardLevel(cardId);
    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return cardId;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsMorphtronicMonster(cardId))
    return CARD_NONE;

  *outLevel = CardLevel(cardId);
  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  RemovedFromPlay_PushFixed(fixedDuelist, cardId);
  return cardId;
}

static u8 HandHasMorphtronic(u8 *outLevel)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id;

    if (!IsMorphtronicMonster(cardId))
      continue;

    *outLevel = CardLevel(cardId);
    return TRUE;
  }

  return FALSE;
}

static u16 FindMorphtronicLevelInDeck(u8 level, u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsMorphtronicMonster(cardId) || CardLevel(cardId) != level)
      continue;

    if (excludeId != CARD_NONE && cardId == excludeId)
      continue;

    return cardId;
  }

  return CARD_NONE;
}

static u8 AddMorphtronicFromDeckToHand(u16 cardId)
{
  s16 deckIndex;
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0 || cardId == CARD_NONE)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

static u8 CanAtkPath(void)
{
  u8 gyIndex;
  u8 level;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (!GyHasMorphtronic(&gyIndex, &level))
    return FALSE;

  return FindMorphtronicLevelInDeck(level, CARD_NONE) != CARD_NONE;
}

static u8 CanDefPath(void)
{
  u8 level;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (!HandHasMorphtronic(&level))
    return FALSE;

  /* Need another same-Level Morphtronic in Deck (exclude none until discard known). */
  return FindMorphtronicLevelInDeck(level, CARD_NONE) != CARD_NONE;
}

unsigned char CanActivateMORPHTRONIC_REMOTEN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_REMOTEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_REMOTEN)
    return FALSE;

  /* position-gated OPT search (EffectOpt). ATK: banish GY Morphtronic → add
   * same Lv. DEF: discard Morphtronic → add other same Lv. */
  if (EffectOpt_IsUsed(MORPHTRONIC_REMOTEN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->isDefending)
    return CanDefPath();

  return CanAtkPath();
}

void ActivateMORPHTRONIC_REMOTENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 level;
  u16 banished;
  u16 searchId;
  u8 gyIndex;

  Duel_ShowEffectTextTyped(MORPHTRONIC_REMOTEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(MORPHTRONIC_REMOTEN))
    return;

  if (self->isDefending) {
    u16 discardedId = CARD_NONE;
    u8 i;
    u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

    for (i = 0; i < max; i++) {
      struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

      if (!IsMorphtronicMonster(slot->id))
        continue;

      discardedId = slot->id;
      level = CardLevel(discardedId);
      if (Duel_DestroyZone(slot, ACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
      break;
    }

    if (discardedId == CARD_NONE)
      return;

    if (IsDuelOver() == TRUE)
      return;

    searchId = FindMorphtronicLevelInDeck(level, discardedId);
    if (searchId == CARD_NONE)
      searchId = FindMorphtronicLevelInDeck(level, CARD_NONE);

    if (searchId == CARD_NONE || !AddMorphtronicFromDeckToHand(searchId))
      return;
  } else {
    if (!GyHasMorphtronic(&gyIndex, &level))
      return;

    banished = BanishMorphtronicFromGy(gyIndex, &level);
    if (banished == CARD_NONE)
      return;

    searchId = FindMorphtronicLevelInDeck(level, CARD_NONE);
    if (searchId == CARD_NONE || !AddMorphtronicFromDeckToHand(searchId))
      return;
  }

  EffectOpt_MarkUsed(MORPHTRONIC_REMOTEN);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
