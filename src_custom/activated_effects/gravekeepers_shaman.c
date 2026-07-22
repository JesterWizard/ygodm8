#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "gravekeepers_shaman.h"

#define SHAMAN_DEF_PER_GK 200

u8 GetDuelistForZone(struct DuelCard *zone);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u8 CountGkInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsGravekeeperMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsGravekeeperMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }
  return count;
}

u8 GravekeepersShaman_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 me;
  u16 def;

  if (zone == NULL || zone->id != GRAVEKEEPERS_SHAMAN)
    return FALSE;

  me = GetDuelistForZone(zone);
  if (me > DUEL_OPPONENT)
    return FALSE;

  SetCardInfo(zone->id);
  def = Duel_StatFromCount(CountGkInGy(me), SHAMAN_DEF_PER_GK, gCardInfo.def);
  Duel_WriteCardInfoStats(zone->id, gCardInfo.atk, def);
  return TRUE;
}

unsigned char CanActivateGRAVEKEEPERS_SHAMAN(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_SHAMAN)
    return FALSE;

  /* DEF overlay via GravekeepersShaman_ApplyDynamicZoneStats.
   * GY-effect negate + Necrovalley Field lock need permanent hooks. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_SHAMANEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SHAMAN, 2);
}
