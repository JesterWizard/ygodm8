#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel.h"
#include "effect.h"
#include "effect_scripts.h"
#include "alluring_mirror_split.h"
#include "amazoness_call.h"
#include "amazoness_village.h"
#include "amazoness_fighting_spirit.h"
#include "all_out_attacks.h"
#include "ancient_gear_castle.h"
#include "ancient_gear_tank.h"
#include "arcane_barrier.h"
#include "aroma_garden.h"
#include "aroma_gardening.h"
#include "backfire.h"
#include "celestial_sword_eatos.h"
#include "clock_tower_prison.h"
#include "colosseum_cage_of_the_gladiator_beasts.h"
#include "dark_city_at_midnight.h"
#include "dark_magical_circle.h"
#include "dark_magician_circle.h"
#include "elemental_hero_inferno.h"
#include "geartown.h"
#include "morphtronic_map.h"
#include "morphtronic_monitron.h"
#include "harpies_hunting_ground.h"
#include "pandemonium.h"
#include "skyscraper.h"
#include "soul_levy.h"
#include "supreme_kings_castle.h"
#include "thumbs_down.h"
#include "linked_revive_trap.h"

/* Generated ACTIVATE Effects mirroring EffectScript table. */
#include "../generated/effect_registry.inc"

/* Hand-authored continuous / trigger Effects (battle, field, …). */
static enum DuelActionResult Op_DamageCalcAtkBoosts(struct EffectCtx *ctx)
{
  (void)ctx;
  ApplyElementalHeroInfernoBattleAtkBoost();
  ApplySkyscraperBattleAtkBoost();
  ApplySupremeKingsCastleBattleAtkBoost();
  ApplyAmazonessFightingSpiritBattleAtkBoost();
  return DUEL_ACTION_OK;
}

static enum DuelActionResult Op_ClearAmazonessCallMultiAttack(struct EffectCtx *ctx)
{
  (void)ctx;
  ClearAmazonessCallMultiAttackState();
  return DUEL_ACTION_OK;
}

