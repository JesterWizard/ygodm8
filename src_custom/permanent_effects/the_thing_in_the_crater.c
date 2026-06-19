#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "graveyard_effects.h"
#include "the_thing_in_the_crater.h"

extern void ActivatePermanentEffectCardText(u16 cardId);

static u8 IsPyroSummonTarget(u16 cardId)
{
  return Duel_CardHasMonsterType(cardId, TYPE_PYRO);
}

static u8 HandHasPyroTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsPyroSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonPyro(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (!HandHasPyroTarget(gTurnHands[turnDuelist]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return TRUE;
}

static s8 PickPyroHandZone(struct DuelCard **handRow, u8 pickHighestAtk)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!IsPyroSummonTarget(cardId))
      continue;

    if (!pickHighestAtk)
      return i;

    SetCardInfo(cardId);
    if (chosenZone < 0 || gCardInfo.atk > bestAtk) {
      chosenZone = i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenZone;
}

static void TrySpecialSummonPyro(u8 turnDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;

  if (!CanSpecialSummonPyro(turnDuelist))
    return;

  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]) {
    Duel_SpecialSummonFromHand(turnDuelist, CARD_NONE, IsPyroSummonTarget, opts);
    return;
  }

  handZone = PickPyroHandZone(handRow, TRUE);
  if (handZone < 0)
    return;

  Duel_SpecialSummonFromHandZone(turnDuelist, handZone, opts);
}

static u8 GraveyardMatchesTheThingInTheCrater(u8 turnRow)
{
  if (turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == THE_THING_IN_THE_CRATER;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == THE_THING_IN_THE_CRATER;
}

unsigned char ShouldActivateTheThingInTheCrater(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != THE_THING_IN_THE_CRATER)
    return FALSE;

  if (!GraveyardMatchesTheThingInTheCrater(gActiveEffect.turnRow))
    return FALSE;

  turnDuelist = (gActiveEffect.turnRow == 7) ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  return CanSpecialSummonPyro(turnDuelist);
}

void ActivateTheThingInTheCrater(void)
{
  u8 turnDuelist;
  u8 hideEffectText;

  if (gActiveEffect.turnRow == 7)
    turnDuelist = INACTIVE_DUELIST;
  else
    turnDuelist = ACTIVE_DUELIST;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  ActivatePermanentEffectCardText(THE_THING_IN_THE_CRATER);
  gHideEffectText = hideEffectText;

  GetGraveCardAndClearGrave(turnDuelist);
  TrySpecialSummonPyro(turnDuelist);
}
