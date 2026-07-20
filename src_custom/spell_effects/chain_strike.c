#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define CHAIN_STRIKE_DAMAGE_PER_LINK 400
#define CHAIN_STRIKE_MIN_LINK 2

static enum DuelActionResult ChainStrike_Burn(s32 damage)
{
  return Duel_ChangeLp(INACTIVE_DUELIST, -damage, FALSE);
}

u8 CanActivateCHAIN_STRIKE(void)
{
  /* ponytail: no Chain Link / chain-depth API in this engine (grep ChainLink empty).
   * Ceiling: always unactivatable; upgrade: require link >= 2, burn 400 * link,
   * and forbid activation when multiple copies of this card are already on the chain. */
  return FALSE;
}

static void CHAIN_STRIKE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(CHAIN_STRIKE);

  if (IsDuelOver() == TRUE)
    return;

  /* Floor burn assumes Chain Link 2 if somehow activated without a depth API. */
  if (ChainStrike_Burn(CHAIN_STRIKE_DAMAGE_PER_LINK * CHAIN_STRIKE_MIN_LINK)
      == DUEL_ACTION_DUEL_OVER)
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
          CHAIN_STRIKE, CHAIN_STRIKE_DAMAGE_PER_LINK * CHAIN_STRIKE_MIN_LINK,
          CHAIN_STRIKE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
