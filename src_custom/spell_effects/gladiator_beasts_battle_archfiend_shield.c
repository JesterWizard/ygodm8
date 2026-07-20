#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static const char sGladiatorBeastArchetypeName[] APPEND_RODATA = "Gladiator Beast";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastArchetypeName);
}

static u8 IsValidArchfiendShieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsGladiatorBeastMonster(zone->id);
}

static u8 HasArchfiendShieldTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidArchfiendShieldTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateGLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD(void)
{
  return HasArchfiendShieldTarget();
}

static void EquipArchfiendShield(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting; link cleanup may not treat this as active
   * equip. Ceiling: add GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD to card_hooks
   * GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone;
   * upgrade: same as H_HEATED_HEART. */

  /* ponytail: "if equipped would be destroyed, destroy this instead" needs a
   * destroy-substitute gate outside this file (no in-file Duel_DestroyZone
   * redirect). Ceiling: equip link only; upgrade: Duel_DestroyZone → if
   * DynamicEquipTargetsMonsterWithSpell(zone, ARCHFIEND_SHIELD) then destroy
   * the equip spell instead. */

  /* ponytail: recycle-to-hand when equipped monster returns to Deck (tag-out)
   * and this card is sent to GY needs a return-to-deck / equip-send hook outside
   * this file. Ceiling: equip only; upgrade: on GB return-to-deck → if linked
   * ARCHFIEND_SHIELD hits GY then add it from GY to hand. */
}

static void ResolveArchfiendShieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidArchfiendShieldTarget(fixedRow, fixedCol))
    return;

  EquipArchfiendShield(spellZone, target);
}

static void CancelArchfiendShieldTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickArchfiendShieldTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidArchfiendShieldTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD_ResolveBody(void)
{
  Duel_ShowEffectText(GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD);

  if (IsDuelOver() == TRUE || !CanActivateGLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidArchfiendShieldTarget, ResolveArchfiendShieldTarget,
                     CancelArchfiendShieldTargeting, AiPickArchfiendShieldTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectGLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD(void)
{
  if (!CanActivateGLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD,
                                       GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GladiatorBeastsBattleArchfiendShield_SelfCheck(void)
{
  if (!IsGladiatorBeastMonster(GLADIATOR_BEAST_ANDAL))
    while (1)
      ;
  if (IsGladiatorBeastMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
