#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define POT_OF_EXTRAVAGANCE_BANISH_SMALL 3
#define POT_OF_EXTRAVAGANCE_BANISH_LARGE 6
#define POT_OF_EXTRAVAGANCE_DRAW_PER_3 1

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

/* Returns TRUE for banish 6 / draw 2, FALSE for banish 3 / draw 1. */
static u8 PlayerChoosesLargeBanish(void)
{
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    WaitForVBlank();
  }
}

static void POT_OF_EXTRAVAGANCE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 banished;
  u8 drawCount;

  Duel_ShowEffectText(POT_OF_EXTRAVAGANCE);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    banished = PlayerChoosesLargeBanish() ? POT_OF_EXTRAVAGANCE_BANISH_LARGE
                                          : POT_OF_EXTRAVAGANCE_BANISH_SMALL;
  else
    banished = POT_OF_EXTRAVAGANCE_BANISH_SMALL; /* AI prefers cheaper mode */

  drawCount = (u8)((banished / POT_OF_EXTRAVAGANCE_BANISH_SMALL)
                   * POT_OF_EXTRAVAGANCE_DRAW_PER_3);

  if (Duel_DrawCards(ACTIVE_DUELIST, drawCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectPOT_OF_EXTRAVAGANCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(POT_OF_EXTRAVAGANCE, POT_OF_EXTRAVAGANCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