static const struct Effect sEffectsExtra[] __attribute__((section(".text"))) = {
  {
      CARD_NONE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_CONTINUOUS,
      EFFECT_EVENT_ON_DAMAGE_CALC,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      NULL,
      NULL,
      NULL,
      Op_DamageCalcAtkBoosts,
  },
  {
      ALLURING_MIRROR_SPLIT,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_BATTLE_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_OPT,
      Cond_AlluringMirrorSplitBattleDestroy,
      NULL,
      NULL,
      Op_AlluringMirrorSplitBattleDestroy,
  },
  {
      ALLURING_MIRROR_SPLIT,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_OPT,
      Cond_AlluringMirrorSplitFloat,
      NULL,
      NULL,
      Op_AlluringMirrorSplitFloat,
  },
  {
      ALL_OUT_ATTACKS,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_AllOutAttacksOnSummon,
      NULL,
      NULL,
      Op_AllOutAttacksOnSummon,
  },
  {
      MORPHTRONIC_MONITRON,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_MorphtronicMonitronOnSummon,
      NULL,
      NULL,
      Op_MorphtronicMonitronOnSummon,
  },
  {
      AMAZONESS_VILLAGE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_BATTLE_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_OPT,
      Cond_AmazonessVillageDestroySs,
      NULL,
      NULL,
      Op_AmazonessVillageDestroySs,
  },
  {
      AMAZONESS_VILLAGE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_OPT,
      Cond_AmazonessVillageDestroySs,
      NULL,
      NULL,
      Op_AmazonessVillageDestroySs,
  },
  {
      ANCIENT_GEAR_CASTLE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_AncientGearCastleOnSummon,
      NULL,
      NULL,
      Op_AncientGearCastleOnSummon,
  },
  {
      GEARTOWN,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_GeartownOnDestroy,
      NULL,
      NULL,
      Op_GeartownOnDestroy,
  },
  {
      MORPHTRONIC_MAP,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_MorphtronicMapOnDestroy,
      NULL,
      NULL,
      Op_MorphtronicMapOnDestroy,
  },
  {
      ANCIENT_GEAR_TANK,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_AncientGearTankOnDestroy,
      NULL,
      NULL,
      Op_AncientGearTankOnDestroy,
  },
  {
      ARCANE_BARRIER,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_ArcaneBarrierOnDestroy,
      NULL,
      NULL,
      Op_ArcaneBarrierOnDestroy,
  },
  {
      AROMA_GARDEN,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_AromaGardenOnDestroy,
      NULL,
      NULL,
      Op_AromaGardenOnDestroy,
  },
  {
      AROMA_GARDEN,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_BATTLE_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_AromaGardenOnDestroy,
      NULL,
      NULL,
      Op_AromaGardenOnDestroy,
  },
  {
      BACKFIRE,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_BackfireOnDestroy,
      NULL,
      NULL,
      Op_BackfireOnDestroy,
  },
  {
      BACKFIRE,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_BATTLE_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_BackfireOnDestroy,
      NULL,
      NULL,
      Op_BackfireOnDestroy,
  },
  {
      SOUL_LEVY,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_SoulLevyOnSummon,
      NULL,
      NULL,
      Op_SoulLevyOnSummon,
  },
  {
      THUMBS_DOWN,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_ThumbsDownOnDestroy,
      NULL,
      NULL,
      Op_ThumbsDownOnDestroy,
  },
  {
      THUMBS_DOWN,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_BATTLE_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_ThumbsDownOnDestroy,
      NULL,
      NULL,
      Op_ThumbsDownOnDestroy,
  },
  {
      CLOCK_TOWER_PRISON,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_TURN_STANDBY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_ClockTowerPrisonOnOppStandby,
      NULL,
      NULL,
      Op_ClockTowerPrisonOnOppStandby,
  },
  {
      CLOCK_TOWER_PRISON,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_ClockTowerPrisonOnDestroy,
      NULL,
      NULL,
      Op_ClockTowerPrisonOnDestroy,
  },
  {
      DARK_CITY_AT_MIDNIGHT,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_DarkCityOnSummon,
      NULL,
      NULL,
      Op_DarkCityOnSummon,
  },
  {
      DARK_MAGICAL_CIRCLE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_DarkMagicalCircleOnDarkMagicianSummon,
      NULL,
      NULL,
      Op_DarkMagicalCircleOnDarkMagicianSummon,
  },
  {
      DARK_MAGICIAN_CIRCLE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_DarkMagicianCircleOnDarkMagicianSummon,
      NULL,
      NULL,
      Op_DarkMagicianCircleOnDarkMagicianSummon,
  },
  {
      DARK_CITY_AT_MIDNIGHT,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_DarkCityOnDestroy,
      NULL,
      NULL,
      Op_DarkCityOnDestroy,
  },
  {
      HARPIES_HUNTING_GROUND,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_HarpiesHuntingGroundOnHarpieSummon,
      NULL,
      NULL,
      Op_HarpiesHuntingGroundOnHarpieSummon,
  },
  {
      PANDEMONIUM,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_DESTROY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_PandemoniumOnArchfiendDestroy,
      NULL,
      NULL,
      Op_PandemoniumOnArchfiendDestroy,
  },
  {
      COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_SUMMON,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_ColosseumCageOnDeckSpecialSummon,
      NULL,
      NULL,
      Op_ColosseumCageOnDeckSpecialSummon,
  },
  {
      CELESTIAL_SWORD_EATOS,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_LEAVE_FIELD,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_CelestialSwordEatosOnLeave,
      NULL,
      NULL,
      Op_CelestialSwordEatosOnLeave,
  },
  {
      CARD_NONE,
      EFFECT_KIND_TRAP,
      EFFECT_TYPE_TRIGGER,
      EFFECT_EVENT_ON_LEAVE_FIELD,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      Cond_LinkedReviveTrapOnLeave,
      NULL,
      NULL,
      Op_LinkedReviveTrapOnLeave,
  },
  {
      CARD_NONE,
      EFFECT_KIND_SPELL,
      EFFECT_TYPE_CONTINUOUS,
      EFFECT_EVENT_ON_TURN_STANDBY,
      EFFECT_META_NONE,
      EFFECT_FLAG_NONE,
      NULL,
      NULL,
      NULL,
      Op_ClearAmazonessCallMultiAttack,
  },
};

