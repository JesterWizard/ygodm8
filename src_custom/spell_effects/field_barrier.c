#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 ControllerAlreadyHasFaceUpFieldBarrier(struct DuelCard *activatingZone)
{
  u8 col;
  u8 row = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == activatingZone || zone == NULL || zone->id != FIELD_BARRIER)
      continue;

    if (zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static void FIELD_BARRIER_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (ControllerAlreadyHasFaceUpFieldBarrier(zone)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(FIELD_BARRIER);

  /* ponytail: Field Spell destroy protection + block new Field Spell activation
   * need destroy-gate and Field Spell activation hooks outside this file (no
   * in-file destroy/activate dispatch). Ceiling: continuous face-up + 1-copy
   * control check only; upgrade: LynJump Duel_DestroyZone / Field Spell activate
   * → if face-up FIELD_BARRIER then skip Field Spell destroy and refuse new
   * Field Spell activations. */
}

APPEND_TEXT void EffectFIELD_BARRIER(void)
{
  if (Duel_TryResolveSpellThroughTraps(FIELD_BARRIER, FIELD_BARRIER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
