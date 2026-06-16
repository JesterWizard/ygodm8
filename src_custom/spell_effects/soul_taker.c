#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "soul_taker.h"
#include "spell_effects.h"

#define SOUL_TAKER_LP 1000

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);

static u8 IsValidSoulTakerTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FindFirstSoulTakerTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidSoulTakerTargetZone(OPPONENT_MONSTER_ROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 IsSoulTakerCard(u16 cardId)
{
  return cardId == SOUL_TAKER;
}

u8 FieldHasSoulTakerTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstSoulTakerTarget(&col);
}

void BeginSoulTakerTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstSoulTakerTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(SOUL_TAKER, 1);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_SOUL_TAKER_TARGET;
  gDuelCursor.currentY = OPPONENT_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
}

void TrySelectSoulTakerTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidSoulTakerTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = SOUL_TAKER;
  gSpellEffectData.row1 = targetRow;
  gSpellEffectData.col1 = targetCol;
  gSpellEffectData.row2 = originRow;
  gSpellEffectData.col2 = originCol;
  ActivateSpellEffect();
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}

void CancelSoulTakerTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

static void SoulTaker_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  Duel_DestroyZone(target, INACTIVE_DUELIST, FALSE);

  if (Duel_ChangeLp(ACTIVE_DUELIST, SOUL_TAKER_LP, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectSoulTaker(void)
{
  if (!IsValidSoulTakerTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SOUL_TAKER, SoulTaker_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
