#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static const char sMorphtronicArchetypeName[] APPEND_RODATA = "Morphtronic";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicArchetypeName);
}

static u8 IsValidMorphtronicCordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsMorphtronicMonster(zone->id);
}

static u8 HasMorphtronicCordTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMorphtronicCordTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 MorphtronicCord_ShouldDestroySpellTrapOnPositionChange(const struct DuelCard *zone)
{
  return DynamicEquipTargetsMonsterWithSpell(zone, MORPHTRONIC_CORD);
}

static void EquipMorphtronicCord(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, MORPHTRONIC_CORD, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
}

static void ResolveMorphtronicCordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidMorphtronicCordTarget(fixedRow, fixedCol))
    return;

  EquipMorphtronicCord(spellZone, target);
}

static void CancelMorphtronicCordTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == MORPHTRONIC_CORD)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickMorphtronicCordTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidMorphtronicCordTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 CanActivateMORPHTRONIC_CORD(void)
{
  return HasMorphtronicCordTarget();
}

static void MORPHTRONIC_CORD_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_CORD);

  if (IsDuelOver() == TRUE || !CanActivateMORPHTRONIC_CORD())
    return;
gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMorphtronicCordTarget, ResolveMorphtronicCordTarget,
                     CancelMorphtronicCordTargeting, AiPickMorphtronicCordTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMORPHTRONIC_CORD(void)
{
  if (!CanActivateMORPHTRONIC_CORD()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_CORD, MORPHTRONIC_CORD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MorphtronicCord_SelfCheck(void)
{
  if (!IsMorphtronicMonster(MORPHTRONIC_CELFON))
    while (1)
      ;
  if (IsMorphtronicMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
