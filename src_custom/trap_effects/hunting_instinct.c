#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

void UpdateDuelGfxExceptField(void);

static u8 IsDinosaurMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DINOSAUR);
}

APPEND_TEXT void EffectHUNTING_INSTINCT(void)
{
  s8 handZone;
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(HUNTING_INSTINCT, gTrapEffectData.originCardId);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], IsDinosaurMonster);
  else {
    u8 i;

    handZone = -1;
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsDinosaurMonster(gTurnHands[INACTIVE_DUELIST][i]->id)) {
        handZone = (s8)i;
        break;
      }
    }
  }

  if (handZone >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromHandZone(INACTIVE_DUELIST, handZone, opts)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
