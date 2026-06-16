#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 FieldHasDarkMagicianGirl(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], DARK_MAGICIAN_GIRL);
}

static u8 CanSpecialSummonWithSagesStone(void)
{
  if (!FieldHasDarkMagicianGirl())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

APPEND_TEXT void EffectSagesStone(void)
{
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);
  Duel_ShowEffectText(SAGES_STONE);

  if (IsDuelOver() == TRUE || !CanSpecialSummonWithSagesStone())
    return;

  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, DARK_MAGICIAN, Duel_DefaultSpecialSummonOpts(FALSE));
}
