#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "just_deserts.h"

#define JUST_DESERTS_DAMAGE_PER_MONSTER 500

void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);

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

static void ApplyJustDesertsDamage(u8 monsterCount)
{
  u16 damage;

  if (monsterCount == 0)
    return;

  damage = (u16)monsterCount * JUST_DESERTS_DAMAGE_PER_MONSTER;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(damage);
  else
    SetOpponentLifePointsToSubtract(damage);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void ActivateJustDesertsZone(struct DuelCard *zone)
{
  u8 monsterCount = CountActiveDuelistMonsters();

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = JUST_DESERTS;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  ApplyJustDesertsDamage(monsterCount);
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
