#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define POISON_OF_THE_OLD_MAN_HEAL 1200
#define POISON_OF_THE_OLD_MAN_BURN 800

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE for burn 800, FALSE for gain 1200. */
static u8 PlayerChoosesBurn(void)
{
  /* ponytail: no dedicated choice UI — A = burn 800, B = gain 1200 LP.
   * Ceiling: unlabeled buttons; upgrade path: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static void POISON_OF_THE_OLD_MAN_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 chooseBurn;

  Duel_ShowEffectText(POISON_OF_THE_OLD_MAN);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chooseBurn = PlayerChoosesBurn();
  else
    chooseBurn = TRUE; /* AI prefers burn 800 */

  if (chooseBurn) {
    if (Duel_ChangeLp(INACTIVE_DUELIST, -POISON_OF_THE_OLD_MAN_BURN, FALSE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    if (Duel_ChangeLp(ACTIVE_DUELIST, POISON_OF_THE_OLD_MAN_HEAL, FALSE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectPOISON_OF_THE_OLD_MAN(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(POISON_OF_THE_OLD_MAN, POISON_OF_THE_OLD_MAN_BURN,
                                         POISON_OF_THE_OLD_MAN_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
