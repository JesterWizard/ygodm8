#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";
static const char sDestinyHeroNameAlt[] APPEND_RODATA = "Destiny Hero";

static u8 IsBreakDestinyTarget(u16 cardId)
{
  if (cardId == DESTINY_END_DRAGOON)
    return TRUE;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sDestinyHeroName)
      && !Duel_CardNameContains(cardId, sDestinyHeroNameAlt))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 8;
}

APPEND_TEXT void EffectBREAK_THE_DESTINY(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;
  struct DuelCard *target = NULL;

  Duel_ShowTrapResponseText(BREAK_THE_DESTINY, gTrapEffectData.originCardId);

  /* ponytail: skip opp next Main Phase 1 + GY search Destiny-mention S/T need
   * phase/GY hooks. Ceiling: destroy 1 Lv8+ Destiny HERO / Destiny End Dragoon. */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsBreakDestinyTarget(zone->id)) {
      target = zone;
      break;
    }
  }

  if (target != NULL)
    Duel_DestroyZone(target, INACTIVE_DUELIST, FALSE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
