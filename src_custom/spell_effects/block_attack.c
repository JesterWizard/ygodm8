#include "global.h"
#include "common-chax.h"
#include "block_attack.h"
#include "constants/card_ids.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);
void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void ResetCardEffectTextData(void);
void SetCardEffectTextType(u8);
void ActivateCardEffectText(void);

static u8 IsValidBlockAttackTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return zone->isDefending == FALSE;
}

static u8 FindFirstBlockAttackTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidBlockAttackTargetZone(OPPONENT_MONSTER_ROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 IsBlockAttackCard(u16 cardId)
{
  return cardId == BLOCK_ATTACK;
}

u8 FieldHasBlockAttackTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstBlockAttackTarget(&col);
}

void BeginBlockAttackTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstBlockAttackTarget(&targetCol))
    return;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(1);
    gCardEffectTextData.cardId = BLOCK_ATTACK;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_BLOCK_ATTACK_TARGET;
  gDuelCursor.currentY = OPPONENT_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
}

void TrySelectBlockAttackTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidBlockAttackTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = BLOCK_ATTACK;
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

void CancelBlockAttackTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectBlockAttack(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!IsValidBlockAttackTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = spellZone->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    target->isDefending = TRUE;
    target->isFaceUp = TRUE;
    ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  } else {
    ActivateTrapEffect(0);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
