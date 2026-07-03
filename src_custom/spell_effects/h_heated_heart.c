#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "h_heated_heart.h"
#include "mini_card.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);

static u8 ActiveDuelistMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsFaceUpMonsterTarget(struct DuelCard *zone)
{
  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidHHeatedHeartTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveDuelistMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsFaceUpMonsterTarget(zone);
}

static u8 FindFirstHHeatedHeartTarget(u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidHHeatedHeartTargetZone(monsterRow, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

void ApplyHeatedHeartAtkBonusToCardInfo(const struct DuelCard *zone)
{
  u32 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!DynamicEquipTargetsMonsterWithSpell(zone, H_HEATED_HEART))
    return;

  atk = (u32)gCardInfo.atk + (u32)HEATED_HEART_ATK_BOOST;
  gCardInfo.atk = Duel_ClampStat(atk);
}

u8 MonsterHasHeatedHeartPiercing(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow >= 4 || fixedCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return DynamicEquipTargetsMonsterWithSpell(zone, H_HEATED_HEART);
}

u8 IsHHeatedHeartCard(u16 cardId)
{
  return cardId == H_HEATED_HEART;
}

u8 FieldHasHHeatedHeartTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstHHeatedHeartTarget(&col);
}

void BeginHHeatedHeartTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  if (!FindFirstHHeatedHeartTarget(&targetCol))
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_H_HEATED_HEART_TARGET;
  gDuelCursor.currentY = monsterRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectHHeatedHeartTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidHHeatedHeartTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = H_HEATED_HEART;
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

void CancelHHeatedHeartTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

static void HHeatedHeart_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!RegisterDynamicEquip(spellZone, target, H_HEATED_HEART, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  RefreshFieldMonsterStatOverlays();
  Duel_ShowEffectText(H_HEATED_HEART);
}

APPEND_TEXT void EffectHHeatedHeart(void)
{
  if (!IsValidHHeatedHeartTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(H_HEATED_HEART, HHeatedHeart_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HHeatedHeart_SelfCheck(void)
{
  if (HEATED_HEART_ATK_BOOST != 500)
    while (1)
      ;
}
#endif
