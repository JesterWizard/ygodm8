#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "diffusion_wave_motion.h"
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
void SetAttackAction(s32, s32);
void HandleAtkAndLifePointsAction(void);
void CheckGraveyardAndLoserFlags(void);

#define DIFFUSION_WAVE_MOTION_LP_COST 1000
#define DIFFUSION_WAVE_MOTION_MIN_LEVEL 7

static u8 ActiveDuelistMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 ActiveDuelistHasLpForCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= DIFFUSION_WAVE_MOTION_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= DIFFUSION_WAVE_MOTION_LP_COST;
}

static u8 InactiveDuelistHasMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 MonsterQualifiesForDiffusionWaveMotion(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.level < DIFFUSION_WAVE_MOTION_MIN_LEVEL)
    return FALSE;

  return gCardInfo.type == TYPE_SPELLCASTER;
}

static u8 IsValidDiffusionWaveMotionTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveDuelistMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterQualifiesForDiffusionWaveMotion(zone->id);
}

static u8 FindFirstDiffusionWaveMotionTarget(u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidDiffusionWaveMotionTargetZone(monsterRow, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 FindAiDiffusionWaveMotionTarget(u8 *outCol)
{
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (!MonsterQualifiesForDiffusionWaveMotion(zone->id))
      continue;

    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outCol = col;
    }
  }

  return found;
}

static u8 TurnColForZone(struct DuelCard *zone, u8 turnRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[turnRow][col] == zone)
      return col;
  }

  return 0;
}

static void AttackAllOpponentMonstersLikeBerserkDragon(struct DuelCard *attacker)
{
  u8 i;
  u8 turn = WhoseTurn();
  u8 attackerTurnRow = ACTIVE_DUELIST_MONSTER_ROW;
  u8 attackerTurnCol = TurnColForZone(attacker, attackerTurnRow);

  attacker->isDefending = FALSE;
  FlipCardFaceUp(attacker);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDuelOver() == TRUE || gTurnZones[attackerTurnRow][attackerTurnCol]->id == CARD_NONE)
      break;

    if (gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE) {
      FlipCardFaceUp(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]);
      if (turn == DUEL_PLAYER)
        SetAttackAction(attackerTurnCol, 4 - i);
      else
        SetAttackAction(i, 4 - attackerTurnCol);

      HandleAtkAndLifePointsAction();
      CheckGraveyardAndLoserFlags();
      if (turn != DUEL_PLAYER)
        gUnk2023EA0.unk18 = 0;
    }
  }
}

static void QueueDiffusionWaveMotionActivation(u8 targetRow, u8 targetCol, u8 originRow, u8 originCol)
{
  gSpellEffectData.id = DIFFUSION_WAVE_MOTION;
  gSpellEffectData.row1 = targetRow;
  gSpellEffectData.col1 = targetCol;
  gSpellEffectData.row2 = originRow;
  gSpellEffectData.col2 = originCol;
  ActivateSpellEffect();
}

u8 IsDiffusionWaveMotionCard(u16 cardId)
{
  return cardId == DIFFUSION_WAVE_MOTION;
}

u8 FieldHasDiffusionWaveMotionTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;

  if (!InactiveDuelistHasMonster())
    return FALSE;

  if (!ActiveDuelistHasLpForCost())
    return FALSE;

  return FindFirstDiffusionWaveMotionTarget(&col);
}

void BeginDiffusionWaveMotionTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;
  u8 monsterRow = ActiveDuelistMonsterFixedRow();

  if (WhoseTurn() != DUEL_PLAYER) {
    if (!FindAiDiffusionWaveMotionTarget(&targetCol))
      return;

    QueueDiffusionWaveMotionActivation(monsterRow, targetCol, originFixedRow, originFixedCol);
    return;
  }

  if (!FindFirstDiffusionWaveMotionTarget(&targetCol))
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_DIFFUSION_WAVE_MOTION_TARGET;
  gDuelCursor.currentY = monsterRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectDiffusionWaveMotionTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidDiffusionWaveMotionTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  QueueDiffusionWaveMotionActivation(targetRow, targetCol, originRow, originCol);
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}

void CancelDiffusionWaveMotionTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

static void LockActiveDuelistMonsters(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id != CARD_NONE)
      zone->isLocked = TRUE;
  }
}

static void DiffusionWaveMotion_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!InactiveDuelistHasMonster() || !ActiveDuelistHasLpForCost())
    return;

  Duel_ShowEffectText(DIFFUSION_WAVE_MOTION);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -DIFFUSION_WAVE_MOTION_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  AttackAllOpponentMonstersLikeBerserkDragon(target);
  LockActiveDuelistMonsters();
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDiffusionWaveMotion(void)
{
  if (!IsValidDiffusionWaveMotionTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(DIFFUSION_WAVE_MOTION, DIFFUSION_WAVE_MOTION_LP_COST,
                                         DiffusionWaveMotion_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DiffusionWaveMotion_SelfCheck(void)
{
  if (DIFFUSION_WAVE_MOTION_MIN_LEVEL != 7)
    while (1);
}
#endif
