#include "global.h"
#include "common-chax.h"

static u8 GetSinisterSerpentGraveyardDuelist(void)
{
  if (gActiveEffect.turnRow == 6)
    return ACTIVE_DUELIST;
  if (gActiveEffect.turnRow == 7)
    return INACTIVE_DUELIST;
  return 0xFF;
}

static struct DuelCard **GetSinisterSerpentMonsterRow(u8 duelist)
{
  if (duelist == ACTIVE_DUELIST)
    return gTurnZones[ACTIVE_DUELIST_MONSTER_ROW];
  if (duelist == INACTIVE_DUELIST)
    return gTurnZones[INACTIVE_DUELIST_MONSTER_ROW];
  return NULL;
}

u8 ShouldActivateSinisterSerpentEffect(void)
{
  u8 duelist;
  struct DuelCard **monsterRow;

  if (gActiveEffect.cardId != SINISTER_SERPENT)
    return FALSE;

  duelist = GetSinisterSerpentGraveyardDuelist();
  if (duelist == 0xFF)
    return FALSE;

  if (gTurnDuelistBattleState[duelist]->graveyard != SINISTER_SERPENT)
    return FALSE;

  monsterRow = GetSinisterSerpentMonsterRow(duelist);
  return NumEmptyZonesInRow(monsterRow) > 0;
}

void ActivateSinisterSerpentEffect(void)
{
  u8 duelist;
  struct DuelCard **monsterRow;
  u16 cardId;
  struct DuelCard *zone;

  if (!ShouldActivateSinisterSerpentEffect())
    return;

  duelist = GetSinisterSerpentGraveyardDuelist();
  monsterRow = GetSinisterSerpentMonsterRow(duelist);
  cardId = GetGraveCardAndClearGrave(duelist);
  zone = monsterRow[FirstEmptyZoneInRow(monsterRow)];
  zone->id = cardId;
  ResetPermStage(zone);
  ResetTempStage(zone);
  zone->unk4 = 0;
  UnlockCard(zone);
  zone->isDefending = FALSE;
  zone->isLocked = FALSE;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  FlipCardFaceUp(zone);
  zone->willChangeSides = 0;

  if (!gHideEffectText)
  {
    gCardEffectTextData.cardId = SINISTER_SERPENT;
    ActivateCardEffectText();
  }
}
