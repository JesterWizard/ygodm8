#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "destined_rivals.h"
#include "duel_helpers.h"
#include "effect_events.h"

void UpdateDuelGfxExceptField(void);

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

void DestinedRivals_ClearExhaustedOnTurnBoundary(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL)
        zone->effectExhausted = FALSE;
    }
  }
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
}
