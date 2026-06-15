#include "global.h"
#include "common-chax.h"
#include "book_of_moon.h"
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

static u8 IsMonsterFixedRow(u8 fixedRow)
{
  return fixedRow == OPPONENT_MONSTER_ROW || fixedRow == PLAYER_MONSTER_ROW;
}

static u8 IsFaceUpMonsterTarget(struct DuelCard *zone)
{
  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position monsters stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsValidBookOfMoonTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!IsMonsterFixedRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return IsFaceUpMonsterTarget(zone);
}

static u8 FindFirstBookOfMoonTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidBookOfMoonTargetZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void SetMonsterFaceDownDefense(struct DuelCard *zone)
{
  zone->isDefending = TRUE;
  FlipCardFaceDown(zone);
}

u8 IsBookOfMoonCard(u16 cardId)
{
  return cardId == BOOK_OF_MOON;
}

u8 FieldHasBookOfMoonTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstBookOfMoonTarget(&row, &col);
}

void BeginBookOfMoonTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstBookOfMoonTarget(&targetRow, &targetCol))
    return;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(1);
    gCardEffectTextData.cardId = BOOK_OF_MOON;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_BOOK_OF_MOON_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectBookOfMoonTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidBookOfMoonTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = BOOK_OF_MOON;
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

void CancelBookOfMoonTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectBookOfMoon(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!IsValidBookOfMoonTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = spellZone->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    SetMonsterFaceDownDefense(target);
    ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  } else {
    ActivateTrapEffect(0);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BookOfMoon_SelfCheck(void)
{
  struct DuelCard zone = {0};

  zone.id = BATTLE_FOOTBALLER;
  zone.isDefending = FALSE;
  zone.isFaceUp = TRUE;
  SetMonsterFaceDownDefense(&zone);
  if (zone.isFaceUp != FALSE || zone.isDefending != TRUE)
    while (1);
}
#endif
