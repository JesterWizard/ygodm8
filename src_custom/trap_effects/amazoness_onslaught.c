#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static void ActivateAMAZONESS_ONSLAUGHTZone(struct DuelCard *zone)
{
  struct DuelSummonOpts opts;
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  if (Duel_ActivateContinuousTrapPreamble(zone, AMAZONESS_ONSLAUGHT)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Battle Phase OPT SS + after-damage banish + leave GY search need
   * battle/leave hooks. Ceiling: SS 1 Amazoness from hand +1 stage (~500 ATK). */

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 handId;

    if (gTurnHands[INACTIVE_DUELIST][col] == NULL)
      continue;
    handId = gTurnHands[INACTIVE_DUELIST][col]->id;
    if (!Duel_IsAmazonessCard(handId) || GetTypeGroup(handId) != TYPE_GROUP_MONSTER)
      continue;
    if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, handId, NULL, opts) == DUEL_ACTION_OK) {
      u8 mCol;

      for (mCol = 0; mCol < MAX_ZONES_IN_ROW; mCol++) {
        struct DuelCard *m = gFixedZones[row][mCol];

        if (m != NULL && m->id == handId) {
          IncrementPermStage(m);
          break;
        }
      }
    }
    break;
  }

  UpdateDuelGfxExceptField();
}

void TryActivateAMAZONESS_ONSLAUGHTOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(AMAZONESS_ONSLAUGHT,
                                         ActivateAMAZONESS_ONSLAUGHTZone);
}

