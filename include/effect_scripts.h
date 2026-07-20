#ifndef GUARD_EFFECT_SCRIPTS_H
#define GUARD_EFFECT_SCRIPTS_H

#include "global.h"
#include "effect_system.h"

/* Phase 4: ordered op-sequence scripts (2A C tables).
 * See documentation/effect-data-system.md.
 */

enum EffectScriptStepOp {
  EFFECT_SCRIPT_END = 0,
  EFFECT_SCRIPT_SHOW_TEXT,
  EFFECT_SCRIPT_DRAW,
  EFFECT_SCRIPT_CHANGE_LP,
  EFFECT_SCRIPT_DESTROY_ALL_MONSTERS_ROW,
  EFFECT_SCRIPT_DESTROY_ACTIVATING_SPELL,
  EFFECT_SCRIPT_OPT_REQUIRE,
  EFFECT_SCRIPT_OPT_MARK,
  /* a0 = EffectCondId; fail closed if no match on field. */
  EFFECT_SCRIPT_REQUIRE_COND,
  /* a0 = EffectCondId; destroy first match (AI / no-pick targeting). */
  EFFECT_SCRIPT_DESTROY_FIRST_BY_COND
};

/* Metadata categories for Phase 5 AI (stable tags; sparse for now). */
enum EffectMetaCategory {
  EFFECT_META_NONE = 0,
  EFFECT_META_DRAW,
  EFFECT_META_DESTROY,
  EFFECT_META_BURN,
  EFFECT_META_SEARCH
};

struct EffectScriptStep {
  u8 op;
  u8 a0; /* duelist / turnRow / unused */
  u8 a1; /* count / updateGfx high uses */
  u8 a2; /* updateGfx */
  s16 s0; /* LP delta */
};

struct EffectScriptMeta {
  u8 category;
  u8 timing; /* reserved */
  u8 flags; /* reserved */
};

struct EffectScript {
  u16 cardId;
  u8 kind;
  u8 stepCount;
  const struct EffectScriptStep *steps;
  struct EffectScriptMeta meta;
  u8 (*canActivate)(void);
  void (*afterSteps)(void);
};

const struct EffectScript *EffectScript_Find(u16 cardId, u8 kind);
const struct EffectScript *EffectScript_FindAny(u16 cardId);
u8 EffectScript_Run(const struct EffectScript *script);

/* Phase 5: category for AI/UI. Script table first; else sparse legacy map. */
u8 EffectMeta_GetCategory(u16 cardId);
u8 EffectMeta_HasConvertedScript(u16 cardId);

#endif /* GUARD_EFFECT_SCRIPTS_H */
