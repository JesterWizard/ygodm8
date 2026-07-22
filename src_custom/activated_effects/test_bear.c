#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
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

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 ControlsFaceUpGladiatorBeast(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && IsGladiatorBeastMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 CountDeckGladiatorBeasts(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 count = 0;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsGladiatorBeastMonster(gDuelDecks[fixedDuelist].cards[i]))
      count++;
  }

  return count;
}

static u8 IsOtherFaceUpGladiatorTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (fixedRow != gMonEffect.row)
    return FALSE;

  if (zone == NULL || zone == self || zone->id == CARD_NONE)
    return FALSE;

  return zone->isFaceUp && IsGladiatorBeastMonster(zone->id);
}

static u8 HasOtherFaceUpGladiatorTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOtherFaceUpGladiatorTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static struct DuelCard *FindHandGladiatorBeast(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *zone = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (zone != NULL && IsGladiatorBeastMonster(zone->id))
      return zone;
  }

  return NULL;
}

static void SpecialSummonUpToTwoGladiatorBeastsFromDeck(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 summoned = 0;

  while (summoned < 2) {
    u8 fixedDuelist = FixedDuelistForActive();
    u8 deckSize = NumCardsInDeck(fixedDuelist);
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
    u16 cardId = CARD_NONE;
    u8 i;

    if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;

    for (i = top; i < deckSize; i++) {
      if (IsGladiatorBeastMonster(gDuelDecks[fixedDuelist].cards[i])) {
        cardId = gDuelDecks[fixedDuelist].cards[i];
        break;
      }
    }

    if (cardId == CARD_NONE)
      break;

    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      break;

    summoned++;
    if (IsDuelOver() == TRUE)
      return;
  }
}

static void ResolveShuffleTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (!IsOtherFaceUpGladiatorTarget(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  cardId = target->id;
  ClearZone(self);
  ClearZone(target);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (!ArchlordKristya_IsSpecialSummonLocked())
    SpecialSummonUpToTwoGladiatorBeastsFromDeck();

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickGladiatorTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOtherFaceUpGladiatorTarget(gMonEffect.row, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveHandShufflePath(struct DuelCard *self)
{
  struct DuelCard *handGb = FindHandGladiatorBeast();
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (self == NULL || handGb == NULL)
    return;

  cardId = handGb->id;
  ClearZone(self);
  ClearZone(handGb);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (!ArchlordKristya_IsSpecialSummonLocked())
    SpecialSummonUpToTwoGladiatorBeastsFromDeck();

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateTEST_BEAR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TEST_BEAR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TEST_BEAR)
    return FALSE;

  /* Deck/ED-summoned GB gate for hand SS relaxed to any face-up GB.
   * Ceiling: OPT tribute self + shuffle 1 GB → SS up to 2 GB from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (CountDeckGladiatorBeasts() == 0)
    return FALSE;

  return HasOtherFaceUpGladiatorTarget() || FindHandGladiatorBeast() != NULL;
}

void ActivateTEST_BEAREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(TEST_BEAR, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (HasOtherFaceUpGladiatorTarget()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;

    Duel_SetupPickZone(IsOtherFaceUpGladiatorTarget, ResolveShuffleTarget, CancelTargeting,
                       AiPickGladiatorTarget);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  ResolveHandShufflePath(self);
}

u8 CanSpecialSummonTestBearFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != TEST_BEAR)
    return FALSE;

  /* printed needs GB SS from Deck/ED; stand-in = any face-up GB. */
  if (!ControlsFaceUpGladiatorBeast())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonTestBearFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonTestBearFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(TEST_BEAR, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonTestBearFromHand(u8 handZone);
u8 TrySpecialSummonTestBearFromHand(u8 handZone);
#endif
