#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "graveyard_effects.h"
#include "the_wicked_eraser.h"
#include "mini_card.h"

void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void UpdateDuelGfxExceptField(void);

#define THE_WICKED_ERASER_STAT_PER_CARD 1000

void ClearTheWickedEraserPending(void)
{
  gTheWickedEraserFieldWipePending = FALSE;
  gTheWickedEraserFieldWipeTurnRow = 0xFF;
  gTheWickedEraserFieldWipeFromField = FALSE;
}

static u8 GraveyardScanRowForTurnDuelist(u8 turnDuelist)
{
  return (turnDuelist == ACTIVE_DUELIST) ? 6 : 7;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 OpponentFixedDuelistForZone(struct DuelCard *zone)
{
  u8 owner;

  owner = GetDuelistForZone(zone);
  if (owner == 0xFF)
    return 0xFF;

  return owner == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
}

static u8 CountCardsControlledByFixedDuelist(u8 fixedDuelist)
{
  u8 count = 0;
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  u8 monsterRow = fixedDuelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 backrow = fixedDuelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

  count += Duel_CountCardsInHand(gTurnHands[turnDuelist]);
  count += Duel_CountMonstersOnFixedRow(monsterRow);
  count += Duel_CountMonstersOnFixedRow(backrow);
  return count;
}

static u8 EraserIsActiveOnField(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col]->id == THE_WICKED_ERASER)
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroyAllFieldCards(void)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  for (row = 0; row < 4; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

u8 TheWickedEraser_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 opponent;
  u8 count;
  u16 stat;

  if (zone == NULL || zone->id != THE_WICKED_ERASER)
    return FALSE;

  opponent = OpponentFixedDuelistForZone(zone);
  if (opponent == 0xFF)
    return FALSE;

  count = CountCardsControlledByFixedDuelist(opponent);
  stat = Duel_StatFromCount(count, THE_WICKED_ERASER_STAT_PER_CARD, 0);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

void TryTheWickedEraserOnMonsterPlacement(struct DuelCard *zone)
{
  (void)zone;

  if (EraserIsActiveOnField())
    RefreshFieldMonsterStatOverlays();
}

void TheWickedEraser_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone != NULL && zone->id == THE_WICKED_ERASER)
    UpdateDuelGfxExceptField();

  TryTheWickedEraserOnMonsterPlacement(NULL);
}

void NoteTheWickedEraserGraveyardSend(struct DuelCard *zone)
{
  u8 turnDuelist;

  if (zone == NULL || zone->id != THE_WICKED_ERASER)
    return;

  if (!gGraveyardSendWasFromField)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(GetDuelistForZone(zone));
  gTheWickedEraserFieldWipeTurnRow = GraveyardScanRowForTurnDuelist(turnDuelist);
  gTheWickedEraserFieldWipePending = TRUE;
  gTheWickedEraserFieldWipeFromField = TRUE;
}

unsigned char ShouldActivateTheWickedEraser(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gTheWickedEraserFieldWipeFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (!gTheWickedEraserFieldWipePending)
    return FALSE;

  return gActiveEffect.turnRow == gTheWickedEraserFieldWipeTurnRow;
}

void ActivateTheWickedEraser(void)
{
  u8 hideEffectText;

  if (!gTheWickedEraserFieldWipePending)
    return;

  gTheWickedEraserFieldWipePending = FALSE;
  gTheWickedEraserFieldWipeTurnRow = 0xFF;
  gTheWickedEraserFieldWipeFromField = FALSE;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(THE_WICKED_ERASER, CARD_EFFECT_TEXT_THE_WICKED_ERASER_POPUP_1);
  gHideEffectText = hideEffectText;

  if (IsDuelOver() == TRUE)
    return;

  DestroyAllFieldCards();

  if (IsDuelOver() == TRUE)
    return;

  CheckWinConditionExodia(WhoseTurn());
  TryActivatingPermanentEffects();
}

void TheWickedEraser_TryResolveFieldWipe(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return;

  if (!gTheWickedEraserFieldWipePending)
    return;

  if (!gTheWickedEraserFieldWipeFromField)
    return;

  gActiveEffect.turnRow = gTheWickedEraserFieldWipeTurnRow;
  gActiveEffect.col = 0;
  gActiveEffect.cardId = THE_WICKED_ERASER;
  ActivateTheWickedEraser();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheWickedEraser_SelfCheck(void)
{
  if (Duel_StatFromCount(3, THE_WICKED_ERASER_STAT_PER_CARD, 0) != 3000)
    __builtin_trap();
}
#endif
