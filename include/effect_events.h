#ifndef GUARD_EFFECT_EVENTS_H
#define GUARD_EFFECT_EVENTS_H

#include "global.h"

/* Effect event bus + generic OPT (Phase 3).
 * See documentation/effect-data-system.md.
 */

enum EffectEventId {
  EFFECT_EVENT_ON_SUMMON = 0,
  EFFECT_EVENT_ON_DESTROY,
  EFFECT_EVENT_ON_BATTLE_DESTROY,
  EFFECT_EVENT_ON_DAMAGE_CALC,
  EFFECT_EVENT_ON_TURN_STANDBY,
  EFFECT_EVENT_ON_LEAVE_FIELD,
  EFFECT_EVENT_COUNT
};

#define EFFECT_EVENT_MAX_SUBSCRIBERS 8
#define EFFECT_OPT_MAX_CARDS 48

struct EffectEvent {
  u8 type;
  u16 cardId;
  u8 fixedRow;
  u8 col;
  u8 controller;
  u8 flags;
  struct DuelCard *zone;
};

typedef void (*EffectEventHandler)(const struct EffectEvent *ev);

void EffectEvent_Subscribe(u8 eventId, EffectEventHandler handler);
void EffectEvent_Emit(const struct EffectEvent *ev);
void EffectEvent_EmitSimple(u8 eventId, u16 cardId, struct DuelCard *zone);

/* Turn-boundary: clear OPT bits and emit ON_TURN_STANDBY. */
void EffectEvent_OnTurnBoundary(void);

u8 EffectOpt_IsUsed(u16 cardId);
void EffectOpt_MarkUsed(u16 cardId);
void EffectOpt_ClearAll(void);

#endif /* GUARD_EFFECT_EVENTS_H */
