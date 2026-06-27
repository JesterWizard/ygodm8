#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "possessed_dark_soul.h"

void UpdateDuelGfxExceptField(void);

static struct DuelCard *PossessedDarkSoulSelfZone(void)
{
  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static u8 IsPossessedDarkSoulTarget(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(zone->id);
  return gCardInfo.level <= POSSESSED_DARK_SOUL_MAX_LEVEL;
}

static u8 CountPossessedDarkSoulTargets(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsPossessedDarkSoulTarget(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]))
      count++;
  }

  return count;
}

static u8 EmptyZonesAfterSelfTribute(void)
{
  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) + 1;
}

static u8 CanResolvePossessedDarkSoul(void)
{
  if (CountPossessedDarkSoulTargets() == 0)
    return FALSE;

  return EmptyZonesAfterSelfTribute() > 0;
}

static void TakeControlOfMonsterZone(struct DuelCard *src)
{
  s8 destCol;
  struct DuelCard *dst;

  if (src == NULL || src->id == CARD_NONE)
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (destCol < 0)
    return;

  dst = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][destCol];
  CopyCard(dst, src);
  dst->isFaceUp = TRUE;
  dst->isLocked = FALSE;
  dst->isDefending = FALSE;
  dst->unkTwo = 0;
  dst->unk4 = 2;
  dst->willChangeSides = FALSE;
  ClearZone(src);
  Duel_NotifyMonsterZoneChanged(dst);
}

static void TakeAllPossessedDarkSoulTargets(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsPossessedDarkSoulTarget(zone))
      continue;

    if (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) == 0)
      break;

    TakeControlOfMonsterZone(zone);
  }
}

unsigned char CanActivatePossessedDarkSoul(void)
{
  struct DuelCard *zone = PossessedDarkSoulSelfZone();

  if (gMonEffect.id != POSSESSED_DARK_SOUL)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (zone->id != POSSESSED_DARK_SOUL || !CanUseMonsterEffect(zone))
    return FALSE;

  return CanResolvePossessedDarkSoul();
}

void ActivatePossessedDarkSoulEffect(void)
{
  struct DuelCard *selfZone = PossessedDarkSoulSelfZone();

  if (selfZone->id != POSSESSED_DARK_SOUL || !selfZone->isFaceUp)
    return;

  Duel_ShowEffectTextTyped(POSSESSED_DARK_SOUL, 2);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(selfZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  TakeAllPossessedDarkSoulTargets();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
  UpdateDuelGfxExceptField();
}
