#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsPlantMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_PLANT);
}

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaName);
}

static void ActivateBLESSED_WINDSZone(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u16 myLp;
  u8 i;
  u16 aromaId = CARD_NONE;
  struct DuelSummonOpts opts;
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  if (Duel_ActivateContinuousTrapPreamble(zone, BLESSED_WINDS) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: 3 OPT modes + once-per-turn flag need ignition menu.
   * Ceiling on activate: prefer pay 1000 → SS Aroma from GY; else send Plant
   * → +500 LP; else shuffle Plant from GY → +500 LP. */

  myLp = gDuelLifePoints[fixedDuelist];
  if (myLp > 1000 && !ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0
      && GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (IsAromaMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
        aromaId = GraveyardExpand_GetCardAt(fixedDuelist, i);
        break;
      }
    }
    if (aromaId != CARD_NONE) {
      Duel_ChangeLp(INACTIVE_DUELIST, -1000, FALSE);
      opts = Duel_DefaultSpecialSummonOpts(TRUE);
      Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, aromaId, opts);
      return;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m != NULL && m->isFaceUp && IsPlantMonster(m->id)) {
      Duel_DestroyZone(m, INACTIVE_DUELIST, FALSE);
      Duel_ChangeLp(INACTIVE_DUELIST, 500, TRUE);
      return;
    }
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (!IsPlantMonster(id))
        continue;
      GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
      Duel_ChangeLp(INACTIVE_DUELIST, 500, TRUE);
      return;
    }
  }

  (void)UpdateDuelGfxExceptField;
}

void TryActivateBLESSED_WINDSOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(BLESSED_WINDS, ActivateBLESSED_WINDSZone);
}

