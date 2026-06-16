#include "global.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"

static unsigned char CountGrenMajuDaEizaStages(struct DuelCard *zone)
{
  u8 duelist = GetDuelistForZone(zone);

  if (duelist == 0xFF)
    return 0;

  return gDuelDecks[duelist].cardsDrawn / 3;
}

unsigned char ShouldActivateGrenMajuDaEiza(void)
{
  if (gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return gActiveEffect.cardId == GREN_MAJU_DA_EIZA;
}

void ActivateGrenMajuDaEiza(void)
{
  unsigned char stages;
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  FlipCardFaceUp(zone);

  stages = CountGrenMajuDaEizaStages(zone);
  while (stages--)
    IncrementTempStage(zone);

  Duel_ShowEffectTextTyped(GREN_MAJU_DA_EIZA, 8);
}
