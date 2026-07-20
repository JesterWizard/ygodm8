#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
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

static u8 IsMorphtronicSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 IsLvLe4Morphtronic(u16 cardId)
{
  if (!IsMorphtronicMonster(cardId) || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].level > 0 && gCardData_NEW[cardId].level <= 4;
}

static s8 FindOtherMorphtronicHandZone(u8 exceptZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (i == exceptZone)
      continue;

    if (IsMorphtronicMonster(
            SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindMorphtronicSpellTrapInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsMorphtronicSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindLvLe4MorphtronicInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsLvLe4Morphtronic(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 AddCardFromDeckToHand(u16 cardId)
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

static u8 PlaceOneHandCardOnDeckTop(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot->id == CARD_NONE)
      continue;

    cardId = slot->id;
    ClearZone(slot);
    if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
      gDuelDecks[fixedDuelist].cardsDrawn--;
    gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
    return TRUE;
  }

  return FALSE;
}

static u8 CanAtkPath(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindMorphtronicSpellTrapInDeck() != CARD_NONE;
}

static u8 CanDefPath(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindLvLe4MorphtronicInDeck() != CARD_NONE;
}

unsigned char CanActivateMORPHTRONIC_SCANNEN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_SCANNEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_SCANNEN)
    return FALSE;

  /* ponytail: FromHand banish Morphtronic → SS; ATK/DEF OPT search modes. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->isDefending)
    return CanDefPath();

  return CanAtkPath();
}

void ActivateMORPHTRONIC_SCANNENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(MORPHTRONIC_SCANNEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->isDefending) {
    cardId = FindLvLe4MorphtronicInDeck();
    if (cardId == CARD_NONE || !AddCardFromDeckToHand(cardId))
      return;
  } else {
    cardId = FindMorphtronicSpellTrapInDeck();
    if (cardId == CARD_NONE || !AddCardFromDeckToHand(cardId))
      return;

    PlaceOneHandCardOnDeckTop();
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonMorphtronicScannenFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MORPHTRONIC_SCANNEN)
    return FALSE;

  if (FindOtherMorphtronicHandZone(handZone) < 0)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonMorphtronicScannenFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 banishZone;

  if (!CanSpecialSummonMorphtronicScannenFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MORPHTRONIC_SCANNEN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  banishZone = FindOtherMorphtronicHandZone(handZone);
  if (banishZone < 0)
    return FALSE;

  if (Duel_BanishZone(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)banishZone),
                      TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

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
u8 CanSpecialSummonMorphtronicScannenFromHand(u8 handZone);
u8 TrySpecialSummonMorphtronicScannenFromHand(u8 handZone);
#endif
