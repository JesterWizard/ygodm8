#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

static unsigned char CardMatchesAttribute(u16 cardId, u8 attribute) {
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == attribute;
}

static unsigned char AnyMonsterMatchesEitherAttribute(u8 attribute1, u8 attribute2) {
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnZones[1][i]->id;

    if (CardMatchesAttribute(cardId, attribute1) || CardMatchesAttribute(cardId, attribute2))
      return TRUE;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnZones[2][i]->id;

    if (CardMatchesAttribute(cardId, attribute1) || CardMatchesAttribute(cardId, attribute2))
      return TRUE;
  }

  return FALSE;
}

static void ApplyStageShiftByAttribute(u8 boostedAttribute, u8 weakenedAttribute) {
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[1][i]->id == CARD_NONE)
      continue;
    SetCardInfo(gTurnZones[1][i]->id);
    if (gCardInfo.attribute == boostedAttribute)
      IncrementTempStage(gTurnZones[1][i]);
    else if (gCardInfo.attribute == weakenedAttribute)
      DecrementTempStage(gTurnZones[1][i]);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[2][i]->id == CARD_NONE)
      continue;
    SetCardInfo(gTurnZones[2][i]->id);
    if (gCardInfo.attribute == boostedAttribute)
      IncrementTempStage(gTurnZones[2][i]);
    else if (gCardInfo.attribute == weakenedAttribute)
      DecrementTempStage(gTurnZones[2][i]);
  }
}

unsigned char ShouldActivateMilusRadiant(void) {
  if (gActiveEffect.turnRow != 1 && gActiveEffect.turnRow != 2)
    return FALSE;

  return AnyMonsterMatchesEitherAttribute(ATTRIBUTE_FOREST, ATTRIBUTE_WIND);
}

void ActivateMilusRadiant(void) {
  FlipCardFaceUp(gTurnZones[gActiveEffect.turnRow][gActiveEffect.col]);
  ApplyStageShiftByAttribute(ATTRIBUTE_FOREST, ATTRIBUTE_WIND);
  Duel_ShowEffectTextTyped(gActiveEffect.cardId, 8);
}
