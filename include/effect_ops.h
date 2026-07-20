#ifndef GUARD_EFFECT_OPS_H
#define GUARD_EFFECT_OPS_H

#include "global.h"
#include "duel_helpers.h"

/* Effect operation registry (Phase 1). Parameterized wrappers over duel_helpers.
 * Phase 4 scripts will call EffectOp_Run by opcode; pilots call Op_* directly.
 * See documentation/effect-data-system.md.
 */

enum EffectOpId {
  EFFECT_OP_DRAW = 0,
  EFFECT_OP_MILL,
  EFFECT_OP_DESTROY_ZONE,
  EFFECT_OP_DESTROY_ALL_MONSTERS_ROW,
  EFFECT_OP_CHANGE_LP,
  EFFECT_OP_SEARCH_DECK_BY_ID,
  EFFECT_OP_COUNT
};

struct EffectOpArgs {
  u8 duelist;
  u8 count;
  u8 updateGfx;
  u8 turnRow;
  u8 graveyardDuelist;
  s32 lpDelta;
  u16 cardId;
  struct DuelCard *zone;
  MonsterZonePredicate pred;
};

typedef enum DuelActionResult (*EffectOpFn)(const struct EffectOpArgs *args);

/* Registry entrypoint for Phase 4 scripts. */
enum DuelActionResult EffectOp_Run(u8 opId, const struct EffectOpArgs *args);
const EffectOpFn *EffectOp_GetTable(void);

/* Convenience wrappers (Draw(n) rather than Draw2). */
enum DuelActionResult Op_Draw(u8 duelist, u8 count, u8 updateGfx);
enum DuelActionResult Op_Mill(u8 duelist, u8 count, u8 updateGfx);
enum DuelActionResult Op_DestroyZone(struct DuelCard *zone, u8 graveyardDuelist, u8 updateGfx);
enum DuelActionResult Op_DestroyAllMonstersInRow(u8 turnRow, MonsterZonePredicate pred,
                                                 u8 updateGfx);
enum DuelActionResult Op_ChangeLp(u8 targetDuelist, s32 delta, u8 updateGfx);
enum DuelActionResult Op_SearchDeckById(u8 duelist, u16 cardId, u8 updateGfx);

#endif /* GUARD_EFFECT_OPS_H */
