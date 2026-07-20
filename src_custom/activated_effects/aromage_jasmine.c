#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateAROMAGE_JASMINE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_JASMINE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_JASMINE)
    return FALSE;

  /* ponytail: extra Plant Normal Summon while LP higher + draw-on-LP-gain need
   * permanent/LP hooks. Ceiling: OPT draw 1 via usage; upgrade: LP-gain gate +
   * extra Normal Summon overlay when your LP exceed opponent's. */
  return CanUseMonsterEffect(zone);
}

void ActivateAROMAGE_JASMINEEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(AROMAGE_JASMINE, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}
