#include "global.h"
#include "common-chax.h"
#include "aromage_jasmine.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 ControllerHasFaceUpJasmineWithLpAdvantage(u8 controller)
{
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row;
  u8 col;

  if (gDuelLifePoints[controller] <= gDuelLifePoints[opp])
    return FALSE;

  row = Duel_FixedMonsterRowForDuelist(controller);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMAGE_JASMINE)
      return TRUE;
  }

  return FALSE;
}

u8 AromageJasmine_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  return ControllerHasFaceUpJasmineWithLpAdvantage(controller);
}

unsigned char CanActivateAROMAGE_JASMINE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_JASMINE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_JASMINE)
    return FALSE;

  /* LP-higher battle protect via AromageJasmine_PreventsBattleDestroy.
   * Draw-on-LP-gain via AromaLpGain (EFFECT_EVENT_ON_LP_GAIN + EffectOpt).
   * Ceiling: extra Plant Normal Summon needs second NS allowance. */
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
