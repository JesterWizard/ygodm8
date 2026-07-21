#include "global.h"
#include "common-chax.h"
#include "clock_tower_prison.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

static u8 ClockTowerPrison_OwnerWithFaceUp(void)
{
  if (Duel_FindBackrowCard(DUEL_PLAYER, CLOCK_TOWER_PRISON, TRUE) != NULL)
    return DUEL_PLAYER;

  if (Duel_FindBackrowCard(DUEL_OPPONENT, CLOCK_TOWER_PRISON, TRUE) != NULL)
    return DUEL_OPPONENT;

  return 0xFF;
}

u8 ClockTowerPrison_FindFaceUpZone(u8 fixedDuelist, struct DuelCard **outZone)
{
  struct DuelCard *zone;

  if (outZone != NULL)
    *outZone = NULL;

  zone = Duel_FindBackrowCard(fixedDuelist, CLOCK_TOWER_PRISON, TRUE);
  if (zone == NULL)
    return FALSE;

  if (outZone != NULL)
    *outZone = zone;

  return TRUE;
}

u8 ClockTowerPrison_ShouldBlockBattleDamage(u8 damagedFixedDuelist)
{
  struct DuelCard *zone;

  if (!ClockTowerPrison_FindFaceUpZone(damagedFixedDuelist, &zone))
    return FALSE;

  return zone->unk4 >= CLOCK_TOWER_PRISON_MAX_COUNTERS;
}

u8 Cond_ClockTowerPrisonOnOppStandby(struct EffectCtx *ctx)
{
  u8 owner;
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  owner = ClockTowerPrison_OwnerWithFaceUp();
  if (owner == 0xFF)
    return FALSE;

  return ev->controller != owner;
}

enum DuelActionResult Op_ClockTowerPrisonOnOppStandby(struct EffectCtx *ctx)
{
  struct DuelCard *zone;
  u8 owner;

  (void)ctx;

  owner = ClockTowerPrison_OwnerWithFaceUp();
  if (owner == 0xFF)
    return DUEL_ACTION_NO_TARGET;

  if (!ClockTowerPrison_FindFaceUpZone(owner, &zone))
    return DUEL_ACTION_NO_TARGET;

  if (zone->unk4 < CLOCK_TOWER_PRISON_MAX_COUNTERS)
    zone->unk4++;

  return DUEL_ACTION_OK;
}

u8 Cond_ClockTowerPrisonOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  struct DuelCard *zone;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != CLOCK_TOWER_PRISON)
    return FALSE;

  zone = ev->zone;
  if (zone == NULL)
    return FALSE;

  return zone->unk4 >= CLOCK_TOWER_PRISON_MAX_COUNTERS;
}

enum DuelActionResult Op_ClockTowerPrisonOnDestroy(struct EffectCtx *ctx)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 turnDuelist;
  enum DuelActionResult result;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  if (ctx->event->controller != DUEL_PLAYER && ctx->event->controller != DUEL_OPPONENT)
    return DUEL_ACTION_INVALID;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(ctx->event->controller);

  Duel_ShowEffectText(CLOCK_TOWER_PRISON);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  if (FirstEmptyZoneInRow(gTurnZones[turnDuelist == ACTIVE_DUELIST
                                          ? ACTIVE_DUELIST_MONSTER_ROW
                                          : INACTIVE_DUELIST_MONSTER_ROW])
      < 0)
    return DUEL_ACTION_BLOCKED;

  result = Duel_SpecialSummonFromHand(turnDuelist, DESTINY_HERO_DREADMASTER, NULL, opts);
  if (result == DUEL_ACTION_OK)
    return result;

  return Duel_SpecialSummonFromDeck(turnDuelist, DESTINY_HERO_DREADMASTER, opts);
}

APPEND_TEXT void EffectCLOCK_TOWER_PRISON(void)
{
  const struct EffectScript *script =
      EffectScript_Find(CLOCK_TOWER_PRISON, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CLOCK_TOWER_PRISON_SelfCheck(void)
{
  if (CLOCK_TOWER_PRISON_MAX_COUNTERS != 4)
    while (1)
      ;
  if (DESTINY_HERO_DREADMASTER == CARD_NONE)
    while (1)
      ;
}
#endif
