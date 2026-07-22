#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"
#include "neo_space.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static const char sNeosName[] APPEND_RODATA = "Neos";

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == NEO_SPACE || cardId == PSEUDO_SPACE || cardId == HARPIES_HUNTING_GROUND
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE)
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

/* ELEMENTAL_HERO_NEOS or Fusion that specifically lists it as material. */
u8 NeoSpace_IsAtkTarget(u16 cardId)
{
  const struct FusionRecipe *recipe;
  u8 i;
  u8 materialCount;

  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;

  if (cardId == ELEMENTAL_HERO_NEOS)
    return TRUE;

  /* Fusion color via gCardData_NEW — no SetCardInfo in overlay path. */
  if (cardId >= NUM_TOTAL_CARDS || gCardData_NEW[cardId].color != COLOR_FUSION)
    return FALSE;

  recipe = FusionRecipe_FindByResult(cardId);
  if (recipe != NULL) {
    materialCount = FusionRecipe_MaterialCount(recipe);
    for (i = 0; i < materialCount; i++) {
      if (FusionRecipe_MaterialAt(recipe, i) == ELEMENTAL_HERO_NEOS)
        return TRUE;
    }
  }

  /* Contact Fusions (Air Neos, etc.) are not in gFusionRecipes — name heuristic. */
  return Duel_CardNameContains(cardId, sNeosName);
}

static u8 NeoSpaceFaceUpOnField(void)
{
  return Duel_FindBackrowCard(DUEL_PLAYER, NEO_SPACE, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, NEO_SPACE, TRUE) != NULL;
}

void ApplyNeoSpaceAtkBoostForZone(struct DuelCard *zone)
{
  if (zone == NULL || !NeoSpaceFaceUpOnField() || !NeoSpace_IsAtkTarget(zone->id))
    return;
  if (gCardInfo.atk == 0xFFFF)
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + 500);
}

u8 NeoSpace_PreventsEndPhaseExtraDeckReturn(const struct DuelCard *zone)
{
  if (zone == NULL || !NeoSpaceFaceUpOnField())
    return FALSE;

  return NeoSpace_IsAtkTarget(zone->id);
}

static void NEO_SPACE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(NEO_SPACE);
  /* Parent: ApplyNeoSpaceAtkBoostForZone in card_hooks; NeoSpace_PreventsEndPhaseExtraDeckReturn
   * in Contact Fusion End Phase return (with InstantNeoSpace). */
}

APPEND_TEXT void EffectNEO_SPACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(NEO_SPACE, NEO_SPACE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NEO_SPACE_SelfCheck(void)
{
  if (!NeoSpace_IsAtkTarget(ELEMENTAL_HERO_NEOS))
    while (1)
      ;
  if (!NeoSpace_IsAtkTarget(ELEMENTAL_HERO_AIR_NEOS))
    while (1)
      ;
  if (NeoSpace_IsAtkTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
