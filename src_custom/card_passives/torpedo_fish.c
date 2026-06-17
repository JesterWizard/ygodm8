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

  if (cardId != TORPEDO_FISH)
    return FALSE;

  return gDuel.field == FIELD_UMI;
}
