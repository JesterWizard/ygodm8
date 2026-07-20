#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define DOMINANCE_TOP_N 5

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 DeckRemaining(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return deckSize - top;
}

static u8 PickDeckToRearrange(void)
{
  u8 me = FixedDuelistForActive();
  u8 opp = me == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  /* Prefer own Deck; opp only if own empty. */
  if (DeckRemaining(me) > 0)
    return me;

  if (DeckRemaining(opp) > 0)
    return opp;

  return 0xFF;
}

static void ShuffleTopNOfFixedDeck(u8 fixedDuelist, u8 n)
{
  u8 start = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 remaining = DeckRemaining(fixedDuelist);
  u8 end;
  u8 size;
  int i;

  if (remaining == 0)
    return;

  if (remaining < n)
    n = remaining;

  end = start + n;
  size = end - start;
  if (size <= 1)
    return;

  /* ponytail: look+reorder UI missing; RandRange shuffle of top N is stand-in. */
  for (i = 0; i < 200; i++) {
    u8 indexA = RandRangeU8(0, size - 1);
    u8 indexB = RandRangeU8(0, size - 1);
    u16 temp = gDuelDecks[fixedDuelist].cards[start + indexA];

    gDuelDecks[fixedDuelist].cards[start + indexA] =
        gDuelDecks[fixedDuelist].cards[start + indexB];
    gDuelDecks[fixedDuelist].cards[start + indexB] = temp;
  }
}

unsigned char CanActivateDESTINY_HERO_DOMINANCE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DOMINANCE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DOMINANCE)
    return FALSE;

  /* ponytail: battle-destroy draw + GY SS 3 D-HERO need battle/destroy hooks.
   * Ceiling: OPT shuffle top 5 of your (else opp) Deck as look+reorder stand-in. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return PickDeckToRearrange() != 0xFF;
}

void ActivateDESTINY_HERO_DOMINANCEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DOMINANCE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  fixedDuelist = PickDeckToRearrange();
  if (fixedDuelist == 0xFF)
    return;

  ShuffleTopNOfFixedDeck(fixedDuelist, DOMINANCE_TOP_N);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
