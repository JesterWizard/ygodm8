#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "el_shaddoll_winda.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

/* Bit0 = ACTIVE already SS'd this turn while Winda up; bit1 = INACTIVE. */
static u8 sWindaSsUsed APPEND_DATA = {0};

static u8 FaceUpWindaOnField(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp && zone->id == EL_SHADDOLL_WINDA)
        return TRUE;
    }
  }

  return FALSE;
}

u8 ElShaddollWinda_PreventsDestroy(const struct DuelCard *zone)
{
  /* Opponent's card effects — effect-destroy path only (not battle). */
  return zone != NULL && zone->id == EL_SHADDOLL_WINDA && zone->isFaceUp;
}

u8 ElShaddollWinda_IsSpecialSummonLockedFor(u8 turnDuelist)
{
  u8 bit;

  if (!FaceUpWindaOnField())
    return FALSE;

  bit = (turnDuelist == ACTIVE_DUELIST) ? 1 : 2;
  return (sWindaSsUsed & bit) != 0;
}

void ElShaddollWinda_OnSpecialSummon(u8 turnDuelist)
{
  if (!FaceUpWindaOnField())
    return;

  if (turnDuelist == ACTIVE_DUELIST)
    sWindaSsUsed |= 1;
  else
    sWindaSsUsed |= 2;
}

void ElShaddollWinda_ClearTurnState(void)
{
  sWindaSsUsed = 0;
}

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

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

static u8 IsShaddollSpellTrap(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static s16 FindShaddollSpellTrapGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsShaddollSpellTrap(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u8 CanAddShaddollSpellTrapFromGy(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FindShaddollSpellTrapGyIndex(fixedDuelist) >= 0;
}

static u8 AddShaddollSpellTrapFromGyToHand(u8 turnDuelist, s16 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsShaddollSpellTrap(cardId))
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

static u8 IsWindaGraveyardTrigger(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != EL_SHADDOLL_WINDA)
    return FALSE;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != EL_SHADDOLL_WINDA)
      return FALSE;
  } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != EL_SHADDOLL_WINDA) {
    return FALSE;
  }

  return CanAddShaddollSpellTrapFromGy(turnDuelist);
}

unsigned char ShouldActivateEL_SHADDOLL_WINDA(void)
{
  /* Destroy immunity + SS-once lock live via ElShaddollWinda_*. */
  return IsWindaGraveyardTrigger();
}

void ActivateEL_SHADDOLL_WINDA(void)
{
  u8 turnDuelist;
  u8 fixedDuelist;
  s16 gyIndex;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  Duel_ShowEffectTextTyped(EL_SHADDOLL_WINDA, 8);
  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindShaddollSpellTrapGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  if (!AddShaddollSpellTrapFromGyToHand(turnDuelist, gyIndex))
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
