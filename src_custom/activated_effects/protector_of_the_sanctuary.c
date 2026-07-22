#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "drop_off.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "protector_of_the_sanctuary.h"

static u8 InactiveSideHasFaceUpProtector(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == PROTECTOR_OF_THE_SANCTUARY && zone->isFaceUp)
      return TRUE;
  }

  return FALSE;
}

u8 ProtectorOfTheSanctuary_BlocksDraw(u8 turnDuelist)
{
  if (gDrawPhaseNormalDrawActive)
    return FALSE;

  if (turnDuelist != ACTIVE_DUELIST)
    return FALSE;

  return InactiveSideHasFaceUpProtector();
}

unsigned char CanActivatePROTECTOR_OF_THE_SANCTUARY(void)
{
  if (gMonEffect.id != PROTECTOR_OF_THE_SANCTUARY)
    return FALSE;

  /* Opp non-Draw-Phase draw lock via ProtectorOfTheSanctuary_BlocksDraw. */
  return FALSE;
}

void ActivatePROTECTOR_OF_THE_SANCTUARYEffect(void)
{
  Duel_ShowEffectTextTyped(PROTECTOR_OF_THE_SANCTUARY, 2);
}
