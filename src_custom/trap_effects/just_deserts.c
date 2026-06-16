#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "just_deserts.h"

#define JUST_DESERTS_DAMAGE_PER_MONSTER 500

static u8 CountActiveDuelistMonsters(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static void ActivateJustDesertsZone(struct DuelCard *zone)
{
  u8 monsterCount = CountActiveDuelistMonsters();
  u16 damage;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(JUST_DESERTS, 3);

  if (IsDuelOver() == TRUE || monsterCount == 0)
    return;

  damage = (u16)monsterCount * JUST_DESERTS_DAMAGE_PER_MONSTER;
  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)damage, FALSE);
}

void TryActivateJustDesertsOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != JUST_DESERTS || zone->isFaceUp != FALSE)
      continue;

    ActivateJustDesertsZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
