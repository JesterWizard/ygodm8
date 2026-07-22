#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "gladiator_beast_battled.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 ControlsOtherFaceUpSagittarii(u8 fixedDuelist, struct DuelCard *exclude)
{
  u8 monRow = fixedDuelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[monRow][col];

    if (zone == NULL || zone == exclude || zone->id != GLADIATOR_BEAST_SAGITTARII)
      continue;

    if (IsCardFaceUp(zone) || zone->isDefending == FALSE)
      return TRUE;
  }

  return FALSE;
}

static s8 FindGladiatorBeastHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i)->id;

    if (IsGladiatorBeastMonster(cardId))
      return (s8)i;
  }

  return -1;
}

static u8 IsOtherGladiatorBeastInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return TRUE;
  }

  return FALSE;
}

static u16 FindOtherGladiatorBeastInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return cardId;
  }

  return CARD_NONE;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void ShuffleSelfTagOut(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 tagId;

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  tagId = FindOtherGladiatorBeastInDeck(GLADIATOR_BEAST_SAGITTARII);
  if (tagId == CARD_NONE)
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, tagId, opts);
}

/* When a GB is SS while another face-up Sagittarii is controlled: discard 1 GB; draw 2.
 * Deck-source not distinguished (any Special Summon stand-in). */
void TryGladiatorBeastSagittariiOnMonsterPlacement(struct DuelCard *zone,
                                                   enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 handZone;

  if (zone == NULL || !IsGladiatorBeastMonster(zone->id) || !SummonModeIsSpecial(mode))
    return;

  if (gHideEffectText)
    return;

  if (EffectOpt_IsUsed(GLADIATOR_BEAST_SAGITTARII))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  if (!ControlsOtherFaceUpSagittarii(fixedDuelist, zone))
    return;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  handZone = FindGladiatorBeastHandZone(turnDuelist);
  if (handZone < 0)
    return;

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_SAGITTARII, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       turnDuelist, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(GLADIATOR_BEAST_SAGITTARII);
  Duel_DrawCards(turnDuelist, 2, TRUE);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateGLADIATOR_BEAST_SAGITTARII(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_SAGITTARII)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_SAGITTARII)
    return FALSE;

  /* End-of-BP + battled via GladiatorBeast_CanActivateTagOutEffect.
   * OPT shuffle self into Deck then SS another Gladiator Beast from Deck.
   * GB-SS discard→draw via TryGladiatorBeastSagittariiOnMonsterPlacement. */
  if (!GladiatorBeast_CanActivateTagOutEffect(zone))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return IsOtherGladiatorBeastInDeck(GLADIATOR_BEAST_SAGITTARII);
}

void ActivateGLADIATOR_BEAST_SAGITTARIIEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_SAGITTARII, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfTagOut(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
