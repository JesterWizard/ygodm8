#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "wulf_lightsworn_beast.h"

void RefreshFieldMonsterStatOverlays(void);

static u8 sWulfMillReentry APPEND_DATA = 0;

void TryApplyWulfAfterDeckMill(u8 turnDuelist, u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 monsterRow;

  if (sWulfMillReentry || cardId != WULF_LIGHTSWORN_BEAST || IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  monsterRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                             : INACTIVE_DUELIST_MONSTER_ROW;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  sWulfMillReentry = TRUE;
  Duel_ShowEffectTextTyped(WULF_LIGHTSWORN_BEAST, 8);
  if (Duel_SpecialSummonFromGrave(turnDuelist, WULF_LIGHTSWORN_BEAST, opts) == DUEL_ACTION_OK)
    RefreshFieldMonsterStatOverlays();
  sWulfMillReentry = FALSE;
}

unsigned char ShouldActivateWULF_LIGHTSWORN_BEAST(void)
{
  /* Deck-mill SS via TryApplyWulfAfterDeckMill. */
  return FALSE;
}

void ActivateWULF_LIGHTSWORN_BEAST(void)
{
}
