#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "glorious_illusion.h"
#include "linked_revive_trap.h"

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

APPEND_TEXT void EffectGLORIOUS_ILLUSION(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelCard *trapZone;
  struct DuelSummonOpts opts;
  u16 cardId = CARD_NONE;
  u8 i;
  s8 monsterCol;

  Duel_ShowTrapResponseText(GLORIOUS_ILLUSION, gTrapEffectData.originCardId);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  monsterCol = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);
  if (ArchlordKristya_IsSpecialSummonLocked() || monsterCol < 0) {
    if (trapZone != NULL)
      Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
    return;
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
        cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
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
    }
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();
}

void TryApplyGloriousIllusionEndPhase(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 backrow = fixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
    u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *trap = gFixedZones[backrow][col];

      if (trap == NULL || trap->id != GLORIOUS_ILLUSION || !trap->isFaceUp
          || trap->unk4 == 0)
        continue;

      Duel_ShowEffectText(GLORIOUS_ILLUSION);
      if (Duel_MillTopDeckCards(turnDuelist, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }
}
