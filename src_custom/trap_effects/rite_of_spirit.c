#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeepersMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

APPEND_TEXT void EffectRITE_OF_SPIRIT(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelSummonOpts opts;
  u8 i;
  u16 cardId = CARD_NONE;

  Duel_ShowTrapResponseText(RITE_OF_SPIRIT, gTrapEffectData.originCardId);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (IsGravekeepersMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
        cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
        break;
      }
    }
  } else if (IsGravekeepersMonster(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard)) {
    cardId = gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard;
  }

  if (cardId != CARD_NONE) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, cardId, opts);
  }

  /* ponytail: unaffected by Necrovalley — already no Necrovalley gate here.
   * PickZone for GY target + trapEffect wire. */

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
