#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 ControlsDarkMagician(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], DARK_MAGICIAN);
}

static u8 CanActivateDarkMagicAttack(void)
{
  return ControlsDarkMagician();
}

static void DestroyOpponentSpellsAndTraps(void)
{
  u8 col;
  u8 destroyed = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][col];

    if (zone == NULL || zone->id == CARD_NONE || !IsSpellOrTrapCard(zone->id))
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;

    destroyed = TRUE;
  }

  if (destroyed)
    NotifyDynamicEquipFieldChanged();
}

static void DARK_MAGIC_ATTACK_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(DARK_MAGIC_ATTACK);

  if (IsDuelOver() == TRUE || !CanActivateDarkMagicAttack())
    return;

  DestroyOpponentSpellsAndTraps();
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  NotifyDynamicEquipFieldChanged();
}

APPEND_TEXT void EffectDARK_MAGIC_ATTACK(void)
{
  if (!CanActivateDarkMagicAttack()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DARK_MAGIC_ATTACK, DARK_MAGIC_ATTACK_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
