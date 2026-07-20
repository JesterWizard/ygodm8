#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

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

/* Body lives in effect_scripts.c (Phase 4 C table). */
APPEND_TEXT void EffectGRAND_CONVERGENCE(void)
{
  const struct EffectScript *script = EffectScript_Find(GRAND_CONVERGENCE, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
