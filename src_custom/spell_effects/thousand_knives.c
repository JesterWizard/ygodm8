#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "spell_effects.h"

static u8 FieldHasDarkMagician(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], DARK_MAGICIAN);
}

static void ClearInactiveDuelistRow(u8 row)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (!IsGodCard(gTurnZones[row][i]->id))
      Duel_DestroyZone(gTurnZones[row][i], INACTIVE_DUELIST, FALSE);
  }
}

APPEND_TEXT void EffectThousandKnives(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (!FieldHasDarkMagician())
    return;

  ClearInactiveDuelistRow(INACTIVE_DUELIST_BACKROW);
  ClearInactiveDuelistRow(INACTIVE_DUELIST_MONSTER_ROW);
  Duel_ShowEffectText(THOUSAND_KNIVES);
}
