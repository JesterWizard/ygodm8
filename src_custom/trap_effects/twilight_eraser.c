#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ControlsTwoSameTypeDifferentNameLS(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u16 ids[MAX_ZONES_IN_ROW];
  u8 types[MAX_ZONES_IN_ROW];
  u8 count = 0;
  u8 i;
  u8 j;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !IsLightswornMonster(zone->id))
      continue;
    SetCardInfo(zone->id);
    ids[count] = zone->id;
    types[count] = gCardInfo.type;
    count++;
  }

  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if (types[i] == types[j] && ids[i] != ids[j])
        return TRUE;
    }
  }

  return FALSE;
}

static u8 BanishTwoLightswornFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 banished = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < 2; i--) {
    if (!IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
      continue;
    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    banished++;
  }

  return banished >= 2;
}

APPEND_TEXT void EffectTWILIGHT_ERASER(void)
{
  u8 banishedField = 0;
  u8 r;
  u8 c;

  Duel_ShowTrapResponseText(TWILIGHT_ERASER, gTrapEffectData.originCardId);

  if (!ControlsTwoSameTypeDifferentNameLS() || !BanishTwoLightswornFromGy()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  for (r = 0; r < 4 && banishedField < 2; r++) {
    for (c = 0; c < MAX_ZONES_IN_ROW && banishedField < 2; c++) {
      struct DuelCard *zone = gFixedZones[r][c];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;
      Duel_BanishZone(zone, FALSE);
      banishedField++;
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: PickZone for 2 field targets + mill→SS Lightsworn from hand. */
}
