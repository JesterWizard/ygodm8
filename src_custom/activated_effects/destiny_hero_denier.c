#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroExceptDenier(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DESTINY_HERO_DENIER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u16 FindDestinyHeroInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDestinyHeroExceptDenier(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindDestinyHeroInGraveyard(u8 *outIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsDestinyHeroExceptDenier(cardId)) {
      *outIndex = 0;
      return cardId;
    }

    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsDestinyHeroExceptDenier(cardId)) {
      *outIndex = i;
      return cardId;
    }
  }

  return CARD_NONE;
}

static u16 FindDestinyHeroBanished(u8 *outFixedDuelist, u8 *outIndex)
{
  u8 fixedDuelist;

  if (!RemovedFromPlay_IsEnabled())
    return CARD_NONE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 count = RemovedFromPlay_GetCount(fixedDuelist);
    u8 i;

    for (i = 0; i < count; i++) {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

      if (IsDestinyHeroExceptDenier(cardId)) {
        *outFixedDuelist = fixedDuelist;
        *outIndex = i;
        return cardId;
      }
    }
  }

  return CARD_NONE;
}

static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  u8 count;
  u8 i;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  if (index >= count)
    return;

  for (i = index + 1; i < count; i++)
    gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];

  gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
}

static u8 PutDestinyHeroOnDeckTop(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;
  u8 gyIndex;
  u8 banishFixed;
  u8 banishIndex;

  cardId = FindDestinyHeroInDeck();
  if (cardId != CARD_NONE) {
    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST,
                              (u8)Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId), FALSE)
        != DUEL_ACTION_OK)
      return FALSE;

    ReturnCardToDeckTop(fixedDuelist, cardId);
    return TRUE;
  }

  cardId = FindDestinyHeroInGraveyard(&gyIndex);
  if (cardId != CARD_NONE) {
    if (!GraveyardExpand_IsEnabled()) {
      gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    } else {
      GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      GraveyardExpand_RefreshDisplay();
    }

    ReturnCardToDeckTop(fixedDuelist, cardId);
    return TRUE;
  }

  cardId = FindDestinyHeroBanished(&banishFixed, &banishIndex);
  if (cardId == CARD_NONE)
    return FALSE;

  RemoveBanishedAt(banishFixed, banishIndex);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  return TRUE;
}

unsigned char CanActivateDESTINY_HERO_DENIER(void)
{
  struct DuelCard *zone;
  u8 gyIndex;
  u8 banishFixed;
  u8 banishIndex;

  if (gMonEffect.id != DESTINY_HERO_DENIER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DENIER)
    return FALSE;

  /* Ceiling: GY SS when other D-HERO present needs GY/once-per-duel hooks.
   * OPT put 1 D-HERO from Deck/GY/banished on top of Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FindDestinyHeroInDeck() != CARD_NONE)
    return TRUE;

  if (FindDestinyHeroInGraveyard(&gyIndex) != CARD_NONE)
    return TRUE;

  return FindDestinyHeroBanished(&banishFixed, &banishIndex) != CARD_NONE;
}

void ActivateDESTINY_HERO_DENIEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DESTINY_HERO_DENIER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!PutDestinyHeroOnDeckTop())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
