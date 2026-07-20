#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

#define ATTACK_AND_RECEIVE_BASE 700
#define ATTACK_AND_RECEIVE_PER_GY 300

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountAttackAndReceiveInGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == ATTACK_AND_RECEIVE)
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == ATTACK_AND_RECEIVE)
      count++;
  }

  return count;
}

APPEND_TEXT void EffectATTACK_AND_RECEIVE(void)
{
  u16 damage;
  u8 gyCount;

  Duel_ShowTrapResponseText(ATTACK_AND_RECEIVE, gTrapEffectData.originCardId);

  /* ponytail: activate when you take damage. Ceiling: burn 700 + 300×GY copies. */

  gyCount = CountAttackAndReceiveInGy();
  damage = ATTACK_AND_RECEIVE_BASE + (u16)gyCount * ATTACK_AND_RECEIVE_PER_GY;
  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)damage, TRUE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
