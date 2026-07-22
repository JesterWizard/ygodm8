#ifndef GUARD_EFFECT_EVENTS_H
#define GUARD_EFFECT_EVENTS_H

#include "global.h"

/* Effect event bus + generic OPT (Phase 3+).
 * See documentation/effect-data-system.md.
 */

enum EffectEventId {
  EFFECT_EVENT_ON_SUMMON = 0,
  EFFECT_EVENT_ON_DESTROY,
  EFFECT_EVENT_ON_BATTLE_DESTROY,
  EFFECT_EVENT_ON_DAMAGE_CALC,
  EFFECT_EVENT_ON_TURN_STANDBY,
  EFFECT_EVENT_ON_LEAVE_FIELD,
  /* Monster row composition changed (NotifyFixedMonsterRowChanged). */
  EFFECT_EVENT_ON_FIELD_CHANGE,
  /* Life Points changed: controller = who gained/lost; param = |delta| (clamped u16). */
  EFFECT_EVENT_ON_LP_GAIN,
  EFFECT_EVENT_ON_LP_LOSS,
  /* Spell/trap/monster effect about to resolve (lightweight chain surface). */
  EFFECT_EVENT_ON_CARD_ACTIVATE,
  EFFECT_EVENT_COUNT
};

/* EFFECT_EVENT_ON_CARD_ACTIVATE flags */
#define EFFECT_EVENT_ACTIVATE_SPELL 0x01
#define EFFECT_EVENT_ACTIVATE_TRAP 0x02
#define EFFECT_EVENT_ACTIVATE_MONSTER 0x04

#define EFFECT_EVENT_MAX_SUBSCRIBERS 32
#define EFFECT_OPT_MAX_CARDS 48

struct EffectEvent {
  u8 type;
  u16 cardId;
  u8 fixedRow;
  u8 col;
  u8 controller;
  u8 flags;
  u16 param; /* LP |delta|, or misc */
  struct DuelCard *zone;
};

typedef void (*EffectEventHandler)(const struct EffectEvent *ev);

void EffectEvent_Subscribe(u8 eventId, EffectEventHandler handler);
void EffectEvent_Emit(const struct EffectEvent *ev);
void EffectEvent_EmitSimple(u8 eventId, u16 cardId, struct DuelCard *zone);
void EffectEvent_EmitLpChange(u8 controller, s32 delta);
void EffectEvent_EmitCardActivate(u16 cardId, struct DuelCard *zone, u8 activateFlags);

/* Lazy-init: subscribe field-continuous checks to ON_FIELD_CHANGE. */
void EffectEvent_EnsureInit(void);

/* Turn-boundary: clear OPT bits and emit ON_TURN_STANDBY. */
void EffectEvent_OnTurnBoundary(void);

u8 EffectOpt_IsUsed(u16 cardId);
void EffectOpt_MarkUsed(u16 cardId);
void EffectOpt_ClearAll(void);

/* ON_CARD_ACTIVATE negate request (one-shot for current activation). */
void EffectEvent_RequestActivationNegate(void);
u8 EffectEvent_ConsumeActivationNegate(void);

#endif /* GUARD_EFFECT_EVENTS_H */
