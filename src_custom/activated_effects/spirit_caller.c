#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "spirit_caller.h"

void UpdateDuelGfxExceptField(void);

static u8 OwnerTurnDuelist(void)
{
  if (gMonEffect.row == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (gMonEffect.row == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 IsSpiritCallerGraveyardTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);

  if (gCardInfo.color != COLOR_NORMAL)
    return FALSE;

  if (gCardInfo.level > SPIRIT_CALLER_MAX_LEVEL)
    return FALSE;

  return TRUE;
}

static u8 CanSpecialSummonFromSpiritCallerGraveyard(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return IsSpiritCallerGraveyardTarget(gTurnDuelistBattleState[turnDuelist]->graveyard);
}

unsigned char CanActivateSpiritCaller(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SPIRIT_CALLER)
    return FALSE;

  if (gMonEffect.row != ACTIVE_DUELIST_MONSTER_ROW && gMonEffect.row != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSpecialSummonFromSpiritCallerGraveyard(OwnerTurnDuelist());
}

void ActivateSpiritCallerEffect(void)
{
  u8 turnDuelist = OwnerTurnDuelist();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  Duel_ShowEffectTextTyped(SPIRIT_CALLER, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_SpecialSummonFromGrave(turnDuelist, CARD_NONE, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}
