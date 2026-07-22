#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "the_blazing_mars.h"

void UpdateDuelGfxExceptField(void);

static struct DuelCard *BlazingMarsZone(void)
{
  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return NULL;

  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static u8 IsOtherMonsterOnField(struct DuelCard *selfZone, struct DuelCard *zone)
{
  if (zone == NULL || zone == selfZone || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 SendOtherMonstersToGrave(struct DuelCard *selfZone)
{
  u8 col;
  u8 sent = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOtherMonsterOnField(selfZone, zone))
      continue;

    sent++;
    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return sent;
  }

  return sent;
}

u8 CanSpecialSummonTheBlazingMarsFromHandOrGrave(void)
{
  /* no multi-select GY banish + hand/GY activation path yet — banish 3
     other monsters to Special Summon deferred until expanded GY targeting exists. */
  return FALSE;
}

unsigned char CanActivateTheBlazingMars(void)
{
  struct DuelCard *zone = BlazingMarsZone();

  if (zone == NULL || zone->id != THE_BLAZING_MARS)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  /* no Main Phase 1 gate yet — field burn is activatable in any main phase. */
  return TRUE;
}

void ActivateTheBlazingMarsEffect(void)
{
  struct DuelCard *zone = BlazingMarsZone();
  u8 sent;
  s32 damage;

  Duel_ShowCardEffectText(THE_BLAZING_MARS, CARD_EFFECT_TEXT_THE_BLAZING_MARS_POPUP_2);

  if (IsDuelOver() == TRUE)
    return;

  sent = SendOtherMonstersToGrave(zone);
  if (IsDuelOver() == TRUE)
    return;

  damage = (s32)sent * THE_BLAZING_MARS_BURN_PER_MONSTER;
  if (damage > 0 && Duel_ChangeLp(INACTIVE_DUELIST, -damage, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheBlazingMars_SelfCheck(void)
{
  if (THE_BLAZING_MARS_BURN_PER_MONSTER != 500)
    while (1)
      ;
}
#endif
