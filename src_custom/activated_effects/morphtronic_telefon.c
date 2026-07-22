#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
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

static u8 CardLevel(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].level;
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

static u16 FindMorphLvLeInGy(u8 maxLevel)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsMorphtronicMonster(cardId) && CardLevel(cardId) > 0
        && CardLevel(cardId) <= maxLevel
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;

    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsMorphtronicMonster(cardId) || CardLevel(cardId) == 0
        || CardLevel(cardId) > maxLevel)
      continue;

    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    return cardId;
  }

  return CARD_NONE;
}

static u8 SpecialSummonMorphFromGy(u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (cardId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) == DUEL_ACTION_OK;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != cardId)
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) == DUEL_ACTION_OK;
  }

  return FALSE;
}

unsigned char CanActivateMORPHTRONIC_TELEFON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_TELEFON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_TELEFON)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (EffectOpt_IsUsed(MORPHTRONIC_TELEFON))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->isDefending) {
    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      return FALSE;
    return DeckCardsRemaining() > 0;
  }

  return TRUE;
}

void ActivateMORPHTRONIC_TELEFONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 remaining;
  u8 roll;
  u8 peek;
  u16 cardId;

  Duel_ShowEffectTextTyped(MORPHTRONIC_TELEFON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(MORPHTRONIC_TELEFON))
    return;

  remaining = DeckCardsRemaining();
  roll = RandRangeU8(1, 6);

  if (self->isDefending) {
    if (remaining == 0)
      return;

    peek = roll;
    if (peek > remaining)
      peek = remaining;

    cardId = FindMorphtronicAmongTop(peek);
    if (cardId == CARD_NONE) {
      Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
      EffectOpt_MarkUsed(MORPHTRONIC_TELEFON);
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      return;
    }

    if (!AddMorphtronicFromDeckToHand(cardId))
      return;
  } else {
    if (Duel_ChangeLp(ACTIVE_DUELIST, (s32)roll * 100, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    cardId = FindMorphLvLeInGy(roll);
    if (cardId != CARD_NONE)
      SpecialSummonMorphFromGy(cardId);
  }

  EffectOpt_MarkUsed(MORPHTRONIC_TELEFON);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
