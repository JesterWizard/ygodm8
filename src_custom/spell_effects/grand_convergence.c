#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define GRAND_CONVERGENCE_DAMAGE 300

static u8 FixedDuelistYouControl(void)
{
  return WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static u8 ControlsMacroCosmos(void)
{
  return Duel_FindBackrowCard(FixedDuelistYouControl(), MACRO_COSMOS, TRUE) != NULL;
}

u8 CanActivateGRAND_CONVERGENCE(void)
{
  return ControlsMacroCosmos();
}

static void GRAND_CONVERGENCE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(GRAND_CONVERGENCE);

  if (IsDuelOver() == TRUE || !CanActivateGRAND_CONVERGENCE())
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -GRAND_CONVERGENCE_DAMAGE, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyAllMonstersMatching(ACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyAllMonstersMatching(INACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectGRAND_CONVERGENCE(void)
{
  if (!CanActivateGRAND_CONVERGENCE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(GRAND_CONVERGENCE, GRAND_CONVERGENCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
