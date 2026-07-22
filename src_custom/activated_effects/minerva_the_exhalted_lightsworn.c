#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MINERVA_MILL_COUNT 3

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
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

static u8 CountLightswornAmongTop(u8 count)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 ls = 0;

  for (i = 0; i < count; i++) {
    if (IsLightswornCard(gDuelDecks[fixedDuelist].cards[top + i]))
      ls++;
  }

  return ls;
}

unsigned char CanActivateMINERVA_THE_EXHALTED_LIGHTSWORN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MINERVA_THE_EXHALTED_LIGHTSWORN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MINERVA_THE_EXHALTED_LIGHTSWORN)
    return FALSE;

  /* Xyz detach + destroy-on-death FALSE. Ceiling: OPT mill 3 → draw = Lightsworn
   * among milled. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return DeckRemaining() >= MINERVA_MILL_COUNT;
}

void ActivateMINERVA_THE_EXHALTED_LIGHTSWORNEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 drawCount;

  Duel_ShowEffectTextTyped(MINERVA_THE_EXHALTED_LIGHTSWORN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (DeckRemaining() < MINERVA_MILL_COUNT)
    return;

  drawCount = CountLightswornAmongTop(MINERVA_MILL_COUNT);

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, MINERVA_MILL_COUNT, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (drawCount > 0) {
    if (Duel_DrawCards(ACTIVE_DUELIST, drawCount, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
