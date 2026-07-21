#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

/* 1 stage ~= 500 ATK. Printed +300; nearest stage unit is +500. */
#define GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGES 1
#define GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGE_BONUS 500
#define GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_BONUS 300
#define GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_CORRECTION \
  (GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGE_BONUS - GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_BONUS)

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

void ApplyGladiatorBeastsBattleGladiusAtkCorrection(const struct DuelCard *zone)
{
  if (!DynamicEquipTargetsMonsterWithSpell(zone, GLADIATOR_BEASTS_BATTLE_GLADIUS))
    return;

  if (gCardInfo.atk < GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_CORRECTION)
    gCardInfo.atk = 0;
  else
    gCardInfo.atk -= GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_CORRECTION;
}

u8 GladiatorBeastsBattleGladius_RecyclesWhenTargetReturnsToDeck(const struct DuelCard *zone)
{
  return DynamicEquipTargetsMonsterWithSpell(zone, GLADIATOR_BEASTS_BATTLE_GLADIUS);
}

static void EquipGladius(struct DuelCard *spellZone, struct DuelCard *target)
{
  ApplyDynamicEquipStages(target, GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, GLADIATOR_BEASTS_BATTLE_GLADIUS,
                            GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
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
  if (GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_STAGE_BONUS
          - GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_CORRECTION
      != GLADIATOR_BEASTS_BATTLE_GLADIUS_ATK_BONUS)
    while (1)
      ;
}
#endif
