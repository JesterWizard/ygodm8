#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

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

  Duel_DestroyZone(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST, FALSE);

  if (spellZone != NULL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    Duel_ShowEffectText(MAGIC_JAMMER);
  }
}
