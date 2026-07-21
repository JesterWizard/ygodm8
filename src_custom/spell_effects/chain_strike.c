#include "global.h"
#include "common-chax.h"
#include "chain_strike.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static enum DuelActionResult ChainStrike_Burn(s32 damage)
{
  return Duel_ChangeLp(INACTIVE_DUELIST, -damage, FALSE);
}

u8 ChainStrike_GetEffectiveLinkCount(u8 reportedLink)
{
  if (reportedLink < CHAIN_STRIKE_MIN_LINK)
    return CHAIN_STRIKE_MIN_LINK;

  return reportedLink;
}

s32 ChainStrike_GetBurnDamage(u8 linkCount)
{
  return (s32)CHAIN_STRIKE_DAMAGE_PER_LINK * (s32)ChainStrike_GetEffectiveLinkCount(linkCount);
}

u8 ChainStrike_CanActivateForChain(u8 linkCount, u8 sameNameOnChain)
{
  if (linkCount < CHAIN_STRIKE_MIN_LINK)
    return FALSE;

  if (sameNameOnChain)
    return FALSE;

  return TRUE;
}

u8 CanActivateCHAIN_STRIKE(void)
{
  /* ponytail: no Chain Link / chain-depth API in this engine — parent wires
   * ChainStrike_CanActivateForChain(link, sameNameOnChain) at activation. */
  return FALSE;
}

static void CHAIN_STRIKE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  s32 damage = ChainStrike_GetBurnDamage(CHAIN_STRIKE_MIN_LINK);

  Duel_ShowEffectText(CHAIN_STRIKE);

  if (IsDuelOver() == TRUE)
    return;

  if (ChainStrike_Burn(damage) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectCHAIN_STRIKE(void)
{
  if (!CanActivateCHAIN_STRIKE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(
          CHAIN_STRIKE, (u16)ChainStrike_GetBurnDamage(CHAIN_STRIKE_MIN_LINK),
          CHAIN_STRIKE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CHAIN_STRIKE_SelfCheck(void)
{
  if (ChainStrike_GetBurnDamage(2) != 800)
    while (1)
      ;
  if (ChainStrike_GetBurnDamage(1) != 800)
    while (1)
      ;
  if (ChainStrike_CanActivateForChain(1, FALSE))
    while (1)
      ;
  if (!ChainStrike_CanActivateForChain(2, FALSE))
    while (1)
      ;
}
#endif
