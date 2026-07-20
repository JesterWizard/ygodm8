#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDinosaur(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_DINOSAUR;
}

static u8 AnyHandCard(u16 cardId)
{
  (void)cardId;
  return TRUE;
}

APPEND_TEXT void EffectFOSSIL_EXCAVATION(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelCard *trapZone;
  struct DuelSummonOpts opts;
  u16 cardId = CARD_NONE;
  u8 i;

  Duel_ShowTrapResponseText(FOSSIL_EXCAVATION, gTrapEffectData.originCardId);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0
      || Duel_DiscardFromHand(INACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK) {
    if (trapZone != NULL)
      Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
    return;
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (IsDinosaur(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
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
      trapZone->unk4 = 1;
      /* effects negated: mark summoned via zone scan — ponytail leave destroy */
    }
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();

  /* ponytail: negate SS effects + mutual destroy-on-leave need leave hooks. */
}
