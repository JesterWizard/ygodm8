#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 IsZombieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_ZOMBIE);
}

static u8 ControlsNoMonsters(void)
{
  return Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) == 0;
}

static u8 HandHasZombieMonster(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsZombieMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateCallOfTheMummyIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != CALL_OF_THE_MUMMY || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (!ControlsNoMonsters())
    return FALSE;

  if (!HandHasZombieMonster(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void ResolveCallOfTheMummyIgnition(struct DuelCard *zone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanActivateCallOfTheMummyIgnition(zone))
    return;

  Duel_ShowEffectText(CALL_OF_THE_MUMMY);

  if (IsDuelOver() == TRUE || !ControlsNoMonsters())
    return;

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsZombieMonster, opts)
      == DUEL_ACTION_DUEL_OVER)
    return;

  zone->effectUsedThisTurn = TRUE;
}

static void CALL_OF_THE_MUMMY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateCallOfTheMummyIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveCallOfTheMummyIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);

  if (CanActivateCallOfTheMummyIgnition(zone))
    ResolveCallOfTheMummyIgnition(zone);
  else
    Duel_ShowEffectText(CALL_OF_THE_MUMMY);
}

APPEND_TEXT void EffectCALL_OF_THE_MUMMY(void)
{
if (Duel_TryResolveSpellThroughTraps(CALL_OF_THE_MUMMY, CALL_OF_THE_MUMMY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
