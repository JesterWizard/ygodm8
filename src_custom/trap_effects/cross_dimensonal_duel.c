#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

APPEND_TEXT void EffectCROSS_DIMENSONAL_DUEL(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;
  struct DuelCard *target = NULL;

  Duel_ShowTrapResponseText(CROSS_DIMENSONAL_DUEL, gTrapEffectData.originCardId);

  /* ponytail: next Standby return at double ATK + GY protect Golem need
   * turn/destroy hooks. Ceiling: banish 1 Ancient Gear you control. */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsAncientGearMonster(zone->id)) {
      target = zone;
      break;
    }
  }

  if (target != NULL)
    Duel_BanishZone(target, FALSE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
