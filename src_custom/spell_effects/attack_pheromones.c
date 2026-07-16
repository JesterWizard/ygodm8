#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static void ATTACK_PHEROMONES_ResolveBody(void)
{
  Duel_ShowEffectText(ATTACK_PHEROMONES);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectATTACK_PHEROMONES(void)
{
  if (Duel_TryResolveSpellThroughTraps(ATTACK_PHEROMONES, ATTACK_PHEROMONES_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
