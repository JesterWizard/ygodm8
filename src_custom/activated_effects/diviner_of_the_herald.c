#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u16 FindFairyInDeckFor(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFairyMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 SendFairyFromDeckToGraveyardFor(u8 turnDuelist, u8 fixedDuelist, u16 *outLevel)
{
  s16 deckIndex;
  u16 cardId;

  cardId = FindFairyInDeckFor(fixedDuelist);
  if (cardId == CARD_NONE)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);

  *outLevel = gCardData_NEW[cardId].level;
  return TRUE;
}

void TryDivinerOfTheHeraldOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 level = 0;

  if (zone == NULL || zone->id != DIVINER_OF_THE_HERALD || gHideEffectText)
    return;

  if (EffectOpt_IsUsed(DIVINER_OF_THE_HERALD))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (FindFairyInDeckFor(fixedDuelist) == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(DIVINER_OF_THE_HERALD, 8);
  /* Printed remainder omitted by this ruleset. */
  if (!SendFairyFromDeckToGraveyardFor(turnDuelist, fixedDuelist, &level))
    return;

  zone->unkTwo = (u8)level;
  EffectOpt_MarkUsed(DIVINER_OF_THE_HERALD);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateDIVINER_OF_THE_HERALD(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;

  if (gMonEffect.id != DIVINER_OF_THE_HERALD)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DIVINER_OF_THE_HERALD)
    return FALSE;

  /* On-NS/SS mill via TryDivinerOfTheHeraldOnMonsterPlacement (EffectOpt).
   * tribute SS Fairy needs tribute hooks.
   * OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in until EP clear). */
  if (EffectOpt_IsUsed(DIVINER_OF_THE_HERALD))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
                     ? DUEL_PLAYER
                     : DUEL_OPPONENT;
  return FindFairyInDeckFor(fixedDuelist) != CARD_NONE;
}

void ActivateDIVINER_OF_THE_HERALDEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
                        ? DUEL_PLAYER
                        : DUEL_OPPONENT;
  u16 level = 0;

  Duel_ShowEffectTextTyped(DIVINER_OF_THE_HERALD, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!SendFairyFromDeckToGraveyardFor(ACTIVE_DUELIST, fixedDuelist, &level))
    return;

  /* Level bump until EOT uses unkTwo; cleared via TryClearDivinerOfTheHeraldEndPhase. */
  self->unkTwo = (u8)level;

  EffectOpt_MarkUsed(DIVINER_OF_THE_HERALD);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
