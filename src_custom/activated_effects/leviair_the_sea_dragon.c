#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static u8 IsTargetableBanishedMonster(u16 cardId)
{
  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= 4;
}

static u8 FindBestBanishedMonster(u8 *outFixedDuelist, u8 *outIndex)
{
  u8 fixedDuelist;
  u8 bestFixed = 0xFF;
  u8 bestIndex = 0xFF;
  u16 bestLevel = 0;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 count = RemovedFromPlay_GetCount(fixedDuelist);
    u8 i;

    for (i = 0; i < count; i++) {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

      if (!IsTargetableBanishedMonster(cardId))
        continue;

      SetCardInfo(cardId);
      if (bestFixed == 0xFF || gCardInfo.level > bestLevel) {
        bestFixed = fixedDuelist;
        bestIndex = i;
        bestLevel = gCardInfo.level;
      }
    }
  }

  if (bestFixed == 0xFF)
    return FALSE;

  *outFixedDuelist = bestFixed;
  *outIndex = bestIndex;
  return TRUE;
}

/* ponytail: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
 * Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt. */
static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  u8 count;
  u8 i;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  if (index >= count)
    return;

  for (i = index + 1; i < count; i++)
    gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];

  gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
}

static u8 CanSpecialSummonBanishedTarget(void)
{
  u8 fixedDuelist;
  u8 index;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindBestBanishedMonster(&fixedDuelist, &index);
}

unsigned char CanActivateLEVIAIR_THE_SEA_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LEVIAIR_THE_SEA_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LEVIAIR_THE_SEA_DRAGON)
    return FALSE;

  /* ponytail: no Xyz detach cost; OPT SS banished Lv≤4 stand-in when RFP enabled.
   * Ceiling: materials not checked; upgrade: overlay detach before SS. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSpecialSummonBanishedTarget();
}

void ActivateLEVIAIR_THE_SEA_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u8 fixedDuelist;
  u8 index;
  u16 cardId;

  Duel_ShowEffectTextTyped(LEVIAIR_THE_SEA_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!FindBestBanishedMonster(&fixedDuelist, &index))
    return;

  cardId = RemovedFromPlay_GetCardAt(fixedDuelist, index);
  if (!IsTargetableBanishedMonster(cardId))
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  RemoveBanishedAt(fixedDuelist, index);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
