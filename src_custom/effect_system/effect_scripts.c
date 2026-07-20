#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_conditions.h"
#include "effect_events.h"
#include "effect_ops.h"
#include "effect_scripts.h"
#include "effect_selectors.h"
#include "effect_system.h"
#include "spirit_of_the_pot_of_greed.h"
#include "card.h"
#include "constants/spell_effects.h"

/* Step arrays + sEffectScripts[] from Phase 4b JSON manifest. */
#include "../generated/effect_scripts_table.inc"

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
  case SPELL_EFFECT_HEAVY_STORM:
  case SPELL_EFFECT_HARPIES_FEATHER_DUSTER:
  case SPELL_EFFECT_WARRIOR_ELIMINATION:
  case SPELL_EFFECT_LAST_DAY_OF_WITCH:
  case SPELL_EFFECT_EXILE_OF_THE_WICKED:
  case SPELL_EFFECT_STAIN_STORM:
  case SPELL_EFFECT_ERADICATING_AEROSOL:
  case SPELL_EFFECT_BREATH_OF_LIGHT:
  case SPELL_EFFECT_ETERNAL_DROUGHT:
  case SPELL_EFFECT_CRUSH_CARD:
  case SPELL_EFFECT_WIDESPREAD_RUIN:
  case SPELL_EFFECT_TORRENTIAL_TRIBUTE:
    return EFFECT_META_DESTROY;
  case SPELL_EFFECT_SPARKS:
  case SPELL_EFFECT_HINOTAMA:
  case SPELL_EFFECT_FINAL_FLAME:
  case SPELL_EFFECT_OOKAZI:
  case SPELL_EFFECT_TREMENDOUS_FIRE:
  case SPELL_EFFECT_RESTRUCTER_REVOLUTION:
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

static u16 sBurnThroughTrapsSpellId APPEND_DATA = {0};
static u16 sBurnThroughTrapsDamage APPEND_DATA = {0};
static u8 sBurnThroughTrapsDestroyGfx APPEND_DATA = {0};

static void BurnThroughTrapsBody(void)
{
  Duel_ResolveBurnSpell(sBurnThroughTrapsSpellId, sBurnThroughTrapsDamage,
                        sBurnThroughTrapsDestroyGfx);
}

static enum DuelActionResult RunStep(const struct EffectScript *script,
                                     const struct EffectScriptStep *step)
{
  struct DuelCard *spellZone;
  struct DuelCard *target;
  u8 fixedRow;
  u8 col;

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

  case EFFECT_SCRIPT_REQUIRE_COND:
    if (!EffectSel_ExistsByCond(step->a0))
      return DUEL_ACTION_BLOCKED;
    return DUEL_ACTION_OK;

  case EFFECT_SCRIPT_DESTROY_FIRST_BY_COND:
    if (!EffectSel_FirstByCond(step->a0, &fixedRow, &col))
      return DUEL_ACTION_NO_TARGET;
    target = gFixedZones[fixedRow][col];
    return Op_DestroyZone(target, GetDuelistForZone(target), step->a2);

  case EFFECT_SCRIPT_BURN_THROUGH_TRAPS:
    if (step->s0 <= 0)
      return DUEL_ACTION_INVALID;
    sBurnThroughTrapsSpellId = script->cardId;
    sBurnThroughTrapsDamage = (u16)step->s0;
    sBurnThroughTrapsDestroyGfx = TRUE;
    if (Duel_TryResolveSpellThroughTrapsEx(script->cardId, (u16)step->s0, BurnThroughTrapsBody)
        == DUEL_ACTION_BLOCKED)
      return DUEL_ACTION_BLOCKED;
    return IsDuelOver() == TRUE ? DUEL_ACTION_DUEL_OVER : DUEL_ACTION_OK;

  default:
    return DUEL_ACTION_INVALID;
  }
}

u8 EffectScript_Run(const struct EffectScript *script)
{
  u8 i;
  enum DuelActionResult result;
  u8 blocked = FALSE;

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
    if (result == DUEL_ACTION_BLOCKED) {
      blocked = TRUE;
      break;
    }
    if (result == DUEL_ACTION_DUEL_OVER || IsDuelOver() == TRUE)
      break;
  }

  if (!blocked && script->afterSteps != NULL && IsDuelOver() != TRUE)
    script->afterSteps();

  return TRUE;
}
