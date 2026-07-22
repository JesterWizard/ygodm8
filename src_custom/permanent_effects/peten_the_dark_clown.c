#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "graveyard_effects.h"

static u8 HandHasPeten(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == PETEN_THE_DARK_CLOWN)
      return TRUE;
  }

  return FALSE;
}

static u8 IsPetenTheDarkClown(u16 cardId)
{
  return cardId == PETEN_THE_DARK_CLOWN;
}

static s8 PickPetenHandZone(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == PETEN_THE_DARK_CLOWN)
      return i;
  }

  return -1;
}

static u8 CanSpecialSummonPeten(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  if (HandHasPeten(gTurnHands[turnDuelist]))
    return TRUE;

  return Duel_FindDeckCardIndex(turnDuelist, PETEN_THE_DARK_CLOWN) >= 0;
}

static void TrySpecialSummonPeten(u8 turnDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  s8 handZone = -1;

  if (!CanSpecialSummonPeten(turnDuelist))
    return;

  if (HandHasPeten(handRow)) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
      handZone = SelectHandCardMatchingPredicate(handRow, IsPetenTheDarkClown);
    else
      handZone = PickPetenHandZone(handRow);

    if (handZone >= 0) {
      Duel_SpecialSummonFromHandZone(turnDuelist, handZone, opts);
      return;
    }
  }

  // hand takes priority when both are available; deck is the fallback
  Duel_SpecialSummonFromDeck(turnDuelist, PETEN_THE_DARK_CLOWN, opts);
}

unsigned char ShouldActivatePetenTheDarkClown(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != PETEN_THE_DARK_CLOWN)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != PETEN_THE_DARK_CLOWN)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != PETEN_THE_DARK_CLOWN)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  return CanSpecialSummonPeten(turnDuelist);
}

void ActivatePetenTheDarkClown(void)
{
  u8 turnDuelist;

  if (gActiveEffect.turnRow == 7)
    turnDuelist = INACTIVE_DUELIST;
  else
    turnDuelist = ACTIVE_DUELIST;

  Duel_ShowEffectText(PETEN_THE_DARK_CLOWN);
  GetGraveCardAndClearGrave(turnDuelist);
  TrySpecialSummonPeten(turnDuelist);
}
