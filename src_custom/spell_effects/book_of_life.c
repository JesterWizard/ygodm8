#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "book_of_life.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

static const u8 sBookOfLifePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsZombieMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_ZOMBIE;
}

static u8 IsMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 GyHasMatchingCard(u8 fixedDuelist, u8 (*pred)(u16))
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return cardId != CARD_NONE && pred(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (pred(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateBookOfLife(void)
{
  u8 activeFixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GyHasMatchingCard(activeFixed, IsZombieMonster))
    return FALSE;

  if (!GyHasMatchingCard(DUEL_OPPONENT, IsMonsterCard))
    return FALSE;

  return TRUE;
}

static u8 LoadOppGyMonsterMenu(u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(DUEL_OPPONENT);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(DUEL_OPPONENT, i);

    if (!IsMonsterCard(cardId))
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

static s8 FindFirstOppGyMonsterIndex(void)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsMonsterCard(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard) ? 0 : -1;

  gyCount = GraveyardExpand_GetCount(DUEL_OPPONENT);
  for (i = 0; i < gyCount; i++) {
    if (IsMonsterCard(GraveyardExpand_GetCardAt(DUEL_OPPONENT, i)))
      return (s8)i;
  }

  return -1;
}

static s8 PlayerPickOppGyMonsterIndex(void)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadOppGyMonsterMenu(gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(
          sBookOfLifePickLabels, ARRAY_COUNT(sBookOfLifePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static void BanishOpponentGyMonster(void)
{
  s8 gyIndex;

  if (!GraveyardExpand_IsEnabled()) {
    /* Single-card GY model: banish opponent's top graveyard card. */
    if (IsMonsterCard(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard))
      Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    gyIndex = PlayerPickOppGyMonsterIndex();
  else
    gyIndex = FindFirstOppGyMonsterIndex();

  if (gyIndex < 0)
    return;

  Duel_BanishGraveyardAtFixed(DUEL_OPPONENT, (u8)gyIndex);
}

static void BookOfLife_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  Duel_ShowEffectText(BOOK_OF_LIFE);

  if (IsDuelOver() == TRUE || !CanActivateBookOfLife())
    return;

  if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  BanishOpponentGyMonster();

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectBookOfLife(void)
{
  if (Duel_TryResolveSpellThroughTraps(BOOK_OF_LIFE, BookOfLife_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
