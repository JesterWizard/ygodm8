#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void EnableDoubleSummonForTurn(void);

static void CHAIN_SUMMONING_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(CHAIN_SUMMONING);

  if (IsDuelOver() == TRUE)
    return;

  /* Extra Normal Summons this turn via Double Summon turn flag. */
  EnableDoubleSummonForTurn();

  /* ponytail: Double Summon API only grants 1 extra NS (=2 total), not 3.
   * Ceiling: up to 2 Normal Summons/Sets this turn; upgrade: chain-summoning
   * pending counter of 2 extras in code_803F02C_hooks (like Double Summon
   * unlock loop) so LockMonsterCardsInRow can unlock twice. */
  /* ponytail: no Chain Link / chain-depth API (same as CHAIN_STRIKE). Ceiling:
   * activable without Link≥3 or same-name-on-chain forbid; upgrade: require
   * link >= 3 and reject when multiple same-name cards/effects already on chain. */

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectCHAIN_SUMMONING(void)
{
  /* ponytail: Chain Link 3+ gate missing — see ResolveBody. Always offered. */
  if (Duel_TryResolveSpellThroughTraps(CHAIN_SUMMONING, CHAIN_SUMMONING_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
