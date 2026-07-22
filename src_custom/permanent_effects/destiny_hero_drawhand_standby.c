#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_drawhand.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

static u8 sDrawhandStandbyPending APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 ControlsDrawhand(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == DESTINY_HERO_DRAWHAND)
      return TRUE;
  }

  return FALSE;
}

static s16 FindDrawhandGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == DESTINY_HERO_DRAWHAND)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DRAWHAND)
      return (s16)i;
  }

  return -1;
}

void DestinyHeroDrawhand_OnSentToGraveyard(u8 fixedDuelist)
{
  if (fixedDuelist == DUEL_PLAYER)
    sDrawhandStandbyPending |= 1;
  else if (fixedDuelist == DUEL_OPPONENT)
    sDrawhandStandbyPending |= 2;
}

void TryApplyDestinyHeroDrawhandStandby(void)
{
  u8 fixed;
  u8 bit;
  u8 turnDuelist;
  s16 gyIndex;
  struct DuelSummonOpts opts;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    bit = fixed == DUEL_PLAYER ? 1 : 2;

    if ((sDrawhandStandbyPending & bit) == 0)
      continue;

    turnDuelist = TurnDuelistForFixed(fixed);
    if (ControlsDrawhand(fixed))
      continue;

    gyIndex = FindDrawhandGyIndex(fixed);
    if (gyIndex < 0)
      continue;

    if (ArchlordKristya_IsSpecialSummonLocked())
      continue;

    if (FirstEmptyZoneInRow(gTurnZones[turnDuelist == ACTIVE_DUELIST
            ? ACTIVE_DUELIST_MONSTER_ROW
            : INACTIVE_DUELIST_MONSTER_ROW]) < 0)
      continue;

    sDrawhandStandbyPending &= (u8)~bit;
    Duel_ShowEffectTextTyped(DESTINY_HERO_DRAWHAND, 9);

    if (!GraveyardExpand_IsEnabled()) {
      if (gDuel.duelistbattleState[fixed].graveyard != DESTINY_HERO_DRAWHAND)
        continue;
      gDuel.duelistbattleState[fixed].graveyard = CARD_NONE;
    } else {
      GraveyardExpand_RemoveAtFixed(fixed, (u8)gyIndex);
      GraveyardExpand_SyncLegacyTop(fixed);
    }

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    Duel_SpecialSummonMonsterId(turnDuelist, DESTINY_HERO_DRAWHAND, opts);
    return;
  }
}
