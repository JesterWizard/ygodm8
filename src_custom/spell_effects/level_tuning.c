#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 HasFaceUpOwnMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (MonsterIsFaceUp(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateLEVEL_TUNING(void)
{
  return HasFaceUpOwnMonster();
}

static void LEVEL_TUNING_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(LEVEL_TUNING);

  if (IsDuelOver() == TRUE)
    return;

  /* ponytail: no TempLevel / zone level-mod field (DuelCard has only tempStage;
   * level lives in ROM card data via SetCardInfo). Cannot apply -1 Level here.
   * End Phase restore also needs a turn hook outside this file.
   * Ceiling: printed Level unchanged; upgrade: TempLevel overlay +
   * turn_effect_hooks End Phase clear that restores marked zones. */

  if (spellZone != NULL && spellZone->id == LEVEL_TUNING)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectLEVEL_TUNING(void)
{
  if (!CanActivateLEVEL_TUNING()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(LEVEL_TUNING, LEVEL_TUNING_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
