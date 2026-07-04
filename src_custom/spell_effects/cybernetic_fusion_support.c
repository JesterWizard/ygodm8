#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cybernetic_fusion_support.h"
#include "duel_helpers.h"
#include "spell_economics.h"
#include "spell_effects.h"

u8 IsCyberneticFusionSupportActive(void)
{
  return gCyberneticFusionSupportActive != 0;
}

void ActivateCyberneticFusionSupportForTurn(void)
{
  gCyberneticFusionSupportActive = 1;
}

void ClearCyberneticFusionSupport(void)
{
  gCyberneticFusionSupportActive = 0;
}

static u8 PayHalfLpCost(void)
{
  u16 cost;

  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  cost = gDuelLifePoints[WhoseTurn()] / 2;
  if (cost == 0)
    return TRUE;

  return Duel_ChangeLp(ACTIVE_DUELIST, -(s32)cost, FALSE) != DUEL_ACTION_DUEL_OVER;
}

APPEND_TEXT void EffectCyberneticFusionSupport(void)
{
  Duel_ShowEffectText(CYBERNETIC_FUSION_SUPPORT);
  if (IsDuelOver() == TRUE)
    return;

  if (!PayHalfLpCost())
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                   TRUE);
  ActivateCyberneticFusionSupportForTurn();
}
