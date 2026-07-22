#include "global.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "card_passives.h"

static u8 IsMonsterFieldRow(u8 turnRow)
{
  return turnRow == 1 || turnRow == 2;
}

u8 IsImmuneToSpellEffectsOnField(u16 cardId, u8 turnRow)
{
  if (!IsMonsterFieldRow(turnRow))
    return FALSE;

  if (cardId == THE_AGENT_OF_FORCE_MARS || cardId == LYRILUSC_INDEPENDENT_NIGHTINGALE)
    return TRUE;

  if (cardId == HORUS_THE_BLACK_FLAME_DRAGON_LV6
      || cardId == HORUS_THE_BLACK_FLAME_DRAGON_LV8)
    return TRUE;

  if (cardId == SILENT_MAGICIAN_LV8 || cardId == SILENT_SWORDSMAN_LV5
      || cardId == SILENT_SWORDSMAN_LV7)
    return TRUE;

  if (cardId == TORPEDO_FISH || cardId == CANNONBALL_SPEAR_SHELLFISH)
    return gDuel.field == FIELD_UMI;

  return FALSE;
}
