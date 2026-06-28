#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void FlipCardFaceUp(struct DuelCard *zone);

static u8 OpponentMonsterNeedsAttackPosition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->isDefending || !zone->isFaceUp;
}

static u8 OpponentHasMonsterNotInAttackPosition(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (OpponentMonsterNeedsAttackPosition(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]))
      return TRUE;

  return FALSE;
}

static void ForceOpponentMonstersToAttackPosition(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i];
    if (!OpponentMonsterNeedsAttackPosition(zone))
      continue;

    zone->isDefending = FALSE;
    zone->isFaceUp = TRUE;
    FlipCardFaceUp(zone);
  }
}

unsigned char ShouldActivateBlueEyesChaosDragonTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != BLUE_EYES_CHAOS_DRAGON)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (!zone->isFaceUp)
    return FALSE;

  return OpponentHasMonsterNotInAttackPosition();
}

void ActivateBlueEyesChaosDragonTurnEffect(void)
{
  Duel_ShowEffectTextTyped(BLUE_EYES_CHAOS_DRAGON, 9);

  if (IsDuelOver() == TRUE)
    return;

  ForceOpponentMonstersToAttackPosition();
}
