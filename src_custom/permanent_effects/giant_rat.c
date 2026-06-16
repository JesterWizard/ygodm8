#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"
#include "giant_rat.h"

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanSpecialSummonGiantRat(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(turnDuelist, GIANT_RAT) >= 0;
}

void MarkGiantRatBattleDestruction(u8 fixedDuelist, u16 cardId)
{
  if (cardId == GIANT_RAT)
    gGiantRatBattleDestroyMask |= (1 << fixedDuelist);
}

unsigned char ShouldActivateGiantRat(void)
{
  u8 turnDuelist;
  u8 fixedDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != GIANT_RAT)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != GIANT_RAT)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != GIANT_RAT)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  if ((gGiantRatBattleDestroyMask & (1 << fixedDuelist)) == 0)
    return FALSE;

  return CanSpecialSummonGiantRat(turnDuelist);
}

void ActivateGiantRat(void)
{
  u8 turnDuelist;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (gActiveEffect.turnRow == 7)
    turnDuelist = INACTIVE_DUELIST;
  else
    turnDuelist = ACTIVE_DUELIST;

  Duel_ShowEffectText(GIANT_RAT);
  GetGraveCardAndClearGrave(turnDuelist);
  gGiantRatBattleDestroyMask &= ~(1 << FixedDuelistForTurnDuelist(turnDuelist));
  Duel_SpecialSummonFromDeck(turnDuelist, GIANT_RAT, opts);
}
