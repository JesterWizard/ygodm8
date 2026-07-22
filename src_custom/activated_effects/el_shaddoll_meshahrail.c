#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MESHAHRAIL_LP_COST 800

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";
static const char sVoidName[] APPEND_RODATA = "Void";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayMeshahrailCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= MESHAHRAIL_LP_COST;
}

static u8 IsShaddollOrVoidSearch(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE || cardId == EL_SHADDOLL_MESHAHRAIL)
    return FALSE;

  if (Duel_CardNameContains(cardId, sShaddollName))
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sVoidName);
}

static u16 FindDeckShaddollOrVoid(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsShaddollOrVoidSearch(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateEL_SHADDOLL_MESHAHRAIL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EL_SHADDOLL_MESHAHRAIL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EL_SHADDOLL_MESHAHRAIL)
    return FALSE;

  /* OPT pay 800 → add 1 Shaddoll or Void S/T from Deck (EffectOpt).
   * Ceiling: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. */
  if (EffectOpt_IsUsed(EL_SHADDOLL_MESHAHRAIL))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!CanPayMeshahrailCost())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckShaddollOrVoid() != CARD_NONE;
}

void ActivateEL_SHADDOLL_MESHAHRAILEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(EL_SHADDOLL_MESHAHRAIL, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(EL_SHADDOLL_MESHAHRAIL))
    return;

  cardId = FindDeckShaddollOrVoid();
  if (cardId == CARD_NONE || !CanPayMeshahrailCost())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)MESHAHRAIL_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(EL_SHADDOLL_MESHAHRAIL);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
