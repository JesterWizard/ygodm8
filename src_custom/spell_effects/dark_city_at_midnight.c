#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dark_city_at_midnight.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);
void IncrementPermStage(struct DuelCard *zone);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static const u8 sDarkCityPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sDarkCitySearchUsed APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

u8 DarkCity_IsLevel8OrHigherDestinyHero(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sDestinyHeroName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 8;
}

static u8 IsDarkCitySearchTarget(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DARK_CITY_AT_MIDNIGHT)
    return FALSE;

  if (Duel_CardNameContains(cardId, sDestinyHeroName))
    return TRUE;

  /* Approximate "mentions a Destiny HERO monster's card name". */
  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 LoadSearchMenu(u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsDarkCitySearchTarget(cardId))
      continue;

    deckIndexOut[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u8 FindDestinyHeroDeckCard(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (Duel_CardNameContains(gDuelDecks[fixedDuelist].cards[i], sDestinyHeroName))
      return i;
  }

  return 0xFF;
}

u8 Cond_DarkCityOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  /* Parent wires this only from the Special Summon event path. */
  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller > DUEL_OPPONENT || !DarkCity_IsLevel8OrHigherDestinyHero(ev->cardId))
    return FALSE;

  return Duel_FindBackrowCard(ev->controller, DARK_CITY_AT_MIDNIGHT, TRUE) != NULL;
}

enum DuelActionResult Op_DarkCityOnSummon(struct EffectCtx *ctx)
{
  u8 row;
  u8 i;

  if (!Cond_DarkCityOnSummon(ctx))
    return DUEL_ACTION_NO_TARGET;

  row = Duel_FixedMonsterRowForDuelist(ctx->event->controller);
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[row][i];

    if (zone->id != CARD_NONE && zone->isFaceUp
        && Duel_CardHasMonsterType(zone->id, TYPE_WARRIOR)) {
      IncrementPermStage(zone);
      IncrementPermStage(zone);
      IncrementPermStage(zone);
    }
  }

  Duel_RefreshMonsterStatOverlays();
  return DUEL_ACTION_OK;
}

u8 Cond_DarkCityOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != DARK_CITY_AT_MIDNIGHT || ev->controller > DUEL_OPPONENT)
    return FALSE;

  return FindDestinyHeroDeckCard(ev->controller) != 0xFF;
}

enum DuelActionResult Op_DarkCityOnDestroy(struct EffectCtx *ctx)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u8 deckIndex;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!Cond_DarkCityOnDestroy(ctx))
    return DUEL_ACTION_NO_TARGET;

  fixedDuelist = ctx->event->controller;
  deckIndex = FindDestinyHeroDeckCard(fixedDuelist);
  if (deckIndex == 0xFF)
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  return Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
}

static void SearchOnActivate(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;
  u16 cardId;
  s8 empty;
  u8 fixedDuelist;

  if (sDarkCitySearchUsed)
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  menuCount = LoadSearchMenu(deckIndexMap);
  if (menuCount == 0)
    return;

  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sDarkCityPickLabels, ARRAY_COUNT(sDarkCityPickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      return;
    }
    pick = gDeckMenu.currentPos;
    DeckMenu_EndDuelTrunkView();
  }

  cardId = gDeckMenu.cards[pick];
  DECKMENU_RESTORE();

  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndexMap[pick], FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
  sDarkCitySearchUsed = TRUE;
  (void)fixedDuelist;
}

static void DARK_CITY_AT_MIDNIGHT_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(DARK_CITY_AT_MIDNIGHT);
  SearchOnActivate();
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDARK_CITY_AT_MIDNIGHT(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_CITY_AT_MIDNIGHT, DARK_CITY_AT_MIDNIGHT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
