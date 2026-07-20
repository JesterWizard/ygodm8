#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* Own tribute stashed in gSpellEffectData.row2/col2 (spell stays in row1/col1). */

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 InactiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsValidOwnTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 IsValidOpponentTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != InactiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasOwnTribute(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOwnTributeZone(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 HasOpponentTribute(void)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOpponentTributeZone(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateSHARE_THE_PAIN(void)
{
  return HasOwnTribute() && HasOpponentTribute();
}

static void DestroyShareThePainSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == SHARE_THE_PAIN)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void TributeMonsterAt(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  PlayMusic(SFX_TRIBUTE);
  Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(fixedRow), FALSE);
}

static void FinishShareThePain(u8 oppRow, u8 oppCol)
{
  TributeMonsterAt(gSpellEffectData.row2, gSpellEffectData.col2);
  if (IsDuelOver() == TRUE)
    return;

  TributeMonsterAt(oppRow, oppCol);
  if (IsDuelOver() == TRUE)
    return;

  DestroyShareThePainSpellZone();
}

static void CancelShareThePainTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyShareThePainSpellZone();
}

static u8 AiPickOpponentTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();
  u16 bestAtk = 0xFFFF;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidOpponentTributeZone(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveOpponentTributeTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidOpponentTributeZone(fixedRow, fixedCol))
    return;

  FinishShareThePain(fixedRow, fixedCol);
}

static void BeginOpponentTributePick(void)
{
  Duel_SetupPickZone(IsValidOpponentTributeZone, ResolveOpponentTributeTarget,
                     CancelShareThePainTargeting, AiPickOpponentTribute);
  Duel_EnterPickZoneTargeting();
}

static u8 AiPickOwnTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u16 bestAtk = 0xFFFF;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidOwnTributeZone(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveOwnTributeTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidOwnTributeZone(fixedRow, fixedCol))
    return;

  gSpellEffectData.row2 = fixedRow;
  gSpellEffectData.col2 = fixedCol;

  if (!HasOpponentTribute()) {
    DestroyShareThePainSpellZone();
    return;
  }

  BeginOpponentTributePick();
}

static void ResolveShareThePainForAi(void)
{
  u8 ownRow;
  u8 ownCol;
  u8 oppRow;
  u8 oppCol;

  if (!AiPickOwnTribute(&ownRow, &ownCol) || !AiPickOpponentTribute(&oppRow, &oppCol)) {
    DestroyShareThePainSpellZone();
    return;
  }

  gSpellEffectData.row2 = ownRow;
  gSpellEffectData.col2 = ownCol;
  FinishShareThePain(oppRow, oppCol);
}

static void SHARE_THE_PAIN_ResolveBody(void)
{
  Duel_ShowEffectText(SHARE_THE_PAIN);

  if (IsDuelOver() == TRUE || !CanActivateSHARE_THE_PAIN())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    ResolveShareThePainForAi();
    return;
  }

  Duel_SetupPickZone(IsValidOwnTributeZone, ResolveOwnTributeTarget,
                     CancelShareThePainTargeting, AiPickOwnTribute);
  Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectSHARE_THE_PAIN(void)
{
  if (!CanActivateSHARE_THE_PAIN()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SHARE_THE_PAIN, SHARE_THE_PAIN_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
