#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"

static u8 TurnDuelistForGraveyardRow(u8 turnRow)
{
  if (turnRow == 7)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 CanSpecialSummonLightSerpent(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

unsigned char ShouldActivateLIGHT_SERPENT(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  /* Hand/deck send stand-in: !gGraveyardSendWasFromField. */
  if (gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != LIGHT_SERPENT)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != LIGHT_SERPENT)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != LIGHT_SERPENT)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  return CanSpecialSummonLightSerpent(turnDuelist);
}

void ActivateLIGHT_SERPENT(void)
{
  u8 turnDuelist;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  turnDuelist = TurnDuelistForGraveyardRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(LIGHT_SERPENT, 8);
  if (IsDuelOver() == TRUE)
    return;

  Duel_SpecialSummonFromGrave(turnDuelist, LIGHT_SERPENT, opts);
}
