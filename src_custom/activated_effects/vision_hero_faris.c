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

static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sVisionHeroName[] APPEND_RODATA = "Vision HERO";

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

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static u8 IsOtherVisionHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == VISION_HERO_FARIS)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sVisionHeroName);
}

static u8 HandHasOtherHero(u8 farisHandZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (i == farisHandZone)
      continue;

    if (IsHeroMonster(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      return TRUE;
  }

  return FALSE;
}

static u8 DiscardOtherHeroExceptZone(u8 exceptZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot;

    if (i == exceptZone)
      continue;

    slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);
    if (!IsHeroMonster(slot->id))
      continue;

    return Duel_DestroyZone(slot, ACTIVE_DUELIST, TRUE) != DUEL_ACTION_DUEL_OVER;
  }

  return FALSE;
}

static u16 FindVisionHeroInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsOtherVisionHeroMonster(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }

  return CARD_NONE;
}

static u8 AddVisionHeroFromDeckToHand(u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0 || cardId == CARD_NONE)
    return FALSE;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] != cardId)
      continue;

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      return FALSE;

    Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateVISION_HERO_FARIS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != VISION_HERO_FARIS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != VISION_HERO_FARIS)
    return FALSE;

  /* ponytail: Continuous Trap place + ED HERO lock need place/ED hooks.
   * Ceiling: OPT add 1 Vision HERO from Deck to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindVisionHeroInDeck() != CARD_NONE;
}

void ActivateVISION_HERO_FARISEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(VISION_HERO_FARIS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindVisionHeroInDeck();
  if (cardId == CARD_NONE)
    return;

  if (!AddVisionHeroFromDeckToHand(cardId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonVisionHeroFarisFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != VISION_HERO_FARIS)
    return FALSE;

  if (!HandHasOtherHero(handZone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonVisionHeroFarisFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonVisionHeroFarisFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(VISION_HERO_FARIS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!DiscardOtherHeroExceptZone(handZone))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonVisionHeroFarisFromHand(u8 handZone);
u8 TrySpecialSummonVisionHeroFarisFromHand(u8 handZone);
#endif
