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

static u8 CountLightsworn(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsLightswornMonster(zone->id))
      count++;
  }

  return count;
}

APPEND_TEXT void EffectLIGHTSWORN_AEGIS(void)
{
  u8 maxTargets = CountLightsworn();
  u8 negated = 0;
  u8 r;
  u8 c;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 oppBack = WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

  Duel_ShowTrapResponseText(LIGHTSWORN_AEGIS, gTrapEffectData.originCardId);

  for (r = 0; r < 4 && negated < maxTargets; r++) {
    if (r != oppRow && r != oppBack)
      continue;
    for (c = 0; c < MAX_ZONES_IN_ROW && negated < maxTargets; c++) {
      struct DuelCard *zone = gFixedZones[r][c];

      if (zone == NULL || !zone->isFaceUp || zone->id == CARD_NONE)
        continue;
      zone->effectExhausted = TRUE;
      negated++;
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
