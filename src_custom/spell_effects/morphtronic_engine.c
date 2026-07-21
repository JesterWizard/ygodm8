#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define MORPHTRONIC_ENGINE_STANDBY_TURNS 2
#define MORPHTRONIC_ENGINE_TARGET_LEVEL 3

void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 IsLevel3Morphtronic(u16 cardId)
{
  if (!IsMorphtronicMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level == MORPHTRONIC_ENGINE_TARGET_LEVEL;
}

static u8 IsValidMorphtronicEngineTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsLevel3Morphtronic(zone->id);
}

static u8 HasMorphtronicEngineTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMorphtronicEngineTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateMORPHTRONIC_ENGINE(void)
{
  return HasMorphtronicEngineTarget();
}

static u8 StagesToDoubleOriginalAtk(u16 cardId)
{
  u16 originalAtk;
  s32 needed;

  SetCardInfo(cardId);
  originalAtk = gCardInfo.atk;
  if (originalAtk == 0)
    return 0;

  /* 1 stage ~= 500 ATK; nearest stage to +original (double). */
  needed = (s32)originalAtk;
  return (u8)((needed + 250) / 500);
}

static void EquipMorphtronicEngine(struct DuelCard *spellZone, struct DuelCard *target)
{
  u8 stages = StagesToDoubleOriginalAtk(target->id);

  /* ponytail: stage unit is 500 ATK — nearest-stage double, not exact
   * original×2 when ATK is not a multiple of 500. Ceiling: stage-approx only;
   * upgrade: exact-ATK overlay while equipped (clone Power Bond / Big Bang Shot). */

  if (stages > 0)
    ApplyDynamicEquipStages(target, stages);

  if (!RegisterDynamicEquip(spellZone, target, MORPHTRONIC_ENGINE, stages))
    return;

  Duel_ActivateContinuousZone(spellZone);
  if (spellZone != NULL)
    spellZone->permStage = 0;

  NotifyDynamicEquipFieldChanged();
  Duel_NotifyMonsterZoneChanged(target);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveMorphtronicEngineTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidMorphtronicEngineTarget(fixedRow, fixedCol))
    return;

  EquipMorphtronicEngine(spellZone, target);
}

static void CancelMorphtronicEngineTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == MORPHTRONIC_ENGINE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickMorphtronicEngineTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidMorphtronicEngineTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 IsActivatedMorphtronicEngineZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == MORPHTRONIC_ENGINE && zone->isFaceUp == TRUE;
}

static u16 EquippedMonsterOriginalAtk(struct DuelCard *spellZone)
{
  u8 i;
  u8 spellRow;
  u8 spellCol;

  if (!Duel_FindFixedZone(spellZone, &spellRow, &spellCol))
    return 0;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *target;

    if (!link->active || link->spellId != MORPHTRONIC_ENGINE)
      continue;
    if (link->spellFixedRow != spellRow || link->spellFixedCol != spellCol)
      continue;

    target = gFixedZones[link->targetFixedRow][link->targetFixedCol];
    if (target == NULL || target->id == CARD_NONE)
      return 0;

    SetCardInfo(target->id);
    return gCardInfo.atk;
  }

  return 0;
}

static void ResolveMorphtronicEngineStandby(struct DuelCard *spellZone)
{
  u16 burn = EquippedMonsterOriginalAtk(spellZone);

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  if (IsDuelOver() == TRUE)
    return;

  if (burn > 0)
    Duel_ChangeLp(ACTIVE_DUELIST, -(s32)burn, TRUE);
}

void TryApplyMorphtronicEngineStandby(void)
{
  u8 i;
  struct DuelCard *spellZone;

  if (IsDuelOver() == TRUE)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (!IsActivatedMorphtronicEngineZone(spellZone))
      continue;

    IncrementPermStage(spellZone);
    if (spellZone->permStage < MORPHTRONIC_ENGINE_STANDBY_TURNS)
      continue;

    ResolveMorphtronicEngineStandby(spellZone);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static void MORPHTRONIC_ENGINE_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_ENGINE);

  if (IsDuelOver() == TRUE || !CanActivateMORPHTRONIC_ENGINE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMorphtronicEngineTarget, ResolveMorphtronicEngineTarget,
                     CancelMorphtronicEngineTargeting, AiPickMorphtronicEngineTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMORPHTRONIC_ENGINE(void)
{
  if (!CanActivateMORPHTRONIC_ENGINE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_ENGINE, MORPHTRONIC_ENGINE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MORPHTRONIC_ENGINE_SelfCheck(void)
{
  if (!IsLevel3Morphtronic(MORPHTRONIC_DATATRON))
    while (1)
      ;
  if (IsLevel3Morphtronic(MORPHTRONIC_CELFON))
    while (1)
      ;
  if (MORPHTRONIC_ENGINE_STANDBY_TURNS != 2)
    while (1)
      ;
}
#endif
