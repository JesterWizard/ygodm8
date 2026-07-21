#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "double_tool_c_and_d.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";
static const char sPowerToolDragonName[] APPEND_RODATA = "Power Tool Dragon";

struct DoubleToolActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
};

extern struct DoubleToolActionData sActionData;

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsDoubleToolEquipTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardNameContains(cardId, sPowerToolDragonName))
    return TRUE;

  if (!Duel_CardNameContains(cardId, sMorphtronicName))
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_MACHINE))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 4;
}

static u8 IsValidEquipTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsDoubleToolEquipTarget(zone->id);
}

static u8 HasEquipTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidEquipTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 DoubleToolEquippedMonsterController(const struct DuelCard *zone, u8 *fixedDuelist)
{
  u8 row;
  u8 col;

  if (zone == NULL || !DynamicEquipTargetsMonsterWithSpell(zone, DOUBLE_TOOL_C_AND_D))
    return FALSE;
  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &row, &col))
    return FALSE;

  *fixedDuelist = Duel_FixedDuelistForMonsterRow(row);
  return TRUE;
}

static u8 FixedDuelistForMonster(const struct DuelCard *zone, u8 *fixedDuelist)
{
  u8 row;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &row, &col))
    return FALSE;

  *fixedDuelist = Duel_FixedDuelistForMonsterRow(row);
  return TRUE;
}

void ApplyDoubleToolCAndDAtkBonusToCardInfo(const struct DuelCard *zone)
{
  u8 controller;

  if (!DoubleToolEquippedMonsterController(zone, &controller) || WhoseTurn() != controller)
    return;
  if (gCardInfo.atk == 0xFFFF)
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + DOUBLE_TOOL_C_AND_D_ATK_BOOST);
}

/* ponytail: attack-target negate/redirect need attacker-context selection hook.
 * Ceiling: ATK overlay + battle destroy wired; upgrade: call ShouldNegate /
 * GetAttackRedirectTarget from attack-declare / target-pick path. */
u8 DoubleTool_ShouldNegateAttackTargetEffects(const struct DuelCard *attacker,
                                              const struct DuelCard *target)
{
  u8 attackerController;
  u8 targetController;

  if (!DoubleToolEquippedMonsterController(attacker, &attackerController)
      || WhoseTurn() != attackerController)
    return FALSE;
  if (!FixedDuelistForMonster(target, &targetController))
    return FALSE;

  return targetController != attackerController;
}

struct DuelCard *DoubleTool_GetAttackRedirectTarget(const struct DuelCard *attacker)
{
  u8 attackerController;
  u8 targetController;
  u8 equippedController;
  u8 col;
  struct DuelCard *target;

  if (!FixedDuelistForMonster(attacker, &attackerController)
      || WhoseTurn() != attackerController)
    return NULL;

  targetController = attackerController == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    target = gFixedZones[Duel_FixedMonsterRowForDuelist(targetController)][col];
    if (DoubleToolEquippedMonsterController(target, &equippedController))
      return target;
  }

  return NULL;
}

u8 DoubleTool_ShouldDestroyBattleOpponent(const struct DuelCard *attacker,
                                          const struct DuelCard *defender)
{
  u8 equippedController;
  u8 opponentController;

  if (DoubleToolEquippedMonsterController(attacker, &equippedController)) {
    if (WhoseTurn() != equippedController
        && FixedDuelistForMonster(defender, &opponentController)
        && opponentController != equippedController)
      return TRUE;
  }

  if (DoubleToolEquippedMonsterController(defender, &equippedController)) {
    if (WhoseTurn() != equippedController
        && FixedDuelistForMonster(attacker, &opponentController)
        && opponentController != equippedController)
      return TRUE;
  }

  return FALSE;
}

void ApplyDoubleToolCAndDBattleEffect(void)
{
  struct DuelCard *playerZone;
  struct DuelCard *opponentZone;
  struct DuelCard *attacker;
  struct DuelCard *defender;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return;
  if (sActionData.playerCardId == CARD_NONE || sActionData.opponentCardId == CARD_NONE)
    return;

  playerZone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
  opponentZone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
  if (playerZone == NULL || opponentZone == NULL
      || playerZone->id != sActionData.playerCardId
      || opponentZone->id != sActionData.opponentCardId)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    attacker = playerZone;
    defender = opponentZone;
  } else {
    attacker = opponentZone;
    defender = playerZone;
  }

  if (DoubleTool_ShouldDestroyBattleOpponent(attacker, defender))
    Duel_DestroyZone(defender, GetDuelistForZone(defender), TRUE);
}

static void DoubleToolOnTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *monster = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ClearPickZone();
  if (monster == NULL || spellZone == NULL)
    return;

  if (!RegisterDynamicEquip(spellZone, monster, DOUBLE_TOOL_C_AND_D, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_RefreshMonsterStatOverlays();
}

static void DoubleToolCancel(void)
{
  Duel_ClearPickZone();
}

static u8 DoubleToolValidate(u8 fixedRow, u8 fixedCol)
{
  return IsValidEquipTarget(fixedRow, fixedCol);
}

static u8 DoubleToolAiPick(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidEquipTarget(row, col))
      continue;
    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 CanActivateDOUBLE_TOOL_C_AND_D(void)
{
  return HasEquipTarget();
}

static void DOUBLE_TOOL_C_AND_D_ResolveBody(void)
{
  if (!CanActivateDOUBLE_TOOL_C_AND_D()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(DOUBLE_TOOL_C_AND_D);
  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  Duel_SetupPickZone(DoubleToolValidate, DoubleToolOnTarget, DoubleToolCancel,
                     DoubleToolAiPick);
  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectDOUBLE_TOOL_C_AND_D(void)
{
  if (Duel_TryResolveSpellThroughTraps(DOUBLE_TOOL_C_AND_D, DOUBLE_TOOL_C_AND_D_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
