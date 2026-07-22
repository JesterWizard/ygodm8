#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"

#define AMEBA_CONTROL_SWITCH_DAMAGE 2000
#define AMEBA_MAX_PENDING 2

extern u8 gAmebaPendingCount;
extern u8 gAmebaPendingDamageTarget0;
extern u8 gAmebaPendingDamageTarget1;
extern u8 gAmebaFlushing;

void Duel_NotifyMonsterControlSwitched(u16 cardId, u8 newFixedRow)
{
  u8 damageTarget;

  if (cardId != AMEBA)
    return;

  /* AI candidate sim runs real effect code but restores duel state;
   * do not queue burns that survive into the chosen action. */
  if (gHideEffectText == TRUE)
    return;

  if (newFixedRow != PLAYER_MONSTER_ROW && newFixedRow != OPPONENT_MONSTER_ROW)
    return;

  if (gAmebaPendingCount >= AMEBA_MAX_PENDING)
    return;

  damageTarget = Duel_FixedDuelistForMonsterRow(newFixedRow);

  if (gAmebaPendingCount == 0)
    gAmebaPendingDamageTarget0 = damageTarget;
  else
    gAmebaPendingDamageTarget1 = damageTarget;

  gAmebaPendingCount++;
}

void Duel_FlushMonsterControlSwitchEffects(void)
{
  u8 count;
  u8 damageTarget;
  u8 damageTarget0;
  u8 damageTarget1;
  u8 i;

  if (gHideEffectText == TRUE || gAmebaFlushing || gAmebaPendingCount == 0)
    return;

  gAmebaFlushing = TRUE;
  count = gAmebaPendingCount;
  damageTarget0 = gAmebaPendingDamageTarget0;
  damageTarget1 = gAmebaPendingDamageTarget1;
  gAmebaPendingCount = 0;

  for (i = 0; i < count; i++) {
    if (IsDuelOver() == TRUE)
      break;

    damageTarget = (i == 0) ? damageTarget0 : damageTarget1;

    Duel_ShowEffectTextTyped(AMEBA, 1);

    if (IsDuelOver() == TRUE)
      break;

    /* Skip nested UpdateDuelGfxExceptField; caller just refreshed field. */
    Duel_ChangeLp(damageTarget, -AMEBA_CONTROL_SWITCH_DAMAGE, FALSE);
  }

  gAmebaFlushing = FALSE;
}
