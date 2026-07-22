#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "silent_magician_lv8.h"

u8 SilentMagicianLv8_PreventsDestroy(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != SILENT_MAGICIAN_LV8 || !zone->isFaceUp)
    return FALSE;

  if (gSpellEffectData.id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(gSpellEffectData.id) == TYPE_GROUP_SPELL;
}

unsigned char CanActivateSILENT_MAGICIAN_LV8(void)
{
  if (gMonEffect.id != SILENT_MAGICIAN_LV8)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateSILENT_MAGICIAN_LV8Effect(void)
{
  Duel_ShowEffectTextTyped(SILENT_MAGICIAN_LV8, 2);
}
