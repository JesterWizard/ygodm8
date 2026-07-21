#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsNextTarget(u16 cardId)
{
  if (cardId == ELEMENTAL_HERO_NEOS)
    return TRUE;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

APPEND_TEXT void EffectNEXT(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelSummonOpts opts;
  u8 summoned = 0;
  u8 i;
  u16 seen[MAX_ZONES_IN_ROW];
  u8 seenCount = 0;

  Duel_ShowTrapResponseText(NEXT, gTrapEffectData.originCardId);

  if (ArchlordKristya_IsSpecialSummonLocked()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 id;
    u8 j;
    u8 dup = FALSE;

    if (gTurnHands[INACTIVE_DUELIST][i] == NULL)
      continue;
    id = gTurnHands[INACTIVE_DUELIST][i]->id;
    if (!IsNextTarget(id))
      continue;
    for (j = 0; j < seenCount; j++) {
      if (seen[j] == id)
        dup = TRUE;
    }
    if (dup)
      continue;
    if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;
    if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, id, NULL, opts) != DUEL_ACTION_OK)
      continue;
    seen[seenCount++] = id;
    summoned++;
    if (IsDuelOver() == TRUE)
      return;
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist)
         && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0; ) {
      u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);
      u8 j;
      u8 dup = FALSE;

      if (!IsNextTarget(id)) {
        i++;
        continue;
      }
      for (j = 0; j < seenCount; j++) {
        if (seen[j] == id)
          dup = TRUE;
      }
      if (dup) {
        i++;
        continue;
      }
      if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, id, opts) != DUEL_ACTION_OK)
        break;
      seen[seenCount++] = id;
      summoned++;
      if (IsDuelOver() == TRUE)
        return;
      i = 0; /* GY shifted */
    }
  }

  (void)summoned;
  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
