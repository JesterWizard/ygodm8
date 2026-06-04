#include "global.h"
#include "common-chax.h"
#include "graveyard_effects.h"

u8 gDeferGraveyardDrawBattleResolve;

u8 CardTriggersDrawOnFieldDestroy(u16 cardId)
{
  return cardId == SANGAN || cardId == WITCH_OF_THE_BLACK_FOREST;
}

static u8 GraveyardScanDuelistToFixed(u8 duelist)
{
  if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

unsigned char ShouldActivateGraveyardDrawOnDestroy(void)
{
  if (gDeferGraveyardDrawBattleResolve)
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
  u8 hideEffectText;
  u16 cardId;

  cardId = gActiveEffect.cardId;

  if (gActiveEffect.turnRow == 6)
    fixedDuelist = GraveyardScanDuelistToFixed(ACTIVE_DUELIST);
  else
    fixedDuelist = GraveyardScanDuelistToFixed(INACTIVE_DUELIST);

  TryDrawingCard(fixedDuelist);
  GetGraveCardAndClearGrave2(fixedDuelist);

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  gCardEffectTextData.cardId = cardId;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;
}

void FinishGraveyardDrawBattleResolve(void)
{
  gDeferGraveyardDrawBattleResolve = FALSE;
}
