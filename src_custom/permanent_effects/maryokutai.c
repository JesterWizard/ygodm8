#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

extern unsigned char IsSkillDrainActiveOnField(void);

static struct DuelCard *GetSpellOriginZone(void)
{
  u8 row = gTrapEffectData.originRow;
  u8 col = gTrapEffectData.originCol;

  if (col >= MAX_ZONES_IN_ROW || row >= 5)
    return NULL;

  return gTurnZones[row][col];
}

static u8 FindFaceUpMaryokutaiCol(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone->id == MARYOKUTAI && zone->isFaceUp)
      return i;
  }

  return 0xFF;
}

u8 TryMaryokutaiSpellCounter(void)
{
  u8 maryokutaiCol;
  struct DuelCard *spellZone;
  struct DuelCard *maryokutaiZone;

  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_SPELL)
    return FALSE;

  if (IsSkillDrainActiveOnField())
    return FALSE;

  maryokutaiCol = FindFaceUpMaryokutaiCol();
  if (maryokutaiCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  spellZone = GetSpellOriginZone();
  maryokutaiZone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][maryokutaiCol];

  ClearZoneAndSendMonToGraveyard(maryokutaiZone, INACTIVE_DUELIST);

  if (spellZone != NULL)
    ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(8);
    gCardEffectTextData.cardId = MARYOKUTAI;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }

  return TRUE;
}
