#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

APPEND_TEXT void EffectTROJAN_GLADIATOR_BEAST(void)
{
  s8 handZone;
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(TROJAN_GLADIATOR_BEAST, gTrapEffectData.originCardId);

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST],
                                               IsGladiatorBeastMonster);
  else {
    u8 i;

    handZone = -1;
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsGladiatorBeastMonster(gTurnHands[INACTIVE_DUELIST][i]->id)) {
        handZone = (s8)i;
        break;
      }
    }
  }

  if (handZone >= 0 && !ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    /* SS to opponent = ACTIVE during trap response. */
    if (Duel_SpecialSummonFromHandZone(INACTIVE_DUELIST, handZone, opts)
        == DUEL_ACTION_DUEL_OVER)
      return;
    /* SS to ACTIVE (opponent during response) then draw. */
  }

  Duel_DrawCards(INACTIVE_DUELIST, 1, TRUE);
  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
