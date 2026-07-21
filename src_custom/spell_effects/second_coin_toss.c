#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "second_coin_toss.h"
#include "spell_effects.h"

extern u16 gNewButtons;
void WaitForVBlank(void);

static u8 sSecondCoinTossUsedPlayer APPEND_DATA = {FALSE};
static u8 sSecondCoinTossUsedOpponent APPEND_DATA = {FALSE};

u8 SecondCoinToss_CanRedo(u8 fixedDuelist)
{
  struct DuelCard *zone;

  zone = Duel_FindBackrowCard(fixedDuelist, SECOND_COIN_TOSS, TRUE);
  if (zone == NULL)
    return FALSE;

  if (fixedDuelist == DUEL_PLAYER)
    return !sSecondCoinTossUsedPlayer;
  if (fixedDuelist == DUEL_OPPONENT)
    return !sSecondCoinTossUsedOpponent;
  return FALSE;
}

void SecondCoinToss_MarkUsed(u8 fixedDuelist)
{
  if (fixedDuelist == DUEL_PLAYER)
    sSecondCoinTossUsedPlayer = TRUE;
  else if (fixedDuelist == DUEL_OPPONENT)
    sSecondCoinTossUsedOpponent = TRUE;
}

void SecondCoinToss_ClearOnTurnBoundary(void)
{
  sSecondCoinTossUsedPlayer = FALSE;
  sSecondCoinTossUsedOpponent = FALSE;
}

static u8 PlayerWantsCoinRedo(void)
{
  /* A = keep first flip, B = redo. Unlabeled; same pattern as other A/B choices. */
  while (1) {
    WaitForVBlank();
    if (gNewButtons & A_BUTTON)
      return FALSE;
    if (gNewButtons & B_BUTTON)
      return TRUE;
  }
}

u8 SecondCoinToss_Flip(u8 controllerFixed)
{
  u8 heads = RandRangeU8(0, 1) == 1;

  if (!SecondCoinToss_CanRedo(controllerFixed))
    return heads;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    if (!PlayerWantsCoinRedo())
      return heads;
  } else if (heads) {
    /* AI: keep heads, redo tails. */
    return heads;
  }

  SecondCoinToss_MarkUsed(controllerFixed);
  return RandRangeU8(0, 1) == 1;
}

APPEND_TEXT void EffectSECOND_COIN_TOSS(void)
{
  const struct EffectScript *script = EffectScript_Find(SECOND_COIN_TOSS, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
  /* Parent: coin callers use SecondCoinToss_Flip(controllerFixed). */
}
