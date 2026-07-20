#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "effect_ops.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spirit_of_the_pot_of_greed.h"
#include "card.h"
#include "constants/spell_effects.h"

u8 CanActivateGRAND_CONVERGENCE(void);

/* ── One Day of Peace: both draw 1, send this to GY ── */

static const struct EffectScriptStep sOneDayOfPeaceSteps[] __attribute__((section(".text"))) = {
  { EFFECT_SCRIPT_SHOW_TEXT, 0, 0, 0, 0 },
  { EFFECT_SCRIPT_DRAW, ACTIVE_DUELIST, 1, FALSE, 0 },
  { EFFECT_SCRIPT_DRAW, INACTIVE_DUELIST, 1, TRUE, 0 },
  { EFFECT_SCRIPT_DESTROY_ACTIVATING_SPELL, ACTIVE_DUELIST, 0, TRUE, 0 },
  { EFFECT_SCRIPT_END, 0, 0, 0, 0 },
};

/* ── Pot of Greed: draw 2, send this to GY ── */

static const struct EffectScriptStep sPotOfGreedSteps[] __attribute__((section(".text"))) = {
  { EFFECT_SCRIPT_SHOW_TEXT, 0, 0, 0, 0 },
  { EFFECT_SCRIPT_DRAW, ACTIVE_DUELIST, 2, FALSE, 0 },
  { EFFECT_SCRIPT_DESTROY_ACTIVATING_SPELL, ACTIVE_DUELIST, 0, TRUE, 0 },
  { EFFECT_SCRIPT_END, 0, 0, 0, 0 },
};

/* ── Grand Convergence: burn 300, wipe both monster rows, GY this ── */

static const struct EffectScriptStep sGrandConvergenceSteps[] __attribute__((section(".text"))) = {
  { EFFECT_SCRIPT_SHOW_TEXT, 0, 0, 0, 0 },
  { EFFECT_SCRIPT_CHANGE_LP, INACTIVE_DUELIST, 0, FALSE, -300 },
  { EFFECT_SCRIPT_DESTROY_ALL_MONSTERS_ROW, ACTIVE_DUELIST_MONSTER_ROW, 0, FALSE, 0 },
  { EFFECT_SCRIPT_DESTROY_ALL_MONSTERS_ROW, INACTIVE_DUELIST_MONSTER_ROW, 0, FALSE, 0 },
  { EFFECT_SCRIPT_DESTROY_ACTIVATING_SPELL, ACTIVE_DUELIST, 0, TRUE, 0 },
  { EFFECT_SCRIPT_END, 0, 0, 0, 0 },
};

static const struct EffectScript sEffectScripts[] __attribute__((section(".text"))) = {
  {
    ONE_DAY_OF_PEACE,
    EFFECT_KIND_SPELL,
    ARRAY_COUNT(sOneDayOfPeaceSteps),
    sOneDayOfPeaceSteps,
    { EFFECT_META_DRAW, 0, 0 },
    NULL,
    NULL,
  },
  {
    POT_OF_GREED,
    EFFECT_KIND_SPELL,
    ARRAY_COUNT(sPotOfGreedSteps),
    sPotOfGreedSteps,
    { EFFECT_META_DRAW, 0, 0 },
    NULL,
    TrySpiritOfThePotOfGreedAfterPotOfGreed,
  },
  {
    GRAND_CONVERGENCE,
    EFFECT_KIND_SPELL,
    ARRAY_COUNT(sGrandConvergenceSteps),
    sGrandConvergenceSteps,
    { EFFECT_META_DESTROY, 0, 0 },
    CanActivateGRAND_CONVERGENCE,
    NULL,
  },
};

const struct EffectScript *EffectScript_Find(u16 cardId, u8 kind)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sEffectScripts); i++) {
    if (sEffectScripts[i].cardId == cardId && sEffectScripts[i].kind == kind)
      return &sEffectScripts[i];
  }

  return NULL;
}

