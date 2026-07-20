#ifndef GUARD_EFFECT_H
#define GUARD_EFFECT_H

#include "global.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "effect_system.h"

/* YGOPRO-shaped effect registration in C (no Lua VM).
 * Each effect: type + code + condition/cost/target/operation.
 * Activate path and event path share this table. See effect-data-system.md.
 */

/* Non-event activate (spell/trap play, menu ignition). */
#define EFFECT_CODE_ACTIVATE 0xFF

enum EffectType {
  EFFECT_TYPE_ACTIVATE = 0, /* creates resolve on play / menu */
  EFFECT_TYPE_TRIGGER,      /* event → optional UI later; for now auto-run */
  EFFECT_TYPE_CONTINUOUS,   /* event → silent apply (ATK boosts, field checks) */
  EFFECT_TYPE_COUNT
};

enum EffectFlag {
  EFFECT_FLAG_NONE = 0,
  EFFECT_FLAG_OPT = 1 << 0, /* EffectOpt gate + mark on successful op */
};

struct EffectCtx {
  u16 cardId;
  u8 kind;
  u8 type;
  u8 code;
  const struct EffectEvent *event; /* NULL on ACTIVATE */
  struct DuelCard *zone;
};

/* Distinct from EffectCondFn / EffectOpFn in effect_conditions.h / effect_ops.h. */
typedef u8 (*EffectCheckFn)(struct EffectCtx *ctx);
typedef enum DuelActionResult (*EffectResolveFn)(struct EffectCtx *ctx);

struct Effect {
  u16 cardId;
  u8 kind;     /* EFFECT_KIND_* */
  u8 type;     /* EFFECT_TYPE_* */
  u8 code;     /* EFFECT_EVENT_* or EFFECT_CODE_ACTIVATE */
  u8 category; /* EFFECT_META_* */
  u8 flags;    /* EFFECT_FLAG_* */
  EffectCheckFn condition;
  EffectCheckFn cost;
  EffectCheckFn target;
  EffectResolveFn operation;
};

/* Shared helpers for script-backed activate effects. */
u8 EffectCond_ScriptGate(struct EffectCtx *ctx);
enum DuelActionResult EffectOp_RunScript(struct EffectCtx *ctx);

/* True if card has any registered Effect (converted). */
u8 Effect_HasCard(u16 cardId);

/* Activate: run ACTIVATE effects for cardId+kind (cond→cost→target→op). */
u8 Effect_TryActivate(u16 cardId, u8 kind);

/* Query: YES/NO/LEGACY for menu / shouldActivate. */
u8 Effect_QueryShouldActivate(u16 cardId, u8 kind);

/* Event: run TRIGGER + CONTINUOUS effects whose code matches ev->type. */
void Effect_DispatchEvent(const struct EffectEvent *ev);

/* Category from first registered Effect for card, else legacy script/meta. */
u8 Effect_GetCategory(u16 cardId);

#endif /* GUARD_EFFECT_H */
