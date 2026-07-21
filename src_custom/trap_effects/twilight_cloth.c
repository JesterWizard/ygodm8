#include "global.h"
#include "common-chax.h"
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

APPEND_TEXT void EffectTWILIGHT_CLOTH(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *target = NULL;
  u8 banished = 0;
  u8 i;
  u8 col;

  Duel_ShowTrapResponseText(TWILIGHT_CLOTH, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id != CARD_NONE) {
      target = zone;
      break;
    }
  }

  if (target != NULL && GraveyardExpand_IsEnabled()) {
    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
      if (!IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
        continue;
      Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
      banished++;
    }
    if (banished > 0) {
      /* +1 perm stage (~500) per banished (capped); printed +200/EOT not staged. */
      u8 stages = banished;

      if (stages > 4)
        stages = 4;
      SetPermStage(target, PermStage(target) + stages);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
