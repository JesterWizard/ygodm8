#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "minerva_lightsworn_maiden.h"

#define MINERVA_MILL_COUNT 4

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

void TryMinervaLightswornMaidenOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != MINERVA_LIGHTSWORN_MAIDEN)
    return;

  if (SummonModeIsSpecial(mode))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;

  Duel_ShowEffectTextTyped(MINERVA_LIGHTSWORN_MAIDEN, 9);
  Duel_MillTopDeckCards(turnDuelist, MINERVA_MILL_COUNT, TRUE);
}
