#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static struct DuelCard *sLevelTuningTarget APPEND_DATA = NULL;
static u16 sLevelTuningTargetId APPEND_DATA = CARD_NONE;

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

u8 LevelTuning_CanTarget(const struct DuelCard *zone)
{
  return MonsterIsFaceUp((struct DuelCard *)zone);
}

void LevelTuning_ApplyToTarget(struct DuelCard *zone)
{
  if (!LevelTuning_CanTarget(zone))
    return;

  sLevelTuningTarget = zone;
  sLevelTuningTargetId = zone->id;
}

void LevelTuning_ApplyLevelToCardInfo(const struct DuelCard *zone)
{
  if (zone != sLevelTuningTarget || zone == NULL || zone->id != sLevelTuningTargetId)
    return;

  if (gCardInfo.level > 1)
    gCardInfo.level--;
}

void LevelTuning_ClearAtTurnBoundary(void)
{
  sLevelTuningTarget = NULL;
  sLevelTuningTargetId = CARD_NONE;
}

static u8 HasFaceUpMonster(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (LevelTuning_CanTarget(gFixedZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateLEVEL_TUNING(void)
{
  return HasFaceUpMonster();
}

static void DestroyLevelTuningSpell(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == LEVEL_TUNING)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 IsValidLevelTuningTarget(u8 fixedRow, u8 fixedCol)
{
  return fixedRow >= OPPONENT_MONSTER_ROW && fixedRow <= PLAYER_MONSTER_ROW
      && fixedCol < MAX_ZONES_IN_ROW
      && LevelTuning_CanTarget(gFixedZones[fixedRow][fixedCol]);
}

static void ResolveLevelTuningTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidLevelTuningTarget(fixedRow, fixedCol))
    return;

  LevelTuning_ApplyToTarget(gFixedZones[fixedRow][fixedCol]);
  DestroyLevelTuningSpell();
}

static void CancelLevelTuningTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyLevelTuningSpell();
}

static u8 AiPickLevelTuningTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 activeRow = Duel_FixedMonsterRowForDuelist(WhoseTurn());

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    if (row == activeRow)
      continue;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidLevelTuningTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidLevelTuningTarget(activeRow, col)) {
      *outRow = activeRow;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void LEVEL_TUNING_ResolveBody(void)
{
  Duel_ShowEffectText(LEVEL_TUNING);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  Duel_SetupPickZone(IsValidLevelTuningTarget, ResolveLevelTuningTarget,
                     CancelLevelTuningTargeting, AiPickLevelTuningTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectLEVEL_TUNING(void)
{
  if (!CanActivateLEVEL_TUNING()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(LEVEL_TUNING, LEVEL_TUNING_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
