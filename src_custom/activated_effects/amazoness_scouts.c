#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

unsigned char CanActivateAMAZONESS_SCOUTS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_SCOUTS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_SCOUTS)
    return FALSE;

  /* ponytail: either-player quick timing not wired; allow once via usage on
   * your turn only. Ceiling: tribute self only; upgrade: Amazoness protection
   * flags on face-up Amazoness monsters until EOT. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateAMAZONESS_SCOUTSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(AMAZONESS_SCOUTS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: face-up Amazoness cannot be targeted/destroyed by effects this
   * turn — no protection flag hook yet. */

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
