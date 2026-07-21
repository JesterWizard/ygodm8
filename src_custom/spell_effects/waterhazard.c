#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define WATERHAZARD_MAX_LEVEL 4

static u8 IsWaterHazardSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_WATER)
    return FALSE;

  return gCardInfo.level <= WATERHAZARD_MAX_LEVEL;
}

static u8 ControlsNoMonsters(void)
{
  return Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) == 0;
}

static u8 HandHasWaterHazardTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsWaterHazardSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateWaterHazardIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != WATERHAZARD || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (!ControlsNoMonsters())
    return FALSE;

  if (!HandHasWaterHazardTarget(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void ResolveWaterHazardIgnition(struct DuelCard *zone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanActivateWaterHazardIgnition(zone))
    return;

  Duel_ShowEffectText(WATERHAZARD);

  if (IsDuelOver() == TRUE || !ControlsNoMonsters())
    return;

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsWaterHazardSummonTarget, opts)
      == DUEL_ACTION_DUEL_OVER)
    return;

  zone->effectUsedThisTurn = TRUE;
}

static void WATERHAZARD_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateWaterHazardIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveWaterHazardIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);

  if (CanActivateWaterHazardIgnition(zone))
    ResolveWaterHazardIgnition(zone);
  else
    Duel_ShowEffectText(WATERHAZARD);
}

APPEND_TEXT void EffectWATERHAZARD(void)
{
if (Duel_TryResolveSpellThroughTraps(WATERHAZARD, WATERHAZARD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void WATERHAZARD_SelfCheck(void)
{
  if (!IsWaterHazardSummonTarget(PENGUIN_SOLDIER))
    while (1)
      ;
  if (IsWaterHazardSummonTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
