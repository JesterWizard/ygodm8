#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

/* 1 stage ~= 500 ATK. Printed +300; nearest stage unit is +500. */
#define GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGES 1

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

static u8 IsValidGladiusTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsGladiatorBeastMonster(zone->id);
}

static u8 HasGladiusTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidGladiusTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateGLADIATOR_BEASTS_BATTLE_GLADIUS(void)
{
  return HasGladiusTarget();
}

static void EquipGladius(struct DuelCard *spellZone, struct DuelCard *target)
{
  /* ponytail: stage unit is 500 ATK — applied +500, not printed +300.
   * Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART
   * after listing GLADIATOR_BEASTS_BATTLE_GLADIUS in IsActiveDynamicEquipSpellZone. */

  ApplyDynamicEquipStages(target, GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, GLADIATOR_BEASTS_BATTLE_GLADIUS,
                            GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: recycle-to-hand when equipped monster returns to Deck (tag-out) and
   * this card is sent to GY needs a return-to-deck / equip-send hook outside this
   * file. Ceiling: equip +ATK only; upgrade: on GB return-to-deck → if linked
   * GLADIATOR_BEASTS_BATTLE_GLADIUS hits GY then Duel_AddDeckCardToHand / GY→hand. */
}

static void ResolveGladiusTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidGladiusTarget(fixedRow, fixedCol))
    return;

  EquipGladius(spellZone, target);
}

static void CancelGladiusTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == GLADIATOR_BEASTS_BATTLE_GLADIUS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickGladiusTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidGladiusTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void GLADIATOR_BEASTS_BATTLE_GLADIUS_ResolveBody(void)
{
  Duel_ShowEffectText(GLADIATOR_BEASTS_BATTLE_GLADIUS);

  if (IsDuelOver() == TRUE || !CanActivateGLADIATOR_BEASTS_BATTLE_GLADIUS())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidGladiusTarget, ResolveGladiusTarget, CancelGladiusTargeting,
                     AiPickGladiusTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectGLADIATOR_BEASTS_BATTLE_GLADIUS(void)
{
  if (!CanActivateGLADIATOR_BEASTS_BATTLE_GLADIUS()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(GLADIATOR_BEASTS_BATTLE_GLADIUS,
                                       GLADIATOR_BEASTS_BATTLE_GLADIUS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GladiatorBeastsBattleGladius_SelfCheck(void)
{
  if (!IsGladiatorBeastMonster(GLADIATOR_BEAST_ANDAL))
    while (1)
      ;
  if (IsGladiatorBeastMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
