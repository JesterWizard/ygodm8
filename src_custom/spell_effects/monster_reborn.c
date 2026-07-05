#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_reborn.h"
#include "spell_effects.h"

static u8 InactiveGraveyardHasMonster(void)
{
  u8 count;
  u8 fixedDuelist;
  u16 cardId;

  if (!GraveyardExpand_IsEnabled())
    return GetTypeGroup(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard) == TYPE_GROUP_MONSTER;

  fixedDuelist = (gTurnDuelistBattleState[INACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
      ? DUEL_PLAYER : DUEL_OPPONENT;
  count = GraveyardExpand_GetCount(fixedDuelist);
  if (count == 0)
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, count - 1);
  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

u8 CanActivateMonsterReborn(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return InactiveGraveyardHasMonster();
}

static void MonsterReborn_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u16 revivedId;

  Duel_ShowEffectText(MONSTER_REBORN);

  if (IsDuelOver() == TRUE || !CanActivateMonsterReborn())
    return;

  revivedId = GetGraveCardAndClearGrave(INACTIVE_DUELIST);
  if (revivedId != CARD_NONE && GetTypeGroup(revivedId) == TYPE_GROUP_MONSTER) {
    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, revivedId, opts) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  if (IsDuelOver() == TRUE)
    return;

  if (spellZone != NULL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectMonsterReborn(void)
{
  if (Duel_TryResolveSpellThroughTraps(MONSTER_REBORN, MonsterReborn_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(MONSTER_REBORN_SELF_CHECK)
void MonsterReborn_SelfCheck(void)
{
  if (!CanActivateMonsterReborn() && InactiveGraveyardHasMonster())
    while (1)
      ;
}
#endif
