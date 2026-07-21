#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

#define VENOM_BURN_DAMAGE_PER_COUNTER 700

APPEND_TEXT void EffectVENOM_BURN(void)
{
  u8 row;
  u8 col;
  struct DuelCard *target = NULL;
  u8 counters;
  s32 damage;

  Duel_ShowTrapResponseText(VENOM_BURN, gTrapEffectData.originCardId);

  /* Find first monster with Venom Counters in unk4. */
  for (row = 0; row < 4 && target == NULL; row++) {
    if (!Duel_IsFixedMonsterRow(row))
      continue;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && zone->unk4 > 0) {
        target = zone;
        break;
      }
    }
  }

  if (target != NULL) {
    counters = target->unk4;
    target->unk4 = 0;
    damage = (s32)counters * VENOM_BURN_DAMAGE_PER_COUNTER;
    Duel_ChangeLp(ACTIVE_DUELIST, -damage, TRUE);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

}
