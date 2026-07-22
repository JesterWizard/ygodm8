#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
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

static u8 IsLevel4OrLowerMorphtronic(u16 cardId)
{
  if (!IsMorphtronicMonster(cardId))
    return FALSE;

  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].level <= 4;
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

static u16 FindLv4MorphtronicAmongTop(u8 count)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = 0; i < count; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[top + i];

    if (IsLevel4OrLowerMorphtronic(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindAnyMorphtronicAmongTop(u8 count)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = 0; i < count; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[top + i];

    if (IsMorphtronicMonster(cardId))
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

unsigned char CanActivateMORPHTRONIC_CELFON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_CELFON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_CELFON)
    return FALSE;

  /* Ceiling: reveal/look UI missing; die roll + SS/add among top N.
   * Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (DeckCardsRemaining() == 0)
    return FALSE;

  if (zone->isDefending) {
    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      return FALSE;
    return TRUE;
  }

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateMORPHTRONIC_CELFONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 remaining;
  u8 roll;
  u8 peek;
  u16 cardId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(MORPHTRONIC_CELFON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  remaining = DeckCardsRemaining();
  if (remaining == 0)
    return;

  roll = RandRangeU8(1, 6);
  peek = roll;
  if (peek > remaining)
    peek = remaining;

  if (self->isDefending) {
    cardId = FindAnyMorphtronicAmongTop(peek);
    if (cardId == CARD_NONE) {
      Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      return;
    }

    if (!AddMorphtronicFromDeckToHand(cardId))
      return;
  } else {
    if (ArchlordKristya_IsSpecialSummonLocked()
        || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      return;

    cardId = FindLv4MorphtronicAmongTop(peek);
    if (cardId == CARD_NONE) {
      Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      return;
    }

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      return;

    Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
