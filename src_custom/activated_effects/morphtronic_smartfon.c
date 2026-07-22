#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

static u8 IsMorphtronicCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 GyHasMorphtronic(u8 *outIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsMorphtronicMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return FALSE;

    *outIndex = 0;
    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (!IsMorphtronicMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      continue;

    *outIndex = i;
    return TRUE;
  }

  return FALSE;
}

static u16 BanishMorphtronicFromGy(u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsMorphtronicMonster(cardId))
      return CARD_NONE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return cardId;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsMorphtronicMonster(cardId))
    return CARD_NONE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  RemovedFromPlay_PushFixed(fixedDuelist, cardId);
  return cardId;
}

static u8 DeckCardsRemaining(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return (u8)(deckSize - top);
}

static u16 FindMorphtronicAmongTop(u8 count)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = 0; i < count; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[top + i];

    if (IsMorphtronicCard(cardId))
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

static u8 AddMorphtronicFromGyToHand(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s8 handZone;
  u8 i;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsMorphtronicCard(cardId))
      return FALSE;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsMorphtronicCard(cardId))
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 CanDefPath(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return IsMorphtronicCard(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsMorphtronicCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 CanAtkPath(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return DeckCardsRemaining() > 0;
}

unsigned char CanActivateMORPHTRONIC_SMARTFON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_SMARTFON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_SMARTFON)
    return FALSE;

  /* Ceiling: reveal UI FALSE; ATK die excavate add; DEF GY add Morphtronic.
   * FromHand: banish Morphtronic GY → SS. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->isDefending)
    return CanDefPath();

  return CanAtkPath();
}

void ActivateMORPHTRONIC_SMARTFONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 remaining;
  u8 roll;
  u8 peek;
  u16 cardId;

  Duel_ShowEffectTextTyped(MORPHTRONIC_SMARTFON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->isDefending) {
    if (!AddMorphtronicFromGyToHand())
      return;
  } else {
    remaining = DeckCardsRemaining();
    if (remaining == 0)
      return;

    roll = RandRangeU8(1, 6);
    peek = roll;
    if (peek > remaining)
      peek = remaining;

    cardId = FindMorphtronicAmongTop(peek);
    if (cardId == CARD_NONE) {
      Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      return;
    }

    if (!AddMorphtronicFromDeckToHand(cardId))
      return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonMorphtronicSmartfonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 gyIndex;

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MORPHTRONIC_SMARTFON)
    return FALSE;

  if (!GyHasMorphtronic(&gyIndex))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonMorphtronicSmartfonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 gyIndex;

  if (!CanSpecialSummonMorphtronicSmartfonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MORPHTRONIC_SMARTFON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!GyHasMorphtronic(&gyIndex))
    return FALSE;

  if (BanishMorphtronicFromGy(gyIndex) == CARD_NONE)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonMorphtronicSmartfonFromHand(u8 handZone);
u8 TrySpecialSummonMorphtronicSmartfonFromHand(u8 handZone);
#endif
