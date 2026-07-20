#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

static u8 AnyCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

APPEND_TEXT void EffectHYSTERIC_PARTY(void)
{
  s8 handZone;
  struct DuelCard *trapZone;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelSummonOpts opts;
  u8 summoned = 0;

  Duel_ShowTrapResponseText(HYSTERIC_PARTY, gTrapEffectData.originCardId);

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], AnyCard);
  else
    handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);

  if (handZone >= 0)
    ClearZoneAndSendMonToGraveyard(gTurnHands[INACTIVE_DUELIST][handZone], INACTIVE_DUELIST);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (trapZone != NULL)
    Duel_ActivateContinuousZone(trapZone);

  if (!ArchlordKristya_IsSpecialSummonLocked()) {
    opts = Duel_DefaultSpecialSummonOpts(FALSE);
    while (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
      if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, HARPIE_LADY, opts)
          != DUEL_ACTION_OK)
        break;
      summoned++;
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  /* Track count in unk4 for leave-field destroy. */
  if (trapZone != NULL)
    trapZone->unk4 = summoned;

  UpdateDuelGfxExceptField();

  /* ponytail: when this face-up leaves → destroy those SS'd Harpie Lady needs
   * leave-field hook. Ceiling: continuous face-up + GY Harpie Lady SS; OPT
   * trapEffect wire. */
  (void)fixedDuelist;
}
