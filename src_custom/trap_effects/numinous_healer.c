#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

#define NUMINOUS_HEALER_BASE 1000
#define NUMINOUS_HEALER_PER_GY 500

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountNuminousHealerInGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == NUMINOUS_HEALER)
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == NUMINOUS_HEALER)
      count++;
  }

  return count;
}

APPEND_TEXT void EffectNUMINOUS_HEALER(void)
{
  u16 heal;
  u8 gyCount;

  Duel_ShowTrapResponseText(NUMINOUS_HEALER, gTrapEffectData.originCardId);

  /* ponytail: activate when you take damage. Ceiling: when Effect runs, heal
   * 1000 + 500×GY copies; upgrade: LP-damage trigger wire. */

  gyCount = CountNuminousHealerInGy();
  heal = NUMINOUS_HEALER_BASE + (u16)gyCount * NUMINOUS_HEALER_PER_GY;
  Duel_ChangeLp(INACTIVE_DUELIST, (s32)heal, TRUE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
