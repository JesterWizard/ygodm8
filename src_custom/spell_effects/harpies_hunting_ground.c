#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE || cardId == SKYSCRAPER_2_HERO_CITY
      || cardId == SKYSCRAPER || cardId == WETLANDS || cardId == GEARTOWN || cardId == DRAGON_RAVINE
      || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static void HARPIES_HUNTING_GROUND_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(HARPIES_HUNTING_GROUND);

  /* ponytail: +200 ATK/DEF for all Winged Beast monsters needs a field-stat
   * applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster
   * ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade:
   * LynJump/stat overlay → if face-up HARPIES_HUNTING_GROUND and
   * TYPE_WINGED_BEAST then ATK/DEF += 200. */
  /* ponytail: on Normal/Special Summon of Harpie Lady / Harpie Lady Sisters
   * (name-treated), summoner destroys 1 S/T — needs a summon-listener outside
   * this file. Ceiling: no trigger from spell file alone; upgrade: after-summon
   * hook → if face-up HARPIES_HUNTING_GROUND and summoned id is HARPIE_LADY /
   * HARPIE_LADY_1/2/3 / HARPIE_LADY_SISTERS (or name "Harpie Lady") then
   * PickZone destroy 1 Spell/Trap. */
}

APPEND_TEXT void EffectHARPIES_HUNTING_GROUND(void)
{
  if (Duel_TryResolveSpellThroughTraps(HARPIES_HUNTING_GROUND,
                                       HARPIES_HUNTING_GROUND_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HARPIES_HUNTING_GROUND_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(HARPIE_LADY, TYPE_WINGED_BEAST))
    while (1)
      ;
  if (Duel_CardHasMonsterType(DARK_MAGICIAN, TYPE_WINGED_BEAST))
    while (1)
      ;
}
#endif
