#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 ShuffleAllBanishedIntoDecks(u8 *outShuffled)
{
  u8 fixedDuelist;
  u8 total = 0;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 count = RemovedFromPlay_GetCount(fixedDuelist);
    u8 i;

    for (i = 0; i < count; i++) {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

      if (cardId == CARD_NONE)
        continue;

      ReturnCardToDeckTop(fixedDuelist, cardId);
      total++;
    }

    for (i = 0; i < REMOVED_FROM_PLAY_CAPACITY; i++)
      gRemovedFromPlay[fixedDuelist][i] = CARD_NONE;
  }

  if (total == 0)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  Duel_ShuffleDeckFromDrawn(INACTIVE_DUELIST);
  *outShuffled = total;
  return TRUE;
}

static u8 AnyBanishedCards(void)
{
  u8 fixedDuelist;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    if (RemovedFromPlay_GetCount(fixedDuelist) > 0)
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateNECROFACE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != NECROFACE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != NECROFACE)
    return FALSE;

  /* Normal Summon shuffle + banish-mill branches need summon/banish
   * hooks. OPT shuffle all banished into Decks + tempStage per card. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return AnyBanishedCards();
}

void ActivateNECROFACEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 shuffled = 0;

  Duel_ShowEffectTextTyped(NECROFACE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!ShuffleAllBanishedIntoDecks(&shuffled))
    return;

  /* tempStage unit is ~500 ATK, not printed +100; upgrade: exact overlay. */
  if (shuffled > 0 && self->tempStage < 127 - (s8)shuffled)
    self->tempStage += (s8)shuffled;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
