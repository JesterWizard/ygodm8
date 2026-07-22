#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void SetCardInfo(unsigned short id);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MINERVA_MAX_BANISH 4

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

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

static u8 CountLightswornOnField(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsLightswornMonster(zone->id))
      count++;
  }

  return count;
}

static u8 CountLightswornInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 count = 0;

  if (!GraveyardExpand_IsEnabled()) {
    return IsLightswornMonster(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 DeckRemaining(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return deckSize - top;
}

static u8 MillLightswornDifferentTypes(u8 max)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u32 seenTypes = 0;
  u8 milled = 0;
  u8 i;

  if (max == 0)
    return 0;

  for (i = top; i < deckSize && milled < max;) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];
    u8 monsterType;
    u32 bit;

    if (!IsLightswornMonster(cardId)) {
      i++;
      continue;
    }

    SetCardInfo(cardId);
    monsterType = gCardInfo.type;
    bit = 1u << (monsterType & 31);
    if (seenTypes & bit) {
      i++;
      continue;
    }

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      break;

    if (GraveyardExpand_IsEnabled()) {
      GraveyardExpand_PushFixed(fixedDuelist, cardId);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
    } else {
      gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = cardId;
    }

    seenTypes |= bit;
    milled++;
    deckSize = NumCardsInDeck(fixedDuelist);
    top = gDuelDecks[fixedDuelist].cardsDrawn;
    i = top;
  }

  return milled;
}

static u8 BanishLightswornFromGyUpTo(u8 max)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 banished = 0;
  u8 i;

  if (max == 0)
    return 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsLightswornMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < max; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (!IsLightswornMonster(cardId))
      continue;

    if (Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1) == CARD_NONE)
      continue;

    banished++;
  }

  if (banished > 0)
    GraveyardExpand_RefreshDisplay();

  return banished;
}

static u8 CanMillDifferentTypes(void)
{
  return CountLightswornOnField() > 0 && DeckRemaining() > 0;
}

static u8 CanBanishMill(void)
{
  return CountLightswornInGy() > 0 && DeckRemaining() > 0;
}

unsigned char CanActivateMINERVA_THE_ATHENIAN_LIGHTSWORN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MINERVA_THE_ATHENIAN_LIGHTSWORN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MINERVA_THE_ATHENIAN_LIGHTSWORN)
    return FALSE;

  /* anti-banish continuous + Synchro material count need continuous/synchro hooks.
   * OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanBanishMill() || CanMillDifferentTypes();
}

void ActivateMINERVA_THE_ATHENIAN_LIGHTSWORNEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 banished;
  u8 max;

  Duel_ShowEffectTextTyped(MINERVA_THE_ATHENIAN_LIGHTSWORN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanBanishMill()) {
    max = CountLightswornInGy();
    if (max > MINERVA_MAX_BANISH)
      max = MINERVA_MAX_BANISH;

    banished = BanishLightswornFromGyUpTo(max);
    if (banished == 0)
      return;

    if (Duel_MillTopDeckCards(ACTIVE_DUELIST, banished, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  max = CountLightswornOnField();
  if (MillLightswornDifferentTypes(max) == 0)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
