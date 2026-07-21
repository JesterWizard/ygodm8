#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sVenomName[] APPEND_RODATA = "Venom";

APPEND_TEXT void EffectAMBUSH_FANGS(void)
{
  struct DuelCard *attacker;

  Duel_ShowTrapResponseText(AMBUSH_FANGS, gTrapEffectData.originCardId);

  attacker = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (attacker != NULL && GetTypeGroup(attacker->id) == TYPE_GROUP_MONSTER) {
    attacker->unk4++; /* Venom Counter stand-in */
    DecrementPermStage(attacker);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
  (void)sVenomName;
}
