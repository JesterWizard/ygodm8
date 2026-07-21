#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static u8 IsDmOrDmg(u16 cardId)
{
  return cardId == DARK_MAGICIAN || cardId == DARK_MAGICIAN_GIRL;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void ActivateMAGICIANS_COMBINATIONZone(struct DuelCard *zone)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;
  u16 tributed = CARD_NONE;
  u16 want;
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;
  u16 ssId = CARD_NONE;

  if (Duel_ActivateContinuousTrapPreamble(zone, MAGICIANS_COMBINATION)
      == DUEL_ACTION_DUEL_OVER)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m != NULL && IsDmOrDmg(m->id)) {
      tributed = m->id;
      Duel_DestroyZone(m, INACTIVE_DUELIST, FALSE);
      break;
    }
  }

  if (tributed == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  want = (tributed == DARK_MAGICIAN) ? DARK_MAGICIAN_GIRL : DARK_MAGICIAN;
  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, want, NULL, opts) == DUEL_ACTION_OK)
    return;

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == want) {
        ssId = want;
        break;
      }
    }
  }

  if (ssId != CARD_NONE)
    Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, ssId, opts);

}

void TryActivateMAGICIANS_COMBINATIONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(MAGICIANS_COMBINATION,
                                         ActivateMAGICIANS_COMBINATIONZone);
}

