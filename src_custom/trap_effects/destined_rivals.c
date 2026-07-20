#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 ControlsBlueEyesOrDarkMagician(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL)
      continue;
    if (zone->id == BLUE_EYES_WHITE_DRAGON || zone->id == DARK_MAGICIAN)
      return TRUE;
  }

  return FALSE;
}

APPEND_TEXT void EffectDESTINED_RIVALS(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  Duel_ShowTrapResponseText(DESTINED_RIVALS, gTrapEffectData.originCardId);

  if (EffectOpt_IsUsed(DESTINED_RIVALS) || !ControlsBlueEyesOrDarkMagician()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id != CARD_NONE)
      zone->effectExhausted = TRUE;
  }

  EffectOpt_MarkUsed(DESTINED_RIVALS);
  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: effectExhausted until EP + OPT turn reset need End Phase /
   * turn_effect clear. Ceiling: marks opp face-up monsters exhausted. */
}
