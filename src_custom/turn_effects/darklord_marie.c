#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define DARKLORD_MARIE_STANDBY_HEAL 200

static void ShowDarklordMarieEffectText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  gCardEffectTextData.cardId = DARKLORD_MARIE;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;
}

void ActivateDarklordMarieTurnEffect(void)
{
  ShowDarklordMarieEffectText();

  if (Duel_ChangeLp(WhoseTurn(), DARKLORD_MARIE_STANDBY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}
