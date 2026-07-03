#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_core.h"
#include "god_card.h"

void UpdateDuelGfxExceptField(void);

struct ElementalHeroCoreActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct ElementalHeroCoreActionData sActionData;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

void ClearElementalHeroCoreBattledPending(void)
{
  gElementalHeroCoreBattledRow = ELEMENTAL_HERO_CORE_BATTLED_NONE;
  gElementalHeroCoreBattledCol = ELEMENTAL_HERO_CORE_BATTLED_NONE;
}

/* Origin Core (gDuelCursor.dest during pick, or explicit exclude) is not a target.
 * Monster rows hold monsters only — include face-down (set) cards. */
static u8 ZoneIsValidDestroyTargetEx(u8 fixedRow, u8 fixedCol, u8 excludeRow, u8 excludeCol)
{
  struct DuelCard *zone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  if (fixedRow == excludeRow && fixedCol == excludeCol)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 ZoneIsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  return ZoneIsValidDestroyTargetEx(fixedRow, fixedCol, gDuelCursor.destY, gDuelCursor.destX);
}

static u8 FindFirstDestroyTargetEx(u8 *outRow, u8 *outCol, u8 excludeRow, u8 excludeCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!ZoneIsValidDestroyTargetEx(row, col, excludeRow, excludeCol))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 FindFirstDestroyTarget(u8 *outRow, u8 *outCol)
{
  return FindFirstDestroyTargetEx(outRow, outCol, gDuelCursor.destY, gDuelCursor.destX);
}

static u16 DestroyTargetSortAtk(struct DuelCard *zone)
{
  /* Face-down set: avoid full stat pipeline; use printed ATK. */
  if (zone->isDefending && !zone->isFaceUp)
    return gCardData_NEW[zone->id].atk;

  return Duel_GetZoneFinalAtk(zone);
}

static u8 PickAiDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!ZoneIsValidDestroyTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = DestroyTargetSortAtk(zone);
      if (bestRow == 0xFF || atk > bestAtk) {
        bestRow = row;
        bestCol = col;
        bestAtk = atk;
      }
    }
  }

  if (bestRow != 0xFF) {
    *outRow = bestRow;
    *outCol = bestCol;
    return TRUE;
  }

  return FALSE;
}

/* ClearZoneAndSendMonToGraveyard wants ACTIVE/INACTIVE, not fixed player/opponent. */
static u8 GraveyardDuelistForMonsterFixedRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResolveDestroyTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (!ZoneIsValidDestroyTarget(targetRow, targetCol))
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForMonsterFixedRow(targetRow), TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;
}

static void CancelDestroyTargeting(void)
{
}

static u8 FindFirstOpponentDestroyTarget(u8 *outRow, u8 *outCol, u8 excludeRow,
                                         u8 excludeCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ZoneIsValidDestroyTargetEx(OPPONENT_MONSTER_ROW, col, excludeRow, excludeCol))
      continue;

    *outRow = OPPONENT_MONSTER_ROW;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void DestroyFirstAutoTarget(u8 originRow, u8 originCol)
{
  u8 targetRow;
  u8 targetCol;

  /* Prefer a monster on the opponent's field, then any other valid target. */
  if (!FindFirstOpponentDestroyTarget(&targetRow, &targetCol, originRow, originCol)
      && !FindFirstDestroyTargetEx(&targetRow, &targetCol, originRow, originCol))
    return;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;
  ResolveDestroyTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
}

static void BeginDestroyTargeting(u8 originRow, u8 originCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDestroyTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  Duel_SetupPickZone(ZoneIsValidDestroyTarget, ResolveDestroyTarget, CancelDestroyTargeting,
                     PickAiDestroyTarget);
  Duel_EnterPickZoneTargeting();
}

static u16 CoreOriginalAtkDoubled(void)
{
  return Duel_ClampStat((u32)gCardData_NEW[ELEMENTAL_HERO_CORE].atk * 2);
}

/* Once per turn, when Core battles: ATK becomes double original.
 * Silent/automatic during real battle only — AI sim must not see the boost. */
void TryApplyElementalHeroCoreAtkDouble(void)
{
  struct DuelCard *zone;
  u16 *atkField;

  /* ponytail: gHideEffectText marks AI attack simulation; keep printed ATK at base. */
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == ELEMENTAL_HERO_CORE) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    atkField = &sActionData.playerCardAtkOrLifePointsMod;
  } else if (sActionData.opponentCardId == ELEMENTAL_HERO_CORE) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    atkField = &sActionData.opponentCardAtkOrLifePointsMod;
  } else {
    return;
  }

  if (zone == NULL || zone->id != ELEMENTAL_HERO_CORE)
    return;

  if (zone->effectUsedThisTurn)
    return;

  zone->effectUsedThisTurn = TRUE;
  *atkField = CoreOriginalAtkDoubled();
}

void ResolveElementalHeroCoreBattledEffect(void)
{
  u8 originRow = gElementalHeroCoreBattledRow;
  u8 originCol = gElementalHeroCoreBattledCol;
  struct DuelCard *zone;
  u8 targetRow;
  u8 targetCol;
  u8 hideEffectText;

  if (originRow == ELEMENTAL_HERO_CORE_BATTLED_NONE
      || originCol == ELEMENTAL_HERO_CORE_BATTLED_NONE)
    return;

  /* Consume immediately so deferred resolve sites do not re-enter. */
  ClearElementalHeroCoreBattledPending();

  zone = gFixedZones[originRow][originCol];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_CORE)
    return;

  /* No other monsters on the field — do not activate. */
  if (!FindFirstDestroyTargetEx(&targetRow, &targetCol, originRow, originCol))
    return;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(ELEMENTAL_HERO_CORE, CARD_EFFECT_TEXT_ELEMENTAL_HERO_CORE_POPUP_1);
  gHideEffectText = hideEffectText;

  if (IsDuelOver() == TRUE)
    return;

  /* Opponent turn: auto-destroy (PickZone softlocks in AI_Main). */
  if (WhoseTurn() != DUEL_PLAYER) {
    DestroyFirstAutoTarget(originRow, originCol);
    return;
  }

  BeginDestroyTargeting(originRow, originCol);
}

void ApplyElementalHeroCoreBattleEffect(void)
{
  struct DuelCard *zone = NULL;
  u8 row = ELEMENTAL_HERO_CORE_BATTLED_NONE;
  u8 col = ELEMENTAL_HERO_CORE_BATTLED_NONE;

  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == ELEMENTAL_HERO_CORE) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    row = sActionData.playerMonsterRow;
    col = sActionData.unkA;
  } else if (sActionData.opponentCardId == ELEMENTAL_HERO_CORE) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    row = sActionData.opponentMonsterRow;
    col = sActionData.unk16;
  } else {
    return;
  }

  if (zone == NULL || zone->id != ELEMENTAL_HERO_CORE)
    return;

  {
    u8 targetRow;
    u8 targetCol;

    if (!FindFirstDestroyTargetEx(&targetRow, &targetCol, row, col))
      return;
  }

  gElementalHeroCoreBattledRow = row;
  gElementalHeroCoreBattledCol = col;

  /* Opponent-turn battles resolve from AiAttackMonster (not inline here) —
   * textboxes inside CheckGraveyardAndLoserFlags freeze the AI attack path. */
  if (WhoseTurn() != DUEL_PLAYER)
    return;

  if (gUnk2023EA0.unk18 == 0)
    ResolveElementalHeroCoreBattledEffect();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroCore_BattleSelfCheck(void)
{
  if (CoreOriginalAtkDoubled() != 5400)
    while (1)
      ;
}
#endif
