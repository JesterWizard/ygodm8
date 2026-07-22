#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "morphtronic_clocken.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MORPHTRONIC_CLOCKEN_BURN_PER 1000
#define MORPHTRONIC_CLOCKEN_ATK_PER_COUNTER 500

u8 MorphtronicClocken_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != MORPHTRONIC_CLOCKEN)
    return FALSE;
  if (zone->isDefending)
    return FALSE;

  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(zone->unk4, MORPHTRONIC_CLOCKEN_ATK_PER_COUNTER, gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateMORPHTRONIC_CLOCKEN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_CLOCKEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_CLOCKEN)
    return FALSE;

  /* ATK overlay via MorphtronicClocken_ApplyDynamicZoneStats.
   * DEF: place Morph Counter; ATK: tribute self → burn. */
  if (zone->isDefending) {
    if (!CanUseMonsterEffect(zone))
      return FALSE;
    return TRUE;
  }

  return TRUE;
}

void ActivateMORPHTRONIC_CLOCKENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 counters;

  Duel_ShowEffectTextTyped(MORPHTRONIC_CLOCKEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->isDefending && CanUseMonsterEffect(self)) {
    self->unk4++;
    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  counters = self->unk4;
  if (counters == 0)
    counters = 1;

  ClearZone(self);

  if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)(MORPHTRONIC_CLOCKEN_BURN_PER * counters), TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
