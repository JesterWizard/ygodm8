#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define MOLTING_ESCAPE_EXACT_ATK_BONUS 300
#define MOLTING_ESCAPE_BOARD_CELLS 20

static u8 sMoltingEscapeBoostCells[MOLTING_ESCAPE_BOARD_CELLS] APPEND_DATA = {0};

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MOLTING_ESCAPE_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

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

static struct DuelCard *FindMoltingEscapeSpellForTarget(const struct DuelCard *target)
{
  u8 i;
  u8 targetRow;
  u8 targetCol;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)target, &targetRow, &targetCol))
    return NULL;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;

    if (!link->active || link->spellId != MOLTING_ESCAPE
        || link->targetFixedRow != targetRow || link->targetFixedCol != targetCol)
      continue;

    spellZone = gFixedZones[link->spellFixedRow][link->spellFixedCol];
    if (IsActiveDynamicEquipSpellZone(spellZone))
      return spellZone;
  }

  return NULL;
}

u8 MoltingEscape_PreventsBattleDestruction(const struct DuelCard *target)
{
  struct DuelCard *spellZone = FindMoltingEscapeSpellForTarget(target);

  return spellZone != NULL && spellZone->effectUsedThisTurn == FALSE;
}

void MoltingEscape_ApplyBattleProtection(struct DuelCard *target)
{
  struct DuelCard *spellZone = FindMoltingEscapeSpellForTarget(target);

  if (spellZone == NULL || spellZone->effectUsedThisTurn)
    return;

  spellZone->effectUsedThisTurn = TRUE;
  {
    u16 cell = GetDuelBoardCellIndex(target);

    if (cell < MOLTING_ESCAPE_BOARD_CELLS)
      sMoltingEscapeBoostCells[cell] = TRUE;
  }
  Duel_RefreshMonsterStatOverlays();
}

void ApplyMoltingEscapeAtkBonusToCardInfo(const struct DuelCard *zone)
{
  u16 cell;
  u32 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  cell = GetDuelBoardCellIndex(zone);
  if (cell >= MOLTING_ESCAPE_BOARD_CELLS || !sMoltingEscapeBoostCells[cell])
    return;

  atk = (u32)gCardInfo.atk + MOLTING_ESCAPE_EXACT_ATK_BONUS;
  gCardInfo.atk = Duel_ClampStat(atk);
}

static void EquipMoltingEscape(struct DuelCard *spellZone, struct DuelCard *target)
{
  /* No ATK on equip — printed +300 applies only when OPT battle-protect fires. */
  if (!RegisterDynamicEquip(spellZone, target, MOLTING_ESCAPE, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
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