u8 EffectCond_ScriptGate(struct EffectCtx *ctx)
{
  const struct EffectScript *script;

  if (ctx == NULL || ctx->cardId == CARD_NONE)
    return FALSE;

  script = EffectScript_Find(ctx->cardId, ctx->kind);
  if (script == NULL)
    return FALSE;

  if (script->canActivate != NULL && !script->canActivate())
    return FALSE;

  return TRUE;
}

enum DuelActionResult EffectOp_RunScript(struct EffectCtx *ctx)
{
  const struct EffectScript *script;

  if (ctx == NULL)
    return DUEL_ACTION_INVALID;

  script = EffectScript_Find(ctx->cardId, ctx->kind);
  if (script == NULL)
    return DUEL_ACTION_INVALID;

  if (!EffectScript_Run(script))
    return DUEL_ACTION_INVALID;

  return IsDuelOver() == TRUE ? DUEL_ACTION_DUEL_OVER : DUEL_ACTION_OK;
}

static u8 EffectPassesCondition(const struct Effect *e, struct EffectCtx *ctx)
{
  if (e->flags & EFFECT_FLAG_OPT) {
    if (EffectOpt_IsUsed(e->cardId))
      return FALSE;
  }

  if (e->condition != NULL && !e->condition(ctx))
    return FALSE;

  return TRUE;
}

static enum DuelActionResult EffectRunPipeline(const struct Effect *e, struct EffectCtx *ctx)
{
  enum DuelActionResult result;

  if (!EffectPassesCondition(e, ctx))
    return DUEL_ACTION_BLOCKED;

  if (e->cost != NULL && !e->cost(ctx))
    return DUEL_ACTION_BLOCKED;

  if (e->target != NULL && !e->target(ctx))
    return DUEL_ACTION_NO_TARGET;

  if (e->operation == NULL)
    return DUEL_ACTION_INVALID;

  result = e->operation(ctx);

  if ((e->flags & EFFECT_FLAG_OPT) && result == DUEL_ACTION_OK)
    EffectOpt_MarkUsed(e->cardId);

  return result;
}

static void InitCtxActivate(struct EffectCtx *ctx, u16 cardId, u8 kind, const struct Effect *e)
{
  ctx->cardId = cardId;
  ctx->kind = kind;
  ctx->type = e->type;
  ctx->code = e->code;
  ctx->event = NULL;
  ctx->zone = NULL;
}

static void InitCtxEvent(struct EffectCtx *ctx, const struct Effect *e, const struct EffectEvent *ev)
{
  ctx->cardId = e->cardId != CARD_NONE ? e->cardId : (ev != NULL ? ev->cardId : CARD_NONE);
  ctx->kind = e->kind;
  ctx->type = e->type;
  ctx->code = e->code;
  ctx->event = ev;
  ctx->zone = ev != NULL ? ev->zone : NULL;
}

/* Hot-path indexes (built once).
 * - cardId sorted: Try/Query/Has/Category → O(log n + matches)
 * - event lists: DispatchEvent → O(subscribers for that event)
 * Kind presence kept so empty PERMANENT/TURN kinds stay O(1). */
#define EFFECT_KIND_COUNT 5
#define EFFECT_REGISTRY_TOTAL \
  (ARRAY_COUNT(sEffectsFromScripts) + ARRAY_COUNT(sEffectsExtra))

struct EffectCardIndexEntry {
  u16 cardId;
  const struct Effect *effect;
};

