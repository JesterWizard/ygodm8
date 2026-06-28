#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"

extern void UpdateDuelGfxExceptField(void);

static u8 ZoneIsHandSlot(struct DuelCard *zone)
{
  u8 i;
  u8 j;

  if (zone == NULL)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[PLAYER_HAND][i] == zone)
      return TRUE;
  }

  for (i = 0; i < 2; i++) {
    for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
      if (gTurnHands[i][j] == zone)
        return TRUE;
    }
  }

  return FALSE;
}

void NoteGraveyardMonsterSend(struct DuelCard *zone)
{
  gGraveyardSendWasFromField = ZoneIsHandSlot(zone) ? FALSE : TRUE;
}

void MarkGraveyardSendFromField(void)
{
  gGraveyardSendWasFromField = TRUE;
}

u8 CardTriggersDrawOnFieldDestroy(u16 cardId)
{
  return cardId == SANGAN || cardId == WITCH_OF_THE_BLACK_FOREST;
}

u8 CardDefersGraveyardEffectUntilBattleFinish(u16 cardId)
{
  return CardTriggersDrawOnFieldDestroy(cardId) || cardId == FAMILIAR_KNIGHT
      || cardId == KAISER_GLIDER || cardId == PETEN_THE_DARK_CLOWN
      || cardId == GIANT_RAT || cardId == THE_THING_IN_THE_CRATER;
}

static u8 GraveyardScanDuelistToFixed(u8 duelist)
{
  if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistToTurnDuelist(u8 fixedDuelist)
{
  u8 turnDuelist;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist])
      return turnDuelist;
  }

  return ACTIVE_DUELIST;
}

unsigned char ShouldActivateGraveyardDrawOnDestroy(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (!CardTriggersDrawOnFieldDestroy(gActiveEffect.cardId))
    return FALSE;

  if (gActiveEffect.turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == gActiveEffect.cardId;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == gActiveEffect.cardId;
}

void ActivateGraveyardDrawOnDestroy(void)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u8 hideEffectText;
  u16 cardId;

  cardId = gActiveEffect.cardId;

  if (gActiveEffect.turnRow == 6) {
    turnDuelist = ACTIVE_DUELIST;
    fixedDuelist = GraveyardScanDuelistToFixed(ACTIVE_DUELIST);
  } else {
    turnDuelist = INACTIVE_DUELIST;
    fixedDuelist = GraveyardScanDuelistToFixed(INACTIVE_DUELIST);
  }

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  ActivatePermanentEffectCardText(cardId);
  gHideEffectText = hideEffectText;

  GetGraveCardAndClearGrave(turnDuelist);
  gPendingGraveyardDrawFixedDuelist = fixedDuelist;
}

void ResolvePendingGraveyardDrawOnDestroy(void)
{
  u8 fixedDuelist = gPendingGraveyardDrawFixedDuelist;
  u8 turnDuelist;

  if (fixedDuelist == PENDING_GRAVEYARD_DRAW_NONE)
    return;

  gPendingGraveyardDrawFixedDuelist = PENDING_GRAVEYARD_DRAW_NONE;
  turnDuelist = FixedDuelistToTurnDuelist(fixedDuelist);
  Duel_DrawCards(turnDuelist, 1, TRUE);
  if (!gHideEffectText)
    PlayMusic(SFX_DRAW_CARD);
  SetCardInfo(CARD_NONE);
}

void FinishGraveyardDrawBattleResolve(void)
{
  gDeferGraveyardDrawBattleResolve = FALSE;
}
