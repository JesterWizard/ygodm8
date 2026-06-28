#include "global.h"
#include "common-chax.h"
#include "book_of_taiyou.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void FlipCardFaceUp(struct DuelCard *zone);


static u8 IsFaceDownMonsterTarget(struct DuelCard *zone)
{
  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp(zone) == FALSE;
}

static u8 IsValidBookOfTaiyouTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsFaceDownMonsterTarget(zone);
}

static u8 FindFirstBookOfTaiyouTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidBookOfTaiyouTargetZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void SetMonsterFaceUpAttack(struct DuelCard *zone)
{
  zone->isDefending = FALSE;
  FlipCardFaceUp(zone);
}

u8 IsBookOfTaiyouCard(u16 cardId)
{
  return cardId == BOOK_OF_TAIYOU;
}

u8 FieldHasBookOfTaiyouTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstBookOfTaiyouTarget(&row, &col);
}

void BeginBookOfTaiyouTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstBookOfTaiyouTarget(&targetRow, &targetCol))
    return;

  Duel_ShowEffectTextTyped(BOOK_OF_TAIYOU, 1);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_BOOK_OF_TAIYOU_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectBookOfTaiyouTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidBookOfTaiyouTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = BOOK_OF_TAIYOU;
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

void CancelBookOfTaiyouTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

static void BookOfTaiyou_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  SetMonsterFaceUpAttack(target);
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectBookOfTaiyou(void)
{
  if (!IsValidBookOfTaiyouTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(BOOK_OF_TAIYOU, BookOfTaiyou_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BookOfTaiyou_SelfCheck(void)
{
  struct DuelCard zone = {0};

  zone.id = BATTLE_FOOTBALLER;
  zone.isDefending = TRUE;
  zone.isFaceUp = FALSE;
  SetMonsterFaceUpAttack(&zone);
  if (zone.isFaceUp != TRUE || zone.isDefending != FALSE)
    while (1);
}
#endif
