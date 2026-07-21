#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "linked_revive_trap.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

APPEND_TEXT void EffectAMAZONESS_WILLPOWER(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelCard *trapZone;
  struct DuelCard *monster;
  struct DuelSummonOpts opts;
  u16 cardId = CARD_NONE;
  u8 i;
  s8 monsterCol;

  Duel_ShowTrapResponseText(AMAZONESS_WILLPOWER, gTrapEffectData.originCardId);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  monsterCol = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);
  if (ArchlordKristya_IsSpecialSummonLocked() || monsterCol < 0) {
    if (trapZone != NULL)
      Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
    return;
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (Duel_IsAmazonessCard(id) && GetTypeGroup(id) == TYPE_GROUP_MONSTER) {
        cardId = id;
        break;
      }
    }
  }

  if (cardId != CARD_NONE) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, cardId, opts) == DUEL_ACTION_OK
        && trapZone != NULL) {
      Duel_ActivateContinuousZone(trapZone);
      LinkedReviveTrap_Link(trapZone, (u8)monsterCol);
      monster = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][monsterCol];
      if (monster != NULL)
        monster->unk4 |= 1; /* must-attack / cannot-change-position mark */
    }
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();
}