const struct EffectScript *EffectScript_FindAny(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sEffectScripts); i++) {
    if (sEffectScripts[i].cardId == cardId)
      return &sEffectScripts[i];
  }

  return NULL;
}

u8 EffectMeta_HasConvertedScript(u16 cardId)
{
  return EffectScript_FindAny(cardId) != NULL;
}

static u8 EffectMeta_GetCategoryLegacy(u16 cardId)
{
  if (cardId == CARD_NONE)
    return EFFECT_META_NONE;

  SetCardInfo(cardId);

  switch (gCardInfo.spellEffect) {
  case SPELL_EFFECT_RAIGEKI:
  case SPELL_EFFECT_DARK_HOLE:
    return EFFECT_META_DESTROY;
  case SPELL_EFFECT_SPARKS:
  case SPELL_EFFECT_HINOTAMA:
  case SPELL_EFFECT_FINAL_FLAME:
  case SPELL_EFFECT_OOKAZI:
  case SPELL_EFFECT_TREMENDOUS_FIRE:
    return EFFECT_META_BURN;
  case SPELL_EFFECT_POT_OF_GREED:
    return EFFECT_META_DRAW;
  default:
    return EFFECT_META_NONE;
  }
}

u8 EffectMeta_GetCategory(u16 cardId)
{
  const struct EffectScript *script = EffectScript_FindAny(cardId);

  if (script != NULL)
    return script->meta.category;

  /* Legacy fallback for unconverted cards with known spellEffect tags. */
  return EffectMeta_GetCategoryLegacy(cardId);
}

static enum DuelActionResult RunStep(const struct EffectScript *script,
                                     const struct EffectScriptStep *step)
{
  struct DuelCard *spellZone;

  switch (step->op) {
  case EFFECT_SCRIPT_END:
    return DUEL_ACTION_OK;

  case EFFECT_SCRIPT_SHOW_TEXT:
    Duel_ShowEffectText(script->cardId);
    return IsDuelOver() == TRUE ? DUEL_ACTION_DUEL_OVER : DUEL_ACTION_OK;

  case EFFECT_SCRIPT_DRAW:
    return Op_Draw(step->a0, step->a1, step->a2);

  case EFFECT_SCRIPT_CHANGE_LP:
    return Op_ChangeLp(step->a0, step->s0, step->a2);

  case EFFECT_SCRIPT_DESTROY_ALL_MONSTERS_ROW:
    return Op_DestroyAllMonstersInRow(step->a0, NULL, step->a2);

  case EFFECT_SCRIPT_DESTROY_ACTIVATING_SPELL:
    spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
    return Op_DestroyZone(spellZone, step->a0, step->a2);

  case EFFECT_SCRIPT_OPT_REQUIRE:
    if (EffectOpt_IsUsed(script->cardId))
      return DUEL_ACTION_BLOCKED;
    return DUEL_ACTION_OK;

  case EFFECT_SCRIPT_OPT_MARK:
    EffectOpt_MarkUsed(script->cardId);
    return DUEL_ACTION_OK;

  default:
    return DUEL_ACTION_INVALID;
  }
}

u8 EffectScript_Run(const struct EffectScript *script)
{
  u8 i;
  enum DuelActionResult result;

  if (script == NULL || script->steps == NULL)
    return FALSE;

  if (script->canActivate != NULL && !script->canActivate()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return TRUE; /* handled — do not fall through to legacy */
  }

  for (i = 0; i < script->stepCount; i++) {
    if (script->steps[i].op == EFFECT_SCRIPT_END)
      break;

    result = RunStep(script, &script->steps[i]);
    if (result == DUEL_ACTION_DUEL_OVER || result == DUEL_ACTION_BLOCKED)
      break;
    if (IsDuelOver() == TRUE)
      break;
  }

  if (script->afterSteps != NULL && IsDuelOver() != TRUE)
    script->afterSteps();

  return TRUE;
}
