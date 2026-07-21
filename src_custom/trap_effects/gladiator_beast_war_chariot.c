#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 ControlsFaceUpGladiatorBeast(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp
        && Duel_CardNameContains(zone->id, sGladiatorBeastName))
      return TRUE;
  }

  return FALSE;
}

APPEND_TEXT void EffectGLADIATOR_BEAST_WAR_CHARIOT(void)
{
  Duel_ShowTrapResponseText(GLADIATOR_BEAST_WAR_CHARIOT, gTrapEffectData.originCardId);

  if (ControlsFaceUpGladiatorBeast()) {
    if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
      struct DuelCard *origin =
          gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];

      if (origin != NULL)
        Duel_DestroyZone(origin, ACTIVE_DUELIST, FALSE);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
