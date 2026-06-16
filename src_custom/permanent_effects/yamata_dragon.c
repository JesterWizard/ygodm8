#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u8 BackrowForMonsterTurnRow(u8 turnRow) {
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST_BACKROW;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST_BACKROW;
  return ACTIVE_DUELIST_BACKROW;
}

static void PlacePotOfGreedOnBackrow(u8 backrow) {
  s8 emptyZone;

  if (NumEmptyZonesInRow(gTurnZones[backrow]) <= 0)
    return;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[backrow]);
  if (emptyZone < 0)
    return;

  gTurnZones[backrow][emptyZone]->id = POT_OF_GREED;
  gTurnZones[backrow][emptyZone]->isFaceUp = FALSE;
  gTurnZones[backrow][emptyZone]->isLocked = FALSE;
  gTurnZones[backrow][emptyZone]->isDefending = FALSE;
  gTurnZones[backrow][emptyZone]->unk4 = 0;
  gTurnZones[backrow][emptyZone]->unkTwo = 0;
  gTurnZones[backrow][emptyZone]->willChangeSides = FALSE;
  ResetPermStage(gTurnZones[backrow][emptyZone]);
  ResetTempStage(gTurnZones[backrow][emptyZone]);
}

static void ShowYamataDragonActivationText(void) {
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  gCardEffectTextData.cardId = YAMATA_DRAGON;
  gCardEffectTextData.cardId2 = POT_OF_GREED;
  ActivateCardEffectText();
}

unsigned char ShouldActivateYamataDragon(void) {
  struct DuelCard *zone;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (gActiveEffect.cardId != YAMATA_DRAGON)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return NumEmptyZonesInRow(gTurnZones[BackrowForMonsterTurnRow(gActiveEffect.turnRow)]) > 0;
}

void ActivateYamataDragon(void) {
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  FlipCardFaceUp(zone);
  PlacePotOfGreedOnBackrow(BackrowForMonsterTurnRow(gActiveEffect.turnRow));
  zone->unk4 = 1;
  ShowYamataDragonActivationText();
}
