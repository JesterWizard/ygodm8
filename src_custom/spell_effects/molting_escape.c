#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 IsValidMoltingEscapeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsReptileMonster(zone->id);
}

static u8 HasMoltingEscapeTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMoltingEscapeTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateMOLTING_ESCAPE(void)
{
  return HasMoltingEscapeTarget();
}

static void EquipMoltingEscape(struct DuelCard *spellZone, struct DuelCard *target)
{
  /* No ATK on equip — printed +300 applies only when OPT battle-protect fires. */
  if (!RegisterDynamicEquip(spellZone, target, MOLTING_ESCAPE, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: OPT battle-protect + +300 ATK when applied needs a battle_effects /
   * CanMonsterBeDestroyedByBattle / damage-step hook outside this file (like
   * Spirit Reaper / Kishido via Duel_ApplyBattleDestroyProtection).
   * Ceiling: Reptile equip register only; upgrade: if DynamicEquipTargetsMonsterWithSpell
   * (zone, MOLTING_ESCAPE) and effectUsedThisTurn clear, skip battle destroy once,
   * then mark OPT + apply +300 (exact overlay or nearest stage) at Damage Step end. */
}

static void ResolveMoltingEscapeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidMoltingEscapeTarget(fixedRow, fixedCol))
    return;

  EquipMoltingEscape(spellZone, target);
}

static void CancelMoltingEscapeTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == MOLTING_ESCAPE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickMoltingEscapeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidMoltingEscapeTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void MOLTING_ESCAPE_ResolveBody(void)
{
  Duel_ShowEffectText(MOLTING_ESCAPE);

  if (IsDuelOver() == TRUE || !CanActivateMOLTING_ESCAPE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMoltingEscapeTarget, ResolveMoltingEscapeTarget,
                     CancelMoltingEscapeTargeting, AiPickMoltingEscapeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMOLTING_ESCAPE(void)
{
  if (!CanActivateMOLTING_ESCAPE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MOLTING_ESCAPE, MOLTING_ESCAPE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MOLTING_ESCAPE_SelfCheck(void)
{
  if (!IsReptileMonster(REPTILIANNE_NAGA))
    while (1)
      ;
  if (IsReptileMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
