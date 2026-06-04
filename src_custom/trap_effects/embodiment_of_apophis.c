#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

u8 EmbodimentOfApophisOnMonsterRow(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gTurnZones[row][col]->id == EMBODIMENT_OF_APOPHIS)
        return TRUE;
    }
  }

  return FALSE;
}

void ApplyEmbodimentOfApophisCardInfoOverrides(u16 id)
{
  if (id == EMBODIMENT_OF_APOPHIS && EmbodimentOfApophisOnMonsterRow()) {
    gCardInfo.type = TYPE_SEA_SERPENT;
    gCardInfo.color = COLOR_NORMAL;
  }
}

static void InitSummonedApophisZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = FALSE;
}

APPEND_TEXT void EffectEmbodimentOfApophis(void)
{
  struct DuelCard *trapZone;
  struct DuelCard *monsterZone;
  s8 monsterCol;

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  monsterCol = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);

  if (monsterCol < 0)
    return;

  ClearZone(trapZone);

  monsterZone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][monsterCol];
  monsterZone->id = EMBODIMENT_OF_APOPHIS;
  InitSummonedApophisZone(monsterZone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = EMBODIMENT_OF_APOPHIS;
    ActivateCardEffectText();
  }
}