static u8 sKindPresent[EFFECT_KIND_COUNT] APPEND_DATA = {0};
static struct EffectCardIndexEntry sCardIndex[EFFECT_REGISTRY_TOTAL] APPEND_DATA = {{0}};
static u16 sCardIndexCount APPEND_DATA = {0};
static const struct Effect *sEventFlat[EFFECT_REGISTRY_TOTAL] APPEND_DATA = {0};
static u8 sEventStart[EFFECT_EVENT_COUNT] APPEND_DATA = {0};
static u8 sEventCount[EFFECT_EVENT_COUNT] APPEND_DATA = {0};
static u8 sIndexesReady APPEND_DATA = {0};

static void SortCardIndex(void)
{
  u16 i;

  /* Insertion sort — registry is tiny (~80). */
  for (i = 1; i < sCardIndexCount; i++) {
    struct EffectCardIndexEntry key = sCardIndex[i];
    s16 j = (s16)i - 1;

    while (j >= 0 && sCardIndex[j].cardId > key.cardId) {
      sCardIndex[j + 1] = sCardIndex[j];
      j--;
    }
    sCardIndex[j + 1] = key;
  }
}

static void EnsureIndexes(void)
{
  u16 i;
  u16 n;
  u8 eventTotals[EFFECT_EVENT_COUNT];
  u8 eventWrite[EFFECT_EVENT_COUNT];

  if (sIndexesReady)
    return;

  for (i = 0; i < EFFECT_KIND_COUNT; i++)
    sKindPresent[i] = FALSE;
  for (i = 0; i < EFFECT_EVENT_COUNT; i++) {
    eventTotals[i] = 0;
    sEventCount[i] = 0;
    sEventStart[i] = 0;
  }

  n = 0;
  for (i = 0; i < ARRAY_COUNT(sEffectsFromScripts); i++) {
    const struct Effect *e = &sEffectsFromScripts[i];

    if (e->kind < EFFECT_KIND_COUNT)
      sKindPresent[e->kind] = TRUE;
    if (n < EFFECT_REGISTRY_TOTAL) {
      sCardIndex[n].cardId = e->cardId;
      sCardIndex[n].effect = e;
      n++;
    }
    if ((e->type == EFFECT_TYPE_TRIGGER || e->type == EFFECT_TYPE_CONTINUOUS)
        && e->code < EFFECT_EVENT_COUNT)
      eventTotals[e->code]++;
  }
  for (i = 0; i < ARRAY_COUNT(sEffectsExtra); i++) {
    const struct Effect *e = &sEffectsExtra[i];

    if (e->kind < EFFECT_KIND_COUNT)
      sKindPresent[e->kind] = TRUE;
    if (n < EFFECT_REGISTRY_TOTAL) {
      sCardIndex[n].cardId = e->cardId;
      sCardIndex[n].effect = e;
      n++;
    }
    if ((e->type == EFFECT_TYPE_TRIGGER || e->type == EFFECT_TYPE_CONTINUOUS)
        && e->code < EFFECT_EVENT_COUNT)
      eventTotals[e->code]++;
  }
  sCardIndexCount = n;
  SortCardIndex();

  n = 0;
  for (i = 0; i < EFFECT_EVENT_COUNT; i++) {
    sEventStart[i] = (u8)n;
    sEventCount[i] = eventTotals[i];
    eventWrite[i] = 0;
    n = (u16)(n + eventTotals[i]);
  }

  for (i = 0; i < ARRAY_COUNT(sEffectsFromScripts); i++) {
    const struct Effect *e = &sEffectsFromScripts[i];
    u8 code;

    if (e->type != EFFECT_TYPE_TRIGGER && e->type != EFFECT_TYPE_CONTINUOUS)
      continue;
    if (e->code >= EFFECT_EVENT_COUNT)
      continue;
    code = e->code;
    sEventFlat[sEventStart[code] + eventWrite[code]] = e;
    eventWrite[code]++;
  }
  for (i = 0; i < ARRAY_COUNT(sEffectsExtra); i++) {
    const struct Effect *e = &sEffectsExtra[i];
    u8 code;

    if (e->type != EFFECT_TYPE_TRIGGER && e->type != EFFECT_TYPE_CONTINUOUS)
      continue;
    if (e->code >= EFFECT_EVENT_COUNT)
      continue;
    code = e->code;
    sEventFlat[sEventStart[code] + eventWrite[code]] = e;
    eventWrite[code]++;
  }

  sIndexesReady = TRUE;
}

