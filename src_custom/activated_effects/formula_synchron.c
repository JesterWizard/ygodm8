#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 DeckHasRemainingCards(void)
{
  u8 fixedDuelist;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  return gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist);
}

unsigned char CanActivateFORMULA_SYNCHRON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != FORMULA_SYNCHRON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != FORMULA_SYNCHRON)
    return FALSE;

  /* Synchro Summon draw trigger + opp-Main-Phase quick Synchro need
   * synchro/chain hooks. Ceiling: OPT draw 1 via usage when deck remains. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return DeckHasRemainingCards();
}

void ActivateFORMULA_SYNCHRONEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(FORMULA_SYNCHRON, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}
