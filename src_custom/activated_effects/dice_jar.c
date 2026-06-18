#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define DICE_JAR_MAX_DAMAGE 6000

static u16 DamageForWinnerRoll(u8 winnerRoll)
{
  if (winnerRoll == 6)
    return DICE_JAR_MAX_DAMAGE;

  return (u16)winnerRoll * 500;
}

void ActivateDiceJarEffect(void)
{
  u8 activeRoll;
  u8 inactiveRoll;
  u8 winnerRoll;
  u8 loserDuelist;

  Duel_ShowEffectTextTyped(DICE_JAR, 2);

  if (IsDuelOver() == TRUE)
    return;

  do {
    activeRoll = RandRangeU8(1, 6);
    inactiveRoll = RandRangeU8(1, 6);
  } while (activeRoll == inactiveRoll);

  if (activeRoll < inactiveRoll) {
    loserDuelist = ACTIVE_DUELIST;
    winnerRoll = inactiveRoll;
  } else {
    loserDuelist = INACTIVE_DUELIST;
    winnerRoll = activeRoll;
  }

  Duel_ChangeLp(loserDuelist, -(s32)DamageForWinnerRoll(winnerRoll), TRUE);
}
