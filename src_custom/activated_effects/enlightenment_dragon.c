#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define ENLIGHTENMENT_LP_COST 2000
#define ENLIGHTENMENT_MILL_COUNT 4

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayLpCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= ENLIGHTENMENT_LP_COST;
}

static u8 FieldHasOtherCard(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == self || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      return TRUE;
    }
  }

  return FALSE;
}

static u8 AnyGraveyardHasCard(void)
{
  u8 fixedDuelist;

  if (!GraveyardExpand_IsEnabled()) {
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != CARD_NONE
        || gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != CARD_NONE;
  }

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    if (GraveyardExpand_GetCount(fixedDuelist) > 0)
      return TRUE;
  }

  return FALSE;
}

static void BanishAllOtherFieldCards(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

static void BanishEntireGraveyard(u8 turnDuelist)
{
  u8 fixedDuelist;

  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[turnDuelist]->graveyard != CARD_NONE)
      Duel_BanishGraveyardTopTurn(turnDuelist);
    return;
  }

  while (GraveyardExpand_GetCount(fixedDuelist) > 0)
    Duel_BanishGraveyardAtFixed(fixedDuelist, 0);

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
}

static u8 DeckRemaining(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return (u8)(deckSize - top);
}

static u8 CanBanishNuke(struct DuelCard *self)
{
  if (!CanPayLpCost())
    return FALSE;

  return FieldHasOtherCard(self) || AnyGraveyardHasCard();
}

unsigned char CanActivateENLIGHTENMENT_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ENLIGHTENMENT_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ENLIGHTENMENT_DRAGON)
    return FALSE;

  /* Extra Summon conditions + destroy-add banished FALSE.
   * Ceiling: OPT pay 2000 → banish all other field+both GYs, else OPT mill 4.
   * Separate OPTs share one MarkMonsterEffectUsed. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanBanishNuke(zone))
    return TRUE;

  return DeckRemaining() >= ENLIGHTENMENT_MILL_COUNT;
}

void ActivateENLIGHTENMENT_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ENLIGHTENMENT_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanBanishNuke(self)) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -ENLIGHTENMENT_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    if (IsDuelOver() == TRUE)
      return;

    BanishAllOtherFieldCards(self);
    if (IsDuelOver() == TRUE)
      return;

    BanishEntireGraveyard(ACTIVE_DUELIST);
    BanishEntireGraveyard(INACTIVE_DUELIST);
    GraveyardExpand_RefreshDisplay();

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (DeckRemaining() < ENLIGHTENMENT_MILL_COUNT)
    return;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, ENLIGHTENMENT_MILL_COUNT, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
