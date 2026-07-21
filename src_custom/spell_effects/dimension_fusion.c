#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "removed_from_play.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define DIMENSION_FUSION_LP_COST 2000

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayDimensionFusionCost(void)
{
  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= DIMENSION_FUSION_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= DIMENSION_FUSION_LP_COST;
}

static u8 TurnDuelistHasEmptyMonsterZone(u8 turnDuelist)
{
  return FirstEmptyZoneInRow(gTurnZones[Duel_TurnMonsterRowForDuelist(turnDuelist)]) >= 0;
}

static u8 FindFirstBanishedMonsterIndex(u8 fixedDuelist)
{
  u8 count = RemovedFromPlay_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

    if (Duel_CardIsMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return i;
  }

  return 0xFF;
}

static u8 FixedDuelistHasSummonableBanished(u8 fixedDuelist)
{
  return FindFirstBanishedMonsterIndex(fixedDuelist) != 0xFF;
}

u8 CanActivateDIMENSION_FUSION(void)
{
  u8 activeFixed;
  u8 inactiveFixed;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!CanPayDimensionFusionCost())
    return FALSE;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  activeFixed = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  inactiveFixed = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);

  if (FixedDuelistHasSummonableBanished(activeFixed) && TurnDuelistHasEmptyMonsterZone(ACTIVE_DUELIST))
    return TRUE;

  if (FixedDuelistHasSummonableBanished(inactiveFixed)
      && TurnDuelistHasEmptyMonsterZone(INACTIVE_DUELIST))
    return TRUE;

  return FALSE;
}

static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  RemovedFromPlay_RemoveAt(fixedDuelist, index);
}

static void SpecialSummonBanishedForTurnDuelist(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  while (TurnDuelistHasEmptyMonsterZone(turnDuelist)) {
    u8 index = FindFirstBanishedMonsterIndex(fixedDuelist);
    u16 cardId;
    enum DuelActionResult result;

    if (index == 0xFF)
      break;

    cardId = RemovedFromPlay_GetCardAt(fixedDuelist, index);
    result = Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
    if (result != DUEL_ACTION_OK && result != DUEL_ACTION_DUEL_OVER)
      break;

    RemoveBanishedAt(fixedDuelist, index);

    if (IsDuelOver() == TRUE)
      return;
  }
}

static void DIMENSION_FUSION_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(DIMENSION_FUSION);

  if (IsDuelOver() == TRUE || !CanActivateDIMENSION_FUSION())
    return;

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -DIMENSION_FUSION_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  SpecialSummonBanishedForTurnDuelist(ACTIVE_DUELIST);
  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonBanishedForTurnDuelist(INACTIVE_DUELIST);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDIMENSION_FUSION(void)
{
  if (!CanActivateDIMENSION_FUSION()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(DIMENSION_FUSION, DIMENSION_FUSION_LP_COST,
                                         DIMENSION_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
