#include "global.h"

static unsigned char ZoneHasFaceUpSpellCanceller(struct DuelCard *zone) {
  return zone->id == SPELL_CANCELLER && zone->isFaceUp;
}

unsigned char IsSpellCancellerSpellLockActive(void) {
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (ZoneHasFaceUpSpellCanceller(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]))
      return TRUE;
    if (ZoneHasFaceUpSpellCanceller(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]))
      return TRUE;
  }

  return FALSE;
}

static unsigned char BackrowZoneHasSpellCard(struct DuelCard *zone) {
  if (zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_SPELL;
}

static void ClearSpellCardsInRow(struct DuelCard **row, u8 duelist) {
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (!BackrowZoneHasSpellCard(row[i]))
      continue;

    ClearZoneAndSendMonToGraveyard(row[i], duelist);
  }
}

unsigned char ShouldActivateSpellCanceller(void) {
  unsigned char i;

  if (gActiveEffect.turnRow == INACTIVE_DUELIST_MONSTER_ROW) {
    if (gActiveEffect.col != GetFirstCardMatchZoneId(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW], SPELL_CANCELLER))
      return FALSE;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (BackrowZoneHasSpellCard(gTurnZones[ACTIVE_DUELIST_BACKROW][i]))
        return TRUE;
    }
  } else if (gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    if (gActiveEffect.col != GetFirstCardMatchZoneId(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], SPELL_CANCELLER))
      return FALSE;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (BackrowZoneHasSpellCard(gTurnZones[INACTIVE_DUELIST_BACKROW][i]))
        return TRUE;
    }
  }

  return FALSE;
}

void ActivateSpellCanceller(void) {
  ResetCardEffectTextData();
  SetCardEffectTextType(8);

  if (gActiveEffect.turnRow == INACTIVE_DUELIST_MONSTER_ROW) {
    FlipCardFaceUp(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][gActiveEffect.col]);
    ClearSpellCardsInRow(gTurnZones[ACTIVE_DUELIST_BACKROW], ACTIVE_DUELIST);
  } else if (gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    FlipCardFaceUp(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][gActiveEffect.col]);
    ClearSpellCardsInRow(gTurnZones[INACTIVE_DUELIST_BACKROW], INACTIVE_DUELIST);
  }

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = SPELL_CANCELLER;
    ActivateCardEffectText();
  }
}
