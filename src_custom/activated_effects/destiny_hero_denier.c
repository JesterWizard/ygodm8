#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static u8 sDenierInit APPEND_DATA = {0};
static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsDestinyHeroExceptDenier(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DESTINY_HERO_DENIER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static s8 FindDenierInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == DESTINY_HERO_DENIER)
      return 0;
    return -1;
  }
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DENIER)
      return (s8)i;
  }
  return -1;
}

static void TryDenierGySs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                            : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;

  /* Once-per-duel ≈ EffectOpt (turn); duel-scoped latch not tracked. */
  if (EffectOpt_IsUsed(DESTINY_HERO_DENIER))
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return;
  if (FindDenierInGy(fixedDuelist) < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DENIER, 8);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(turnDuelist, DESTINY_HERO_DENIER, opts)
      != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DENIER);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void OnOtherDestinyHeroDestroyedWhileDenierInGy(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId == CARD_NONE || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (!IsDestinyHeroExceptDenier(ev->cardId))
    return;
  if (FindDenierInGy(ev->controller) < 0)
    return;

  TryDenierGySs(ev->controller);
}

void DestinyHeroDenier_EnsureInit(void)
{
  if (sDenierInit)
    return;

  sDenierInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnOtherDestinyHeroDestroyedWhileDenierInGy);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY,
                        OnOtherDestinyHeroDestroyedWhileDenierInGy);
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

  /* GY SS when other D-HERO destroyed via DestinyHeroDenier_EnsureInit.
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
