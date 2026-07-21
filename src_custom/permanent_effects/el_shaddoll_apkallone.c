#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "el_shaddoll_apkallone.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "six_card_hand.h"

u8 ElShaddollApkallone_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == EL_SHADDOLL_APKALLONE && zone->isFaceUp;
}

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 TurnDuelistFromGraveyardRow(u8 turnRow)
{
  if (turnRow == 7)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsShaddollCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static u8 IsFaceUpNegateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW
      && fixedRow != PLAYER_BACKROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->isFaceUp;
}

static u8 FieldHasFaceUpNegateTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpNegateTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveNegateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!IsFaceUpNegateTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  zone->unk4 |= 0x80;

  if (self != NULL)
    self->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  PlayMusic(SFX_CANCEL);
  if (self != NULL)
    self->unk4 = 1;
}

static u8 AiPickNegateTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpNegateTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static u16 FindShaddollInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsShaddollCard(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static s16 FindShaddollGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsShaddollCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u8 AddShaddollToHandFromDeckOrGy(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;
  s16 gyIndex;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = FindShaddollInDeck(turnDuelist);
  if (cardId != CARD_NONE) {
    if (Duel_AddDeckCardToHand(turnDuelist, cardId, FALSE) != DUEL_ACTION_OK)
      return FALSE;
    return TRUE;
  }

  gyIndex = FindShaddollGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsShaddollCard(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);
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
  return TRUE;
}

static u8 CanAddShaddollThenDiscard(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  if (FindShaddollInDeck(turnDuelist) != CARD_NONE)
    return TRUE;

  return FindShaddollGyIndex(fixedDuelist) >= 0;
}

static u8 IsApkalloneOnSummonTrigger(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != EL_SHADDOLL_APKALLONE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return FieldHasFaceUpNegateTarget();
}

static u8 IsApkalloneGraveyardTrigger(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != EL_SHADDOLL_APKALLONE)
    return FALSE;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != EL_SHADDOLL_APKALLONE)
      return FALSE;
  } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != EL_SHADDOLL_APKALLONE) {
    return FALSE;
  }

  return CanAddShaddollThenDiscard(turnDuelist);
}

unsigned char ShouldActivateEL_SHADDOLL_APKALLONE(void)
{
  /* Battle indestructible is live via ElShaddollApkallone_PreventsBattleDestroy. */
  if (IsApkalloneOnSummonTrigger())
    return TRUE;

  return IsApkalloneGraveyardTrigger();
}

void ActivateEL_SHADDOLL_APKALLONE(void)
{
  u8 turnDuelist;

  if (IsApkalloneOnSummonTrigger()) {
    Duel_ShowEffectTextTyped(EL_SHADDOLL_APKALLONE, 8);

    if (IsDuelOver() == TRUE)
      return;

    gDuelCursor.destY = gActiveEffect.turnRow;
    gDuelCursor.destX = gActiveEffect.col;

    Duel_SetupPickZone(IsFaceUpNegateTarget, ResolveNegateTarget, CancelTargeting,
                       AiPickNegateTarget);

    if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(EL_SHADDOLL_APKALLONE, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (!AddShaddollToHandFromDeckOrGy(turnDuelist))
    return;

  Duel_DiscardRandomFromHand(turnDuelist, 1, TRUE);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
