#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* 1 stage ~= 500 ATK. Printed +400; nearest temp-stage unit is +500 until EOT. */
#define FORBIDDEN_CHALICE_ATK_STAGES 1

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

static u8 IsValidForbiddenChaliceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasForbiddenChaliceTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidForbiddenChaliceTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateFORBIDDEN_CHALICE(void)
{
  return HasForbiddenChaliceTarget();
}

static void DestroyForbiddenChaliceSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == FORBIDDEN_CHALICE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ApplyForbiddenChaliceBoost(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < FORBIDDEN_CHALICE_ATK_STAGES; i++)
    IncrementTempStage(zone);

  /* ponytail: stage unit is 500 ATK — applied +500 until EOT, not printed +400.
   * Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART. */

  /* ponytail: no per-monster effect-negate flag until EOT (Skill Drain is field-wide
   * only). Ceiling: ATK boost only; upgrade: turn_effect / zone negate bit cleared
   * at ResetTempStagesForFieldCards. */

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveForbiddenChaliceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidForbiddenChaliceTarget(fixedRow, fixedCol))
    return;

  ApplyForbiddenChaliceBoost(zone);
  DestroyForbiddenChaliceSpellZone();
}

static void CancelForbiddenChaliceTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyForbiddenChaliceSpellZone();
}

static u8 AiPickForbiddenChaliceTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidForbiddenChaliceTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void FORBIDDEN_CHALICE_ResolveBody(void)
{
  Duel_ShowEffectText(FORBIDDEN_CHALICE);

  if (IsDuelOver() == TRUE || !HasForbiddenChaliceTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidForbiddenChaliceTarget, ResolveForbiddenChaliceTarget,
                     CancelForbiddenChaliceTargeting, AiPickForbiddenChaliceTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectFORBIDDEN_CHALICE(void)
{
  if (!CanActivateFORBIDDEN_CHALICE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FORBIDDEN_CHALICE, FORBIDDEN_CHALICE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ForbiddenChalice_SelfCheck(void)
{
  if (FORBIDDEN_CHALICE_ATK_STAGES != 1)
    while (1)
      ;
}
#endif
