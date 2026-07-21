#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static u8 ActiveMonsterFixedRow(void)
{
  /* Trap controller is INACTIVE during typical response. */
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

APPEND_TEXT void EffectREVERSAL_OF_FATE(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  struct DuelCard *target = NULL;

  Duel_ShowTrapResponseText(REVERSAL_OF_FATE, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsArcanaForceMonster(zone->id)) {
      target = zone;
      break;
    }
  }

  if (target != NULL) {
    /* Flip Arcana Force coin bit in unk4. */
    target->unk4 ^= 1;
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
