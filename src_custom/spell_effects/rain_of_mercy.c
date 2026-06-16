#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define RAIN_OF_MERCY_LP 1000

static u8 PlayerTurnDuelist(void)
{
  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 OpponentTurnDuelist(void)
{
  return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;
}

static void RainOfMercy_ResolveBody(void)
{
  if (Duel_ChangeLp(PlayerTurnDuelist(), RAIN_OF_MERCY_LP, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(OpponentTurnDuelist(), RAIN_OF_MERCY_LP, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
  Duel_ShowEffectText(RAIN_OF_MERCY);
}

APPEND_TEXT void EffectRainOfMercy(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(RAIN_OF_MERCY, RAIN_OF_MERCY_LP, RainOfMercy_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
