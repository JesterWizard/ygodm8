#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

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

static u16 GetOriginalAtk(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.atk;
}

static u8 IsValidInfernoFireBlastTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (zone->id != RED_EYES_B_DRAGON)
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasInfernoFireBlastTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidInfernoFireBlastTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateINFERNO_FIRE_BLAST(void)
{
  return HasInfernoFireBlastTarget();
}

static void DestroyInfernoFireBlastSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == INFERNO_FIRE_BLAST)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveInfernoFireBlastTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u16 burn;

  if (!IsValidInfernoFireBlastTarget(fixedRow, fixedCol))
    return;

  burn = GetOriginalAtk(zone->id);

  zone->isLocked = TRUE;

  if (burn > 0 && Duel_ChangeLp(INACTIVE_DUELIST, -(s32)burn, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  DestroyInfernoFireBlastSpellZone();
}

static void CancelInfernoFireBlastTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyInfernoFireBlastSpellZone();
}

static u8 AiPickInfernoFireBlastTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidInfernoFireBlastTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void INFERNO_FIRE_BLAST_ResolveBody(void)
{
  Duel_ShowEffectText(INFERNO_FIRE_BLAST);

  if (IsDuelOver() == TRUE || !CanActivateINFERNO_FIRE_BLAST())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidInfernoFireBlastTarget, ResolveInfernoFireBlastTarget,
                     CancelInfernoFireBlastTargeting, AiPickInfernoFireBlastTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectINFERNO_FIRE_BLAST(void)
{
  if (!CanActivateINFERNO_FIRE_BLAST()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(INFERNO_FIRE_BLAST, INFERNO_FIRE_BLAST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void InfernoFireBlast_SelfCheck(void)
{
  if (GetOriginalAtk(RED_EYES_B_DRAGON) != 2400)
    while (1)
      ;
}
#endif
