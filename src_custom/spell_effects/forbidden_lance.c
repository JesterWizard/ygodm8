#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "riryoku.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define FORBIDDEN_LANCE_ATK_LOSS 800

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 sForbiddenLanceSpellTrapImmunity[MAX_DUEL_BOARD_CELLS] APPEND_DATA = {0};

static u16 GetForbiddenLanceImmunityIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MAX_DUEL_BOARD_CELLS)
    return MAX_DUEL_BOARD_CELLS;

  return (u16)(zone - base);
}

static void MarkForbiddenLanceSpellTrapImmunity(const struct DuelCard *zone)
{
  u16 index = GetForbiddenLanceImmunityIndex(zone);

  if (index < MAX_DUEL_BOARD_CELLS)
    sForbiddenLanceSpellTrapImmunity[index] = TRUE;
}

u8 ForbiddenLance_IsImmuneToSpellTrapEffects(const struct DuelCard *zone)
{
  u16 index = GetForbiddenLanceImmunityIndex(zone);

  return index < MAX_DUEL_BOARD_CELLS && sForbiddenLanceSpellTrapImmunity[index];
}

void ForbiddenLance_ClearOnTurnBoundary(void)
{
  u8 i;

  for (i = 0; i < MAX_DUEL_BOARD_CELLS; i++)
    sForbiddenLanceSpellTrapImmunity[i] = FALSE;
}

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

static u8 IsValidForbiddenLanceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasForbiddenLanceTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidForbiddenLanceTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateFORBIDDEN_LANCE(void)
{
  return HasForbiddenLanceTarget();
}

static void DestroyForbiddenLanceSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == FORBIDDEN_LANCE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ApplyForbiddenLanceAtkLoss(struct DuelCard *zone)
{
  AddRiryokuAtkDelta(zone, -FORBIDDEN_LANCE_ATK_LOSS);
  MarkForbiddenLanceSpellTrapImmunity(zone);

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveForbiddenLanceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidForbiddenLanceTarget(fixedRow, fixedCol))
    return;

  ApplyForbiddenLanceAtkLoss(zone);
  DestroyForbiddenLanceSpellZone();
}

static void CancelForbiddenLanceTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyForbiddenLanceSpellZone();
}

static u8 AiPickForbiddenLanceTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidForbiddenLanceTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = Duel_GetZoneFinalAtk(zone);
      if (!found || atk > bestAtk) {
        found = TRUE;
        bestAtk = atk;
        *outRow = row;
        *outCol = col;
      }
    }
  }

  return found;
}

static void FORBIDDEN_LANCE_ResolveBody(void)
{
  Duel_ShowEffectText(FORBIDDEN_LANCE);

  if (IsDuelOver() == TRUE || !HasForbiddenLanceTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidForbiddenLanceTarget, ResolveForbiddenLanceTarget,
                     CancelForbiddenLanceTargeting, AiPickForbiddenLanceTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectFORBIDDEN_LANCE(void)
{
  if (!CanActivateFORBIDDEN_LANCE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FORBIDDEN_LANCE, FORBIDDEN_LANCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ForbiddenLance_SelfCheck(void)
{
  if (FORBIDDEN_LANCE_ATK_LOSS != 800)
    while (1)
      ;
}
#endif
