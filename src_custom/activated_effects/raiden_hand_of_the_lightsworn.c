#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "raiden_hand_of_the_lightsworn.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define RAIDEN_MILL_COUNT 2
#define RAIDEN_END_PHASE_MILL 2

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 DeckTopWillMillLightsworn(u8 count)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < top + count && i < deckSize; i++) {
    if (IsLightswornMonster(gDuelDecks[fixedDuelist].cards[i]))
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateRAIDEN_HAND_OF_THE_LIGHTSWORN(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != RAIDEN_HAND_OF_THE_LIGHTSWORN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != RAIDEN_HAND_OF_THE_LIGHTSWORN)
    return FALSE;

  /* EP mill via TryApplyRaidenEndPhase. Ceiling: Main Phase OPT mill 2. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return gDuelDecks[fixedDuelist].cardsDrawn + RAIDEN_MILL_COUNT <= NumCardsInDeck(fixedDuelist);
}

void TryApplyRaidenEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != RAIDEN_HAND_OF_THE_LIGHTSWORN)
      continue;
    Duel_ShowEffectTextTyped(RAIDEN_HAND_OF_THE_LIGHTSWORN, 2);
    Duel_MillTopDeckCards(turn, RAIDEN_END_PHASE_MILL, TRUE);
    return;
  }
}

void ActivateRAIDEN_HAND_OF_THE_LIGHTSWORNEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 milledLightsworn;

  Duel_ShowEffectTextTyped(RAIDEN_HAND_OF_THE_LIGHTSWORN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  milledLightsworn = DeckTopWillMillLightsworn(RAIDEN_MILL_COUNT);

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, RAIDEN_MILL_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (milledLightsworn) {
    /* ponytail: +1 tempStage (~500 ATK, not exact +200); until opp EP clear needs hook. */
    if (self->tempStage < 127)
      self->tempStage += 1;
    RefreshFieldMonsterStatOverlays();
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
