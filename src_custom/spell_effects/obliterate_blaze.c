#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sExodiaName[] APPEND_RODATA = "Exodia";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsExodiaNamedLv10Plus(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sExodiaName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 10;
}

static u8 IsValidObliterateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow() && fixedRow != (ActiveMonsterFixedRow() ^ 1))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsExodiaNamedLv10Plus(zone->id);
}

static u8 HasObliterateTarget(void)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    if (!Duel_IsFixedMonsterRow(row))
      continue;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidObliterateTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ObliterateOnTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL)
    return;

  /* Mark granted effects via unk4 bit — secondary pay-half / equip / pierce
   * need hooks. */
  zone->unk4 = 1;
}

static u8 ObliterateAiPick(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    if (!Duel_IsFixedMonsterRow(row))
      continue;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidObliterateTarget(row, col))
        continue;
      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ObliteratePlayerResolve(u8 fixedRow, u8 fixedCol)
{
  ObliterateOnTarget(fixedRow, fixedCol);
  Duel_ClearPickZone();
  UpdateDuelGfxExceptField();
}

static void ObliteratePlayerCancel(void)
{
  Duel_ClearPickZone();
}

static u8 ObliteratePlayerValidate(u8 fixedRow, u8 fixedCol)
{
  return IsValidObliterateTarget(fixedRow, fixedCol);
}

static void OBLITERATE_BLAZE_ResolveBody(void)
{
  if (!HasObliterateTarget()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(OBLITERATE_BLAZE);
  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  Duel_SetupPickZone(ObliteratePlayerValidate, ObliteratePlayerResolve,
                     ObliteratePlayerCancel, ObliterateAiPick);
  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  /* ponytail: granted effects (pay half LP → destroy S/T + equip 5 Forbidden One
   * as +2000 Equip; piercing) need activated monster hooks / equip system outside
   * this file. Ceiling: marks target unk4=1 only; upgrade: copy Obliterate effects
   * onto marked Exodia monster. */
}

APPEND_TEXT void EffectOBLITERATE_BLAZE(void)
{
  if (Duel_TryResolveSpellThroughTraps(OBLITERATE_BLAZE, OBLITERATE_BLAZE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