static u8 KindHasEffects(u8 kind)
{
  EnsureIndexes();
  return kind < EFFECT_KIND_COUNT && sKindPresent[kind];
}

/* First index with cardId >= needle, or sCardIndexCount. */
static u16 CardIndexLowerBound(u16 cardId)
{
  u16 lo = 0;
  u16 hi = sCardIndexCount;

  EnsureIndexes();
  while (lo < hi) {
    u16 mid = (u16)((lo + hi) / 2);

    if (sCardIndex[mid].cardId < cardId)
      lo = (u16)(mid + 1);
    else
      hi = mid;
  }
  return lo;
}

u8 Effect_HasCard(u16 cardId)
{
  u16 i;

  if (cardId == CARD_NONE)
    return FALSE;

  i = CardIndexLowerBound(cardId);
  return i < sCardIndexCount && sCardIndex[i].cardId == cardId;
}

u8 Effect_TryActivate(u16 cardId, u8 kind)
{
  u16 i;
  u8 found = FALSE;
  struct EffectCtx ctx;

  if (cardId == CARD_NONE)
    return EFFECT_DISPATCH_LEGACY;
  if (!KindHasEffects(kind))
    return EFFECT_DISPATCH_LEGACY;

  for (i = CardIndexLowerBound(cardId);
       i < sCardIndexCount && sCardIndex[i].cardId == cardId; i++) {
    const struct Effect *e = sCardIndex[i].effect;
    enum DuelActionResult result;

    if (e->kind != kind)
      continue;
    if (e->type != EFFECT_TYPE_ACTIVATE || e->code != EFFECT_CODE_ACTIVATE)
      continue;

    found = TRUE;
    InitCtxActivate(&ctx, cardId, kind, e);
    result = EffectRunPipeline(e, &ctx);
    if (result == DUEL_ACTION_BLOCKED && !gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
  }

  return found ? EFFECT_DISPATCH_HANDLED : EFFECT_DISPATCH_LEGACY;
}

u8 Effect_QueryShouldActivate(u16 cardId, u8 kind)
{
  u16 i;
  struct EffectCtx ctx;
  u8 found = FALSE;

  if (cardId == CARD_NONE)
    return EFFECT_SHOULD_NO;
  if (!KindHasEffects(kind))
    return EFFECT_SHOULD_LEGACY;

  for (i = CardIndexLowerBound(cardId);
       i < sCardIndexCount && sCardIndex[i].cardId == cardId; i++) {
    const struct Effect *e = sCardIndex[i].effect;

    if (e->kind != kind)
      continue;
    if (e->type != EFFECT_TYPE_ACTIVATE)
      continue;

    found = TRUE;
    InitCtxActivate(&ctx, cardId, kind, e);
    if (!EffectPassesCondition(e, &ctx))
      return EFFECT_SHOULD_NO;
  }

  return found ? EFFECT_SHOULD_YES : EFFECT_SHOULD_LEGACY;
}

void Effect_DispatchEvent(const struct EffectEvent *ev)
{
  u8 i;
  u8 n;
  u8 start;
  struct EffectCtx ctx;

  if (ev == NULL || ev->type >= EFFECT_EVENT_COUNT)
    return;

  EnsureIndexes();
  start = sEventStart[ev->type];
  n = sEventCount[ev->type];
  for (i = 0; i < n; i++) {
    const struct Effect *e = sEventFlat[start + i];

    InitCtxEvent(&ctx, e, ev);
    EffectRunPipeline(e, &ctx);
  }
}

u8 Effect_GetCategory(u16 cardId)
{
  u16 i;

  if (cardId == CARD_NONE)
    return EFFECT_META_NONE;

  i = CardIndexLowerBound(cardId);
  if (i < sCardIndexCount && sCardIndex[i].cardId == cardId)
    return sCardIndex[i].effect->category;

  return EFFECT_META_NONE;
}
