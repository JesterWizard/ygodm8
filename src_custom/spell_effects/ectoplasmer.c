#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "ectoplasmer.h"
#include "imperial_order.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);

static u8 IsActivatedEctoplasmerZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == ECTOPLASMER && zone->isFaceUp == TRUE;
}

static u16 GetOriginalAtk(const struct DuelCard *zone)
{
  SetCardInfo(zone->id);
  return gCardInfo.atk;
}

static u8 IsValidEctoplasmerTributeMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp((struct DuelCard *)zone) == TRUE;
}

static u8 FindFirstEctoplasmerTributeTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidEctoplasmerTributeMonster(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 FindEctoplasmerSpellOrigin(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsActivatedEctoplasmerZone(gFixedZones[row][col]))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 FindAiEctoplasmerTributeCol(u8 *outCol)
{
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (!IsValidEctoplasmerTributeMonster(zone))
      continue;

    atk = GetOriginalAtk(zone);
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outCol = col;
    }
  }

  return found;
}

static void ApplyEctoplasmerDamage(u16 originalAtk)
{
  u16 damage = originalAtk / 2;

  if (damage == 0)
    return;

  Duel_ChangeLp(INACTIVE_DUELIST, -(s32)damage, TRUE);
}

static void ResolveEctoplasmerTribute(struct DuelCard *zone)
{
  u16 originalAtk;

  if (!IsValidEctoplasmerTributeMonster(zone))
    return;

  originalAtk = GetOriginalAtk(zone);

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  ApplyEctoplasmerDamage(originalAtk);
}

u8 IsEctoplasmerActiveOnField(void)
{
  u8 row;
  u8 col;

  if (IsImperialOrderNegatingSpell(ECTOPLASMER))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsActivatedEctoplasmerZone(gFixedZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

static void BeginEctoplasmerTargeting(void)
{
  u8 tributeCol;
  u8 originRow;
  u8 originCol;

  if (!FindFirstEctoplasmerTributeTarget(&tributeCol))
    return;

  if (!FindEctoplasmerSpellOrigin(&originRow, &originCol))
    return;

  Duel_ShowEffectTextTyped(ECTOPLASMER, 9);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;
  gDuelCursor.state = DUEL_CURSOR_ECTOPLASMER_TARGET;
  gDuelCursor.currentY = PLAYER_MONSTER_ROW;
  gDuelCursor.currentX = tributeCol;
  DisplayCardInfoBar();
  sub_8041E70(originRow, PLAYER_MONSTER_ROW);
}

static void ResolveEctoplasmerEffectForAi(void)
{
  u8 tributeCol;

  if (!FindAiEctoplasmerTributeCol(&tributeCol))
    return;

  ResolveEctoplasmerTribute(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][tributeCol]);
}

static u8 TurnPlayerHasEctoplasmerTributeTarget(void)
{
  u8 col;

  return FindFirstEctoplasmerTributeTarget(&col);
}

void TryApplyEctoplasmerEndPhaseEffect(void)
{
  if (!IsEctoplasmerActiveOnField() || IsDuelOver() == TRUE)
    return;

  if (!TurnPlayerHasEctoplasmerTributeTarget())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginEctoplasmerTargeting();
    return;
  }

  Duel_ShowEffectTextTyped(ECTOPLASMER, 9);

  if (IsDuelOver() == TRUE)
    return;

  ResolveEctoplasmerEffectForAi();
}

void TrySelectEctoplasmerTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  struct DuelCard *zone;

  if (targetRow != PLAYER_MONSTER_ROW) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  zone = gFixedZones[targetRow][targetCol];
  if (!IsValidEctoplasmerTributeMonster(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ResolveEctoplasmerTribute(zone);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();

  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

APPEND_TEXT void EffectEctoplasmer(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(ECTOPLASMER);
}
