#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u16 GetOriginalAtk(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.atk;
}

static u8 IsValidExplosiveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsAncientGearMonster(zone->id);
}

static u8 HasExplosiveTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidExplosiveTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateANCIENT_GEAR_EXPLOSIVE(void)
{
  return HasExplosiveTarget();
}

static void DestroyExplosiveSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == ANCIENT_GEAR_EXPLOSIVE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveExplosiveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u16 originalAtk;
  u16 burn;

  if (!IsValidExplosiveTarget(fixedRow, fixedCol))
    return;

  originalAtk = GetOriginalAtk(zone->id);
  burn = originalAtk / 2;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (burn > 0 && Duel_ChangeLp(INACTIVE_DUELIST, -(s32)burn, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  DestroyExplosiveSpellZone();
}

static void CancelExplosiveTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyExplosiveSpellZone();
}

static u8 AiPickExplosiveTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidExplosiveTarget(row, col))
      continue;

    zone = gFixedZones[row][col];
    atk = GetOriginalAtk(zone->id);
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ANCIENT_GEAR_EXPLOSIVE_ResolveBody(void)
{
  Duel_ShowEffectText(ANCIENT_GEAR_EXPLOSIVE);

  if (IsDuelOver() == TRUE || !CanActivateANCIENT_GEAR_EXPLOSIVE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidExplosiveTarget, ResolveExplosiveTarget, CancelExplosiveTargeting,
                     AiPickExplosiveTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectANCIENT_GEAR_EXPLOSIVE(void)
{
  if (!CanActivateANCIENT_GEAR_EXPLOSIVE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_EXPLOSIVE, ANCIENT_GEAR_EXPLOSIVE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_EXPLOSIVE_SelfCheck(void)
{
  if (!IsAncientGearMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (IsAncientGearMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
