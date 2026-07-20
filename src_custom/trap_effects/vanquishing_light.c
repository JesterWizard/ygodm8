#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

APPEND_TEXT void EffectVANQUISHING_LIGHT(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *tribute = NULL;

  Duel_ShowTrapResponseText(VANQUISHING_LIGHT, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsLightswornMonster(zone->id)) {
      tribute = zone;
      break;
    }
  }

  if (tribute != NULL) {
    Duel_DestroyZone(tribute, INACTIVE_DUELIST, FALSE);
    /* ponytail: negate Summon + destroy summoned needs summon-negation hook.
     * Ceiling: tributes a Lightsworn only; upgrade: cancel pending summon + destroy. */
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
