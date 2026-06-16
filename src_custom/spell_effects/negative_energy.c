#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "negative_energy.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);

#define NEGATIVE_ENERGY_MAX_LEVEL 3
#define NEGATIVE_ENERGY_STAGE_BOOST 2

static u8 ActiveDuelistMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 MonsterQualifiesForNegativeEnergy(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.level > NEGATIVE_ENERGY_MAX_LEVEL)
    return FALSE;

  return gCardInfo.attribute == ATTRIBUTE_SHADOW
      || gCardInfo.attribute == ATTRIBUTE_FIEND;
}

static u8 IsValidNegativeEnergyTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveDuelistMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return MonsterQualifiesForNegativeEnergy(zone->id);
}

static u8 FindFirstNegativeEnergyTarget(u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidNegativeEnergyTargetZone(monsterRow, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void BoostMonsterStages(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < NEGATIVE_ENERGY_STAGE_BOOST; i++)
    IncrementPermStage(zone);
}

u8 IsNegativeEnergyCard(u16 cardId)
{
  return cardId == NEGATIVE_ENERGY;
}

u8 FieldHasNegativeEnergyTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstNegativeEnergyTarget(&col);
}

void BeginNegativeEnergyTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  if (!FindFirstNegativeEnergyTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(NEGATIVE_ENERGY, 1);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_NEGATIVE_ENERGY_TARGET;
  gDuelCursor.currentY = monsterRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectNegativeEnergyTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidNegativeEnergyTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = NEGATIVE_ENERGY;
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

void CancelNegativeEnergyTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectNegativeEnergy(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!IsValidNegativeEnergyTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2], ACTIVE_DUELIST, FALSE);
  BoostMonsterStages(target);
  RefreshFieldMonsterStatOverlays();
}
