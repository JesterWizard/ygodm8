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

static u8 IsValidHalberdTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsGladiatorBeastMonster(zone->id);
}

static u8 HasHalberdTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidHalberdTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateGLADIATOR_BEAST_BATTLE_HALBERD(void)
{
  return HasHalberdTarget();
}

static void EquipHalberd(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, GLADIATOR_BEAST_BATTLE_HALBERD, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: when equipped attacks → destroy 1 S/T at end of Damage Step needs
   * a battle_effects Damage Step end hook + S/T PickZone outside this file.
   * Ceiling: equip-only works; destroy trigger not wired from this file.
   * Upgrade: end-of-Damage-Step after equipped attacked → if
   * DynamicEquipTargetsMonsterWithSpell(..., GLADIATOR_BEAST_BATTLE_HALBERD)
   * then PickZone destroy 1 Spell/Trap. */

  /* ponytail: recycle-to-hand when equipped monster returns to Deck (tag-out)
   * and this card is sent to GY needs a return-to-deck / equip-send hook
   * outside this file. Ceiling: equip only; upgrade: on GB return-to-deck → if
   * linked GLADIATOR_BEAST_BATTLE_HALBERD hits GY then GY→hand. */

}

static void ResolveHalberdTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidHalberdTarget(fixedRow, fixedCol))
    return;

  EquipHalberd(spellZone, target);
}

static void CancelHalberdTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == GLADIATOR_BEAST_BATTLE_HALBERD)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickHalberdTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidHalberdTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void GLADIATOR_BEAST_BATTLE_HALBERD_ResolveBody(void)
{
  Duel_ShowEffectText(GLADIATOR_BEAST_BATTLE_HALBERD);

  if (IsDuelOver() == TRUE || !CanActivateGLADIATOR_BEAST_BATTLE_HALBERD())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidHalberdTarget, ResolveHalberdTarget, CancelHalberdTargeting,
                     AiPickHalberdTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectGLADIATOR_BEAST_BATTLE_HALBERD(void)
{
  if (!CanActivateGLADIATOR_BEAST_BATTLE_HALBERD()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(GLADIATOR_BEAST_BATTLE_HALBERD,
                                       GLADIATOR_BEAST_BATTLE_HALBERD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GladiatorBeastBattleHalberd_SelfCheck(void)
{
  if (!IsGladiatorBeastMonster(GLADIATOR_BEAST_ANDAL))
    while (1)
      ;
  if (IsGladiatorBeastMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
