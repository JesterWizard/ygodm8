#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectAEGIS_OF_THE_OCEAN_DRAGON_LORD(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  Duel_ShowTrapResponseText(AEGIS_OF_THE_OCEAN_DRAGON_LORD, gTrapEffectData.originCardId);

  /* Mark Lv≤3 WATER monsters with unk4 bit for protect-until-EP. */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    SetCardInfo(zone->id);
    if (gCardInfo.level == 0 || gCardInfo.level > 3)
      continue;
    if (gCardInfo.attribute != ATTRIBUTE_WATER)
      continue;
    zone->unk4 |= 1;
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
