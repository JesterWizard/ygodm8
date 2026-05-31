#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

static struct DuelCard *GetSpellOriginZone(void)
{
  u8 row = gTrapEffectData.originRow;
  u8 col = gTrapEffectData.originCol;

  if (col >= MAX_ZONES_IN_ROW)
    return NULL;

  if (row <= PLAYER_HAND)
    return gFixedZones[row][col];

  if (row < 5)
    return gTurnZones[row][col];

  return NULL;
}

APPEND_TEXT void EffectMagicJammer(void)
{
  struct DuelCard *spellZone = GetSpellOriginZone();

  ClearZoneAndSendMonToGraveyard(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST);

  if (spellZone != NULL)
    ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MAGIC_JAMMER;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}
