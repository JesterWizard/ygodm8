#include "global.h"
#include "common-chax.h"
#include "chain_summoning.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void EnableDoubleSummonForTurn(void);
void UnlockCardsInRow(unsigned char turnRow);

static u8 sChainSummoningExtraPending APPEND_DATA = {0};

u8 ChainSummoning_CanActivateForChain(u8 linkCount, u8 sameNameOnChain)
{
  if (linkCount < CHAIN_SUMMONING_MIN_LINK)
    return FALSE;

  if (sameNameOnChain)
    return FALSE;

  return TRUE;
}

void ChainSummoning_GrantExtraNormalSummons(void)
{
  /* Parent: ChainSummoning_TryUnlockAfterNormalSummon in code_8043EF4_hooks. */
  sChainSummoningExtraPending = CHAIN_SUMMONING_EXTRA_NORMAL_SUMMONS;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    UnlockCardsInRow(ACTIVE_DUELIST_HAND);
}

u8 ChainSummoning_ExtraSummonsRemaining(void)
{
  return sChainSummoningExtraPending;
}

u8 ChainSummoning_TryUnlockAfterNormalSummon(void)
{
  if (sChainSummoningExtraPending == 0)
    return FALSE;

  sChainSummoningExtraPending--;

  if (sChainSummoningExtraPending > 0
      && gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    UnlockCardsInRow(ACTIVE_DUELIST_HAND);

  return TRUE;
}

void ChainSummoning_ResetTurnState(void)
{
  sChainSummoningExtraPending = 0;
}

u8 CanActivateCHAIN_SUMMONING(void)
{
  /* ponytail: no Chain Link / chain-depth API — assume min Link 3. Ceiling:
   * always legal at Link≥3 floor; upgrade: real chain counter. */
  return ChainSummoning_CanActivateForChain(CHAIN_SUMMONING_MIN_LINK, FALSE);
}

static void CHAIN_SUMMONING_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(CHAIN_SUMMONING);

  if (IsDuelOver() == TRUE)
    return;

  ChainSummoning_GrantExtraNormalSummons();

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectCHAIN_SUMMONING(void)
{
  if (!CanActivateCHAIN_SUMMONING()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CHAIN_SUMMONING, CHAIN_SUMMONING_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CHAIN_SUMMONING_SelfCheck(void)
{
  if (ChainSummoning_CanActivateForChain(2, FALSE))
    while (1)
      ;
  if (!ChainSummoning_CanActivateForChain(3, FALSE))
    while (1)
      ;
  if (ChainSummoning_CanActivateForChain(3, TRUE))
    while (1)
      ;
  if (CHAIN_SUMMONING_EXTRA_NORMAL_SUMMONS != 2)
    while (1)
      ;
}
#endif
