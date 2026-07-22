#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const u8 sAmbusherPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 OppFixedDuelist(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_OPPONENT;

  return DUEL_PLAYER;
}

static u8 OppGyHasCard(u8 oppFixed)
{
  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[oppFixed].graveyard != CARD_NONE;

  return GraveyardExpand_GetCount(oppFixed) > 0;
}

static u8 LoadOppGyMenu(u8 oppFixed, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(oppFixed);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(oppFixed, i);

    if (cardId == CARD_NONE)
      continue;

    gyIndexMap[menuCount] = i;
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

static void AppendCardToDeckBottom(u8 fixedDuelist, u16 cardId)
{
  u8 deckSize;

  if (cardId == CARD_NONE)
    return;

  deckSize = NumCardsInDeck(fixedDuelist);
  if (deckSize >= 60)
    return;

  gDuelDecks[fixedDuelist].cards[deckSize] = cardId;
}

static u8 MoveOppGyCardToDeckBottom(u8 oppFixed, u8 gyIndex)
{
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[oppFixed].graveyard;
    if (cardId == CARD_NONE)
      return FALSE;

    gDuel.duelistbattleState[oppFixed].graveyard = CARD_NONE;
  } else {
    cardId = GraveyardExpand_GetCardAt(oppFixed, gyIndex);
    if (cardId == CARD_NONE)
      return FALSE;

    cardId = GraveyardExpand_RemoveAtFixed(oppFixed, gyIndex);
    GraveyardExpand_SyncLegacyTop(oppFixed);
    GraveyardExpand_RefreshDisplay();
  }

  AppendCardToDeckBottom(oppFixed, cardId);
  return TRUE;
}

static s8 PlayerPickOppGyIndex(u8 oppFixed)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadOppGyMenu(oppFixed, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sAmbusherPickLabels, ARRAY_COUNT(sAmbusherPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

unsigned char CanActivateGRAVEKEEPERS_AMBUSHER(void)
{
  struct DuelCard *zone;
  u8 oppFixed = OppFixedDuelist();

  if (gMonEffect.id != GRAVEKEEPERS_AMBUSHER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_AMBUSHER)
    return FALSE;

  /* flip trigger + Necrovalley search need flip/send hooks. 
   * OPT put 1 opponent GY card on bottom of their Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppGyHasCard(oppFixed);
}

void ActivateGRAVEKEEPERS_AMBUSHEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 oppFixed = OppFixedDuelist();
  s8 gyIndex;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_AMBUSHER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickOppGyIndex(oppFixed);
  else if (GraveyardExpand_IsEnabled())
    gyIndex = GraveyardExpand_GetCount(oppFixed) > 0 ? 0 : -1;
  else
    gyIndex = OppGyHasCard(oppFixed) ? 0 : -1;

  if (gyIndex < 0)
    return;

  if (!MoveOppGyCardToDeckBottom(oppFixed, (u8)gyIndex))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
