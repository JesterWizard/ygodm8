#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define CURIOUS_MILL_COUNT 1

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

unsigned char CanActivateCURIOUS_THE_LIGHTSWORN_DOMINION(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != CURIOUS_THE_LIGHTSWORN_DOMINION)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CURIOUS_THE_LIGHTSWORN_DOMINION)
    return FALSE;

  /* ponytail: Link Summon mill + leave-field GY add + mill-cascade need summon/
   * leave-field hooks. Ceiling: OPT mill 1 from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return gDuelDecks[fixedDuelist].cardsDrawn + CURIOUS_MILL_COUNT
      <= NumCardsInDeck(fixedDuelist);
}

void ActivateCURIOUS_THE_LIGHTSWORN_DOMINIONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(CURIOUS_THE_LIGHTSWORN_DOMINION, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, CURIOUS_MILL_COUNT, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
