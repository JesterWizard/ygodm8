#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

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

static u8 IsValidRustyEngineTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsMorphtronicMonster(zone->id);
}

static u8 HasRustyEngineTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidRustyEngineTarget(ActiveMonsterFixedRow(), col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateMORPHTRONIC_RUSTY_ENGINE(void)
{
  return HasRustyEngineTarget();
}

void MorphtronicRustyEngine_InflictDestroyBurn(const struct DuelCard *target)
{
  u16 originalAtk;

  if (!DynamicEquipTargetsMonsterWithSpell(target, MORPHTRONIC_RUSTY_ENGINE))
    return;

  SetCardInfo(target->id);
  originalAtk = gCardInfo.atk;
  if (originalAtk == 0)
    return;

  if (Duel_ChangeLp(DUEL_PLAYER, -(s32)originalAtk, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ChangeLp(DUEL_OPPONENT, -(s32)originalAtk, TRUE);
}

static void DestroyRustyEngineSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == MORPHTRONIC_RUSTY_ENGINE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveRustyEngineTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!IsValidRustyEngineTarget(fixedRow, fixedCol))
    return;

  if (spellZone == NULL || spellZone->id != MORPHTRONIC_RUSTY_ENGINE)
    return;

  /* Stash target in row2/col2 for equip bookkeeping (no file-level BSS). */
  gSpellEffectData.row2 = fixedRow;
  gSpellEffectData.col2 = fixedCol;

  if (!RegisterDynamicEquip(spellZone, target, MORPHTRONIC_RUSTY_ENGINE, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* Parent wire: before clearing a MORPHTRONIC_RUSTY_ENGINE dynamic-equip
   * spell link, call MorphtronicRustyEngine_InflictDestroyBurn(targetZone). */
}

static void CancelRustyEngineTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyRustyEngineSpellZone();
}

static u8 AiPickRustyEngineTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidRustyEngineTarget(monsterRow, col))
      continue;

    *outRow = monsterRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void MORPHTRONIC_RUSTY_ENGINE_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_RUSTY_ENGINE);

  if (IsDuelOver() == TRUE || !CanActivateMORPHTRONIC_RUSTY_ENGINE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidRustyEngineTarget, ResolveRustyEngineTarget,
                     CancelRustyEngineTargeting, AiPickRustyEngineTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMORPHTRONIC_RUSTY_ENGINE(void)
{
  if (!CanActivateMORPHTRONIC_RUSTY_ENGINE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_RUSTY_ENGINE,
                                       MORPHTRONIC_RUSTY_ENGINE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MORPHTRONIC_RUSTY_ENGINE_SelfCheck(void)
{
  if (!IsMorphtronicMonster(MORPHTRONIC_CELFON))
    while (1)
      ;
  if (IsMorphtronicMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
