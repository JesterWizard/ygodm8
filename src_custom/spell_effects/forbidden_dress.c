#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "riryoku.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define FORBIDDEN_DRESS_ATK_LOSS 600

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 sForbiddenDressProtection[MAX_DUEL_BOARD_CELLS] APPEND_DATA = {0};

static u16 GetForbiddenDressProtectionIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MAX_DUEL_BOARD_CELLS)
    return MAX_DUEL_BOARD_CELLS;

  return (u16)(zone - base);
}

static void MarkForbiddenDressProtection(const struct DuelCard *zone)
{
  u16 index = GetForbiddenDressProtectionIndex(zone);

  if (index < MAX_DUEL_BOARD_CELLS)
    sForbiddenDressProtection[index] = TRUE;
}

u8 ForbiddenDress_IsTargetImmune(const struct DuelCard *zone)
{
  u16 index = GetForbiddenDressProtectionIndex(zone);

  return index < MAX_DUEL_BOARD_CELLS && sForbiddenDressProtection[index];
}

u8 ForbiddenDress_IsDestroyImmune(const struct DuelCard *zone)
{
  return ForbiddenDress_IsTargetImmune(zone);
}

void ForbiddenDress_ClearOnTurnBoundary(void)
{
  u8 i;

  for (i = 0; i < MAX_DUEL_BOARD_CELLS; i++)
    sForbiddenDressProtection[i] = FALSE;
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

static u8 IsValidForbiddenDressTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasForbiddenDressTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidForbiddenDressTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateFORBIDDEN_DRESS(void)
{
  return HasForbiddenDressTarget();
}

static void DestroyForbiddenDressSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == FORBIDDEN_DRESS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ApplyForbiddenDressAtkLoss(struct DuelCard *zone)
{
  AddRiryokuAtkDelta(zone, -FORBIDDEN_DRESS_ATK_LOSS);
  MarkForbiddenDressProtection(zone);

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveForbiddenDressTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidForbiddenDressTarget(fixedRow, fixedCol))
    return;

  ApplyForbiddenDressAtkLoss(zone);
  DestroyForbiddenDressSpellZone();
}

static void CancelForbiddenDressTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyForbiddenDressSpellZone();
}

static u8 AiPickForbiddenDressTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidForbiddenDressTarget(row, col))
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

static void FORBIDDEN_DRESS_ResolveBody(void)
{
  Duel_ShowEffectText(FORBIDDEN_DRESS);

  if (IsDuelOver() == TRUE || !HasForbiddenDressTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidForbiddenDressTarget, ResolveForbiddenDressTarget,
                     CancelForbiddenDressTargeting, AiPickForbiddenDressTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectFORBIDDEN_DRESS(void)
{
  if (!CanActivateFORBIDDEN_DRESS()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FORBIDDEN_DRESS, FORBIDDEN_DRESS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ForbiddenDress_SelfCheck(void)
{
  if (FORBIDDEN_DRESS_ATK_LOSS != 600)
    while (1)
      ;
}
#endif
