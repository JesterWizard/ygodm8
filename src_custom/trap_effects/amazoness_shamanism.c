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

APPEND_TEXT void EffectAMAZONESS_SHAMANISM(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 destroyed = 0;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelSummonOpts opts;
  u8 i;
  u8 summoned = 0;

  Duel_ShowTrapResponseText(AMAZONESS_SHAMANISM, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || !Duel_IsAmazonessCard(zone->id))
      continue;
    Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE);
    destroyed++;
    if (IsDuelOver() == TRUE)
      return;
  }

  if (destroyed > 0 && !ArchlordKristya_IsSpecialSummonLocked()) {
    opts = Duel_DefaultSpecialSummonOpts(FALSE);
    opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;

    if (GraveyardExpand_IsEnabled()) {
      for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist) && summoned < destroyed; ) {
        u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

        if (!Duel_IsAmazonessCard(cardId) || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER) {
          i++;
          continue;
        }
        SetCardInfo(cardId);
        if (gCardInfo.level == 0 || gCardInfo.level > 4) {
          i++;
          continue;
        }
        if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
          break;
        if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
          break;
        summoned++;
        if (IsDuelOver() == TRUE)
          return;
        /* GY shifted — restart from 0 */
        i = 0;
      }
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
