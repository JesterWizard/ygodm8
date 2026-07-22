#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "evil_dragon_ananta.h"

#define EVIL_DRAGON_ANANTA_STAT_PER_REPTILE 600

static u8 CountReptileInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);

  for (i = 0; i < gyCount; i++) {
    if (Duel_CardHasMonsterType(GraveyardExpand_GetCardAt(fixedDuelist, i), TYPE_REPTILE))
      count++;
  }

  return count;
}

static u16 AnantaCurrentStat(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);

  if (fixedDuelist == 0xFF)
    return 0;

  return Duel_StatFromCount(
      CountReptileInGraveyard(fixedDuelist),
      EVIL_DRAGON_ANANTA_STAT_PER_REPTILE,
      0);
}

static struct DuelCard *FindFirstDestroyableFieldCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE)
        return zone;
    }
  }

  return NULL;
}

u8 EvilDragonAnanta_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != EVIL_DRAGON_ANANTA)
    return FALSE;

  stat = AnantaCurrentStat(zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

void TryApplyEvilDragonAnantaEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;
  struct DuelCard *target;
  u8 turnDuelist = ACTIVE_DUELIST;
  u8 gyDuelist;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id != EVIL_DRAGON_ANANTA || !zone->isFaceUp)
      continue;

    target = FindFirstDestroyableFieldCard();
    if (target == NULL)
      return;

    Duel_ShowEffectTextTyped(EVIL_DRAGON_ANANTA, 9);
    if (IsDuelOver() == TRUE)
      return;

    gyDuelist = GetDuelistForZone(target);
    if (gyDuelist == 0xFF)
      gyDuelist = turnDuelist;

    if (Duel_DestroyZone(target, gyDuelist, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    return;
  }
}

unsigned char ShouldActivateEVIL_DRAGON_ANANTA(void)
{
  /* EP destroy 1 via TryApplyEvilDragonAnantaEndPhase; ATK via ApplyDynamicZoneStats. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_DRAGON_ANANTA(void)
{
}

#if !defined(__GNUC__)
#error Evil Dragon Ananta stat hook self-check requires GCC
#elif __GNUC__
void EvilDragonAnanta_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = EVIL_DRAGON_ANANTA;
  EvilDragonAnanta_ApplyDynamicZoneStats(&zone);
}
#endif
