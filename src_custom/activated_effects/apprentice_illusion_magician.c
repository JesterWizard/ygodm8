#include "global.h"
#include "apprentice_illusion_magician.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

static u8 HandHasOtherCard(u8 selfHandZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (i == selfHandZone)
      continue;

    if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 DiscardOtherCardExceptZone(u8 exceptZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot;

    if (i == exceptZone)
      continue;

    slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);
    if (slot->id == CARD_NONE)
      continue;

    return Duel_DestroyZone(slot, ACTIVE_DUELIST, TRUE) != DUEL_ACTION_DUEL_OVER;
  }

  return FALSE;
}

static u16 FindDarkMagicianInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == DARK_MAGICIAN)
      return DARK_MAGICIAN;
  }

  return CARD_NONE;
}

static u8 AddDarkMagicianFromDeckToHandFor(u8 turnDuelist)
{
  s16 deckIndex;
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, DARK_MAGICIAN);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), DARK_MAGICIAN);
  return TRUE;
}

static u8 AddDarkMagicianFromDeckToHand(void)
{
  return AddDarkMagicianFromDeckToHandFor(ACTIVE_DUELIST);
}

void TryApprenticeIllusionMagicianOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != APPRENTICE_ILLUSION_MAGICIAN)
    return;

  if (EffectOpt_IsUsed(APPRENTICE_ILLUSION_MAGICIAN))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
                    ? ACTIVE_DUELIST
                    : INACTIVE_DUELIST;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  if (Duel_FindDeckCardIndex(turnDuelist, DARK_MAGICIAN) < 0)
    return;

  Duel_ShowEffectTextTyped(APPRENTICE_ILLUSION_MAGICIAN, 8);

  if (!AddDarkMagicianFromDeckToHandFor(turnDuelist))
    return;

  EffectOpt_MarkUsed(APPRENTICE_ILLUSION_MAGICIAN);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateAPPRENTICE_ILLUSION_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != APPRENTICE_ILLUSION_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != APPRENTICE_ILLUSION_MAGICIAN)
    return FALSE;

  /* On-NS/SS search via TryApprenticeIllusionMagicianOnMonsterPlacement (EffectOpt).
   * OPT add Dark Magician from Deck (shares EffectOpt with on-summon).
   * Ceiling: hand/field send +2000 Quick need damage hooks. */
  if (EffectOpt_IsUsed(APPRENTICE_ILLUSION_MAGICIAN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDarkMagicianInDeck() != CARD_NONE;
}

void ActivateAPPRENTICE_ILLUSION_MAGICIANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(APPRENTICE_ILLUSION_MAGICIAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!AddDarkMagicianFromDeckToHand())
    return;

  EffectOpt_MarkUsed(APPRENTICE_ILLUSION_MAGICIAN);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonApprenticeIllusionMagicianFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != APPRENTICE_ILLUSION_MAGICIAN)
    return FALSE;

  if (!HandHasOtherCard(handZone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonApprenticeIllusionMagicianFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonApprenticeIllusionMagicianFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(APPRENTICE_ILLUSION_MAGICIAN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!DiscardOtherCardExceptZone(handZone))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonApprenticeIllusionMagicianFromHand(u8 handZone);
u8 TrySpecialSummonApprenticeIllusionMagicianFromHand(u8 handZone);
#endif
