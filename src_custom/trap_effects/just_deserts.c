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

  if (Duel_ActivateContinuousTrapPreamble(zone, JUST_DESERTS) == DUEL_ACTION_DUEL_OVER)
    return;

  if (monsterCount == 0)
    return;

  damage = (u16)monsterCount * JUST_DESERTS_DAMAGE_PER_MONSTER;
  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)damage, FALSE);
}

void TryActivateJustDesertsOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(JUST_DESERTS, ActivateJustDesertsZone);
}
