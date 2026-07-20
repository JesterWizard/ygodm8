#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_ops.h"

static enum DuelActionResult OpImpl_Draw(const struct EffectOpArgs *args)
{
  if (args == NULL)
    return DUEL_ACTION_INVALID;
  return Duel_DrawCards(args->duelist, args->count, args->updateGfx);
}

static enum DuelActionResult OpImpl_Mill(const struct EffectOpArgs *args)
{
  if (args == NULL)
    return DUEL_ACTION_INVALID;
  return Duel_MillTopDeckCards(args->duelist, args->count, args->updateGfx);
}

static enum DuelActionResult OpImpl_DestroyZone(const struct EffectOpArgs *args)
{
  if (args == NULL || args->zone == NULL)
    return DUEL_ACTION_INVALID;
  return Duel_DestroyZone(args->zone, args->graveyardDuelist, args->updateGfx);
}

static enum DuelActionResult OpImpl_DestroyAllMonstersRow(const struct EffectOpArgs *args)
{
  if (args == NULL)
    return DUEL_ACTION_INVALID;
  return Duel_DestroyAllMonstersMatching(args->turnRow, args->pred, args->updateGfx);
}

static enum DuelActionResult OpImpl_ChangeLp(const struct EffectOpArgs *args)
{
  if (args == NULL)
    return DUEL_ACTION_INVALID;
  return Duel_ChangeLp(args->duelist, args->lpDelta, args->updateGfx);
}

static enum DuelActionResult OpImpl_SearchDeckById(const struct EffectOpArgs *args)
{
  if (args == NULL)
    return DUEL_ACTION_INVALID;
  return Duel_AddDeckCardToHand(args->duelist, args->cardId, args->updateGfx);
}

static const EffectOpFn sEffectOps[EFFECT_OP_COUNT] __attribute__((section(".text"))) = {
  OpImpl_Draw,
  OpImpl_Mill,
  OpImpl_DestroyZone,
  OpImpl_DestroyAllMonstersRow,
  OpImpl_ChangeLp,
  OpImpl_SearchDeckById,
};

enum DuelActionResult EffectOp_Run(u8 opId, const struct EffectOpArgs *args)
{
  if (opId >= EFFECT_OP_COUNT || sEffectOps[opId] == NULL)
    return DUEL_ACTION_INVALID;
  return sEffectOps[opId](args);
}

const EffectOpFn *EffectOp_GetTable(void)
{
  return sEffectOps;
}

enum DuelActionResult Op_Draw(u8 duelist, u8 count, u8 updateGfx)
{
  struct EffectOpArgs args;

  args.duelist = duelist;
  args.count = count;
  args.updateGfx = updateGfx;
  args.turnRow = 0;
  args.graveyardDuelist = 0;
  args.lpDelta = 0;
  args.cardId = CARD_NONE;
  args.zone = NULL;
  args.pred = NULL;
  return EffectOp_Run(EFFECT_OP_DRAW, &args);
}

enum DuelActionResult Op_Mill(u8 duelist, u8 count, u8 updateGfx)
{
  struct EffectOpArgs args;

  args.duelist = duelist;
  args.count = count;
  args.updateGfx = updateGfx;
  args.turnRow = 0;
  args.graveyardDuelist = 0;
  args.lpDelta = 0;
  args.cardId = CARD_NONE;
  args.zone = NULL;
  args.pred = NULL;
  return EffectOp_Run(EFFECT_OP_MILL, &args);
}

enum DuelActionResult Op_DestroyZone(struct DuelCard *zone, u8 graveyardDuelist, u8 updateGfx)
{
  struct EffectOpArgs args;

  args.duelist = 0;
  args.count = 0;
  args.updateGfx = updateGfx;
  args.turnRow = 0;
  args.graveyardDuelist = graveyardDuelist;
  args.lpDelta = 0;
  args.cardId = CARD_NONE;
  args.zone = zone;
  args.pred = NULL;
  return EffectOp_Run(EFFECT_OP_DESTROY_ZONE, &args);
}

enum DuelActionResult Op_DestroyAllMonstersInRow(u8 turnRow, MonsterZonePredicate pred,
                                                 u8 updateGfx)
{
  struct EffectOpArgs args;

  args.duelist = 0;
  args.count = 0;
  args.updateGfx = updateGfx;
  args.turnRow = turnRow;
  args.graveyardDuelist = 0;
  args.lpDelta = 0;
  args.cardId = CARD_NONE;
  args.zone = NULL;
  args.pred = pred;
  return EffectOp_Run(EFFECT_OP_DESTROY_ALL_MONSTERS_ROW, &args);
}

enum DuelActionResult Op_ChangeLp(u8 targetDuelist, s32 delta, u8 updateGfx)
{
  struct EffectOpArgs args;

  args.duelist = targetDuelist;
  args.count = 0;
  args.updateGfx = updateGfx;
  args.turnRow = 0;
  args.graveyardDuelist = 0;
  args.lpDelta = delta;
  args.cardId = CARD_NONE;
  args.zone = NULL;
  args.pred = NULL;
  return EffectOp_Run(EFFECT_OP_CHANGE_LP, &args);
}

enum DuelActionResult Op_SearchDeckById(u8 duelist, u16 cardId, u8 updateGfx)
{
  struct EffectOpArgs args;

  args.duelist = duelist;
  args.count = 0;
  args.updateGfx = updateGfx;
  args.turnRow = 0;
  args.graveyardDuelist = 0;
  args.lpDelta = 0;
  args.cardId = cardId;
  args.zone = NULL;
  args.pred = NULL;
  return EffectOp_Run(EFFECT_OP_SEARCH_DECK_BY_ID, &args);
}
