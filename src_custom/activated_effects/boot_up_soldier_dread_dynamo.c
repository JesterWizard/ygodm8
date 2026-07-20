#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static const char sGadgetName[] APPEND_RODATA = "Gadget";

static u8 ControlsGadget(void)
{
  u8 row = gMonEffect.row;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sGadgetName)
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateBOOT_UP_SOLDIER_DREAD_DYNAMO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BOOT_UP_SOLDIER_DREAD_DYNAMO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BOOT_UP_SOLDIER_DREAD_DYNAMO)
    return FALSE;

  /* ponytail: continuous +2000 while Gadget on field needs permanent overlay.
   * Ceiling: OPT apply +4 stages (~2000) if Gadget present. */
  return ControlsGadget() && CanUseMonsterEffect(zone);
}

void ActivateBOOT_UP_SOLDIER_DREAD_DYNAMOEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 i;

  Duel_ShowEffectTextTyped(BOOT_UP_SOLDIER_DREAD_DYNAMO, 2);

  if (zone == NULL || !ControlsGadget() || IsDuelOver() == TRUE)
    return;

  for (i = 0; i < 4; i++)
    IncrementPermStage(zone);

  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
