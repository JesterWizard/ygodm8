#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sDarkMagicianGirlName[] APPEND_RODATA = "Dark Magician Girl";

static u8 IsDarkMagicianGirlMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == DARK_MAGICIAN_GIRL)
    return TRUE;

  return Duel_CardNameContains(cardId, sDarkMagicianGirlName);
}

static u8 ControlsDarkMagician(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], DARK_MAGICIAN);
}

static u8 ControlsDarkMagicianGirl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDarkMagicianGirlMonster(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateDARK_BURNING_MAGIC(void)
{
  return ControlsDarkMagician() && ControlsDarkMagicianGirl();
}

static void ClearInactiveDuelistRow(u8 row)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[row][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (IsGodCard(zone->id))
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

static void DestroyAllOpponentCards(void)
{
  ClearInactiveDuelistRow(INACTIVE_DUELIST_MONSTER_ROW);
  if (IsDuelOver() == TRUE)
    return;

  ClearInactiveDuelistRow(INACTIVE_DUELIST_BACKROW);
  NotifyDynamicEquipFieldChanged();
}

static void DARK_BURNING_MAGIC_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(DARK_BURNING_MAGIC);

  if (IsDuelOver() == TRUE)
    return;

  if (!CanActivateDARK_BURNING_MAGIC()) {
    if (spellZone != NULL && spellZone->id == DARK_BURNING_MAGIC)
      Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    else
      UpdateDuelGfxExceptField();
    return;
  }

  DestroyAllOpponentCards();
  if (IsDuelOver() == TRUE)
    return;

  if (spellZone != NULL && spellZone->id == DARK_BURNING_MAGIC)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();

  NotifyDynamicEquipFieldChanged();
}

APPEND_TEXT void EffectDARK_BURNING_MAGIC(void)
{
  if (!CanActivateDARK_BURNING_MAGIC()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DARK_BURNING_MAGIC, DARK_BURNING_MAGIC_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DarkBurningMagic_SelfCheck(void)
{
  if (!IsDarkMagicianGirlMonster(DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (IsDarkMagicianGirlMonster(DARK_MAGICIAN))
    while (1)
      ;
}
#endif
