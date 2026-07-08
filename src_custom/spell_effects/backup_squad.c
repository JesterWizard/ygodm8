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

static void BACKUP_SQUAD_ResolveBody(void)
{
  Duel_ShowEffectText(BACKUP_SQUAD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectBACKUP_SQUAD(void)
{
  if (Duel_TryResolveSpellThroughTraps(BACKUP_SQUAD, BACKUP_SQUAD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
