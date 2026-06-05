#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
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

static void InitSummonedMonsterZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static void SpecialSummonDarkMagicianWithSagesStone(void)
{
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonWithSagesStone())
    return;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterZone < 0)
    return;

  summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
  summonZone->id = DARK_MAGICIAN;
  InitSummonedMonsterZone(summonZone);
}

APPEND_TEXT void EffectSagesStone(void)
{
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = SAGES_STONE;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonDarkMagicianWithSagesStone();
}
