#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FieldHasGravekeepers(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp
          && Duel_CardNameContains(zone->id, sGravekeepersName)
          && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 FieldHasNecrovalley(void)
{
  return Duel_IsBackrowCardOnField(NECROVALLEY, TRUE);
}

APPEND_TEXT void EffectIMPERIAL_TOMBS_OF_NECROVALLEY(void)
{
  struct DuelCard *origin;

  Duel_ShowTrapResponseText(IMPERIAL_TOMBS_OF_NECROVALLEY, gTrapEffectData.originCardId);

  if (FieldHasGravekeepers() && FieldHasNecrovalley()) {
    origin = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
    if (origin != NULL)
      Duel_DestroyZone(origin, ACTIVE_DUELIST, FALSE);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
