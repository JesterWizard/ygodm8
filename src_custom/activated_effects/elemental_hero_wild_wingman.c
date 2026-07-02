#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_wild_wingman.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 GraveyardDuelistForBackrowFixedRow(u8 fixedRow)
{
  u8 turn = WhoseTurn();

  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return turn == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return turn == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 FindFirstTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 DiscardCostCard(void)
{
  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  return IsDuelOver() != TRUE;
}

static void DestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_DestroyZone(zone, GraveyardDuelistForBackrowFixedRow(fixedRow), TRUE);
  NotifyDynamicEquipFieldChanged();
}

static void ResolveEffectForAi(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  (void)originFixedCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(ELEMENTAL_HERO_WILD_WINGMAN, targetRow, targetCol))
    return;

  DestroyTarget(targetRow, targetCol);
}

static void BeginDestroyTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_ELEMENTAL_HERO_WILD_WINGMAN_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(PLAYER_HAND, targetRow);
}

unsigned char CanActivateElementalHeroWildWingman(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != ELEMENTAL_HERO_WILD_WINGMAN)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return FindFirstTarget(&unusedRow, &unusedCol);
}

void TrySelectElementalHeroWildWingmanTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyTarget(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelElementalHeroWildWingmanTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void ActivateElementalHeroWildWingmanEffect(void)
{
  u8 originRow = gMonEffect.row;
  u8 originCol = gMonEffect.zone;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_WILD_WINGMAN, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (!DiscardCostCard())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginDestroyTargeting(originRow, originCol);
    return;
  }

  ResolveEffectForAi(originRow, originCol);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroWildWingman_SelfCheck(void)
{
  u8 row = OPPONENT_BACKROW;
  u8 col = 0;

  if (IsSpellOrTrapCard(POLYMERIZATION) == FALSE)
    while (1)
      ;
  if (IsSpellOrTrapCard(MIRROR_FORCE) == FALSE)
    while (1)
      ;
  if (IsValidTarget(PLAYER_MONSTER_ROW, col))
    while (1)
      ;
  (void)row;
}
#endif
