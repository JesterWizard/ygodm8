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

static void BOND_BETWEEN_TEACHER_AND_STUDENT_ResolveBody(void)
{
  Duel_ShowEffectText(BOND_BETWEEN_TEACHER_AND_STUDENT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectBOND_BETWEEN_TEACHER_AND_STUDENT(void)
{
  if (Duel_TryResolveSpellThroughTraps(BOND_BETWEEN_TEACHER_AND_STUDENT, BOND_BETWEEN_TEACHER_AND_STUDENT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
