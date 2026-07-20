#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"
#include "spell_effects.h"

static const char sNeosName[] APPEND_RODATA = "Neos";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 FusionListsElementalHeroNeos(u16 cardId)
{
  const struct FusionRecipe *recipe;
  u8 i;
  u8 materialCount;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
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
  if (cardId == ELEMENTAL_HERO_NEOS)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeosName);
}

static u8 IsValidInstantNeoSpaceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return FusionListsElementalHeroNeos(zone->id);
}

static u8 HasInstantNeoSpaceTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidInstantNeoSpaceTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateInstantNeoSpace(void)
{
  return HasInstantNeoSpaceTarget();
}

static void EquipInstantNeoSpace(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, INSTANT_NEO_SPACE, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: "does not shuffle into Extra Deck during End Phase" needs an
   * End Phase Contact-return suppress flag outside this file (Neos Contact
   * return hooks live in permanent/turn effects).
   * Ceiling: equip link only; upgrade: if DynamicEquipTargetsMonsterWithSpell
   * (INSTANT_NEO_SPACE) then skip End Phase Extra Deck shuffle for that zone. */

  /* ponytail: leave-field → SS 1 ELEMENTAL_HERO_NEOS from hand/Deck/GY needs a
   * destroy/leave hook outside this file (OnDynamicEquipZoneAboutToClear).
   * Ceiling: equip-only works; revive not wired from this file.
   * Upgrade: leave-hook → Duel_SpecialSummonFromHand/Deck/Grave(ELEMENTAL_HERO_NEOS). */

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting; link cleanup may not treat this as active
   * equip. Ceiling: add INSTANT_NEO_SPACE to card_hooks GetSpellType EQUIP list and
   * dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART. */
}

static void ResolveInstantNeoSpaceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidInstantNeoSpaceTarget(fixedRow, fixedCol))
    return;

  EquipInstantNeoSpace(spellZone, target);
}

static void CancelInstantNeoSpaceTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == INSTANT_NEO_SPACE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickInstantNeoSpaceTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidInstantNeoSpaceTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void INSTANT_NEO_SPACE_ResolveBody(void)
{
  Duel_ShowEffectText(INSTANT_NEO_SPACE);

  if (IsDuelOver() == TRUE || !CanActivateInstantNeoSpace())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidInstantNeoSpaceTarget, ResolveInstantNeoSpaceTarget,
                     CancelInstantNeoSpaceTargeting, AiPickInstantNeoSpaceTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectINSTANT_NEO_SPACE(void)
{
  if (!CanActivateInstantNeoSpace()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(INSTANT_NEO_SPACE, INSTANT_NEO_SPACE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void INSTANT_NEO_SPACE_SelfCheck(void)
{
  if (FusionListsElementalHeroNeos(ELEMENTAL_HERO_NEOS))
    while (1)
      ;
  if (!FusionListsElementalHeroNeos(ELEMENTAL_HERO_AIR_NEOS))
    while (1)
      ;
  if (FusionListsElementalHeroNeos(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
