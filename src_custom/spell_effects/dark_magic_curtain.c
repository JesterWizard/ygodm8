#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 CanSpecialSummonWithDarkMagicCurtain(void)
{
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

APPEND_TEXT void EffectDarkMagicCurtain(void)
{
  u16 halfLp;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  if (WhoseTurn() == DUEL_PLAYER)
    halfLp = gDuelLifePoints[DUEL_PLAYER] / 2;
  else
    halfLp = gDuelLifePoints[DUEL_OPPONENT] / 2;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)halfLp, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(DARK_MAGIC_CURTAIN);

  if (IsDuelOver() == TRUE || !CanSpecialSummonWithDarkMagicCurtain())
    return;

  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, DARK_MAGICIAN, Duel_DefaultSpecialSummonOpts(FALSE));
}
