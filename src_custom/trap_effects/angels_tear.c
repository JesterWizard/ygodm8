#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "angels_tear.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

#define ANGELS_TEAR_BANISH_COUNT 4

static const u8 sAngelsTearPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u8 CountFairyMonstersInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsFairyMonster(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 GraveyardHasTargetableFairy(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsFairyMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 IsGyIndexExcluded(u8 gyIndex, const u8 *excluded, u8 excludedCount)
{
  u8 i;

  for (i = 0; i < excludedCount; i++) {
    if (excluded[i] == gyIndex)
      return TRUE;
  }

  return FALSE;
}

static u8 LoadFairyGraveyardPickMenu(u8 fixedDuelist, const u8 *excluded, u8 excludedCount,
                                     u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsGyIndexExcluded(i, excluded, excludedCount))
      continue;

    if (!IsFairyMonster(cardId))
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

static s8 GyIndexForSortedMenuPick(u8 fixedDuelist, u8 menuPos, u8 menuCount,
                                   const u8 *excluded, u8 excludedCount)
{
  u16 cardId;
  u8 occurrence = 0;
  u8 seen = 0;
  u8 i;
  u8 gyCount;

  if (menuPos >= menuCount)
    return -1;

  cardId = gDeckMenu.cards[menuPos];
  if (cardId == CARD_NONE)
    return -1;

  for (i = 0; i <= menuPos; i++) {
    if (gDeckMenu.cards[i] == cardId)
      occurrence++;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 gyCard = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsGyIndexExcluded(i, excluded, excludedCount))
      continue;

    if (!IsFairyMonster(gyCard))
      continue;

    if (gyCard == cardId) {
      seen++;
      if (seen == occurrence)
        return (s8)i;
    }
  }

  return -1;
}

static s8 PlayerPickFairyGyIndex(u8 fixedDuelist, const u8 *excluded, u8 excludedCount)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 j;
  s8 chosenGyIndex;

  menuCount = LoadFairyGraveyardPickMenu(fixedDuelist, excluded, excludedCount, gyIndexMap);
  if (menuCount == 0)
    return -1;

  if (menuCount == 1)
    return (s8)gyIndexMap[0];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sAngelsTearPickLabels, ARRAY_COUNT(sAngelsTearPickLabels))) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = savedDeckMenu[j];
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = GyIndexForSortedMenuPick(fixedDuelist, gDeckMenu.currentPos, menuCount,
                                           excluded, excludedCount);

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&gDeckMenu)[j] = savedDeckMenu[j];

  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static void SortIndicesDescending(u8 *indices, u8 count)
{
  u8 i;
  u8 j;

  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if (indices[j] > indices[i]) {
        u8 tmp = indices[i];

        indices[i] = indices[j];
        indices[j] = tmp;
      }
    }
  }
}

static s8 FindLowestAtkFairyGyIndex(u8 fixedDuelist, const u8 *excluded, u8 excludedCount)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  s8 bestIndex = -1;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId;
    u16 atk;

    if (IsGyIndexExcluded(i, excluded, excludedCount))
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsFairyMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex < 0 || atk < bestAtk) {
      bestAtk = atk;
      bestIndex = (s8)i;
    }
  }

  return bestIndex;
}

static s8 FindHighestAtkFairyGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  s8 bestIndex = -1;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsFairyMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex < 0 || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = (s8)i;
    }
  }

  return bestIndex;
}

static void BanishGraveyardCardAt(u8 turnDuelist, u8 gyIndex)
{
  Duel_BanishGraveyardAtTurn(turnDuelist, gyIndex);
}

static u8 OwnerUsesPlayerMenu(u8 turnDuelist)
{
  return gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER];
}

static u8 MonsterRowForTurnDuelist(u8 turnDuelist)
{
  if (turnDuelist == ACTIVE_DUELIST)
    return ACTIVE_DUELIST_MONSTER_ROW;

  return INACTIVE_DUELIST_MONSTER_ROW;
}

static u8 PickBanishIndices(u8 turnDuelist, u8 fixedDuelist, u8 *banishIndices)
{
  u8 excludedCount = 0;
  u8 i;

  for (i = 0; i < ANGELS_TEAR_BANISH_COUNT; i++) {
    s8 gyIndex;

    if (OwnerUsesPlayerMenu(turnDuelist))
      gyIndex = PlayerPickFairyGyIndex(fixedDuelist, banishIndices, excludedCount);
    else
      gyIndex = FindLowestAtkFairyGyIndex(fixedDuelist, banishIndices, excludedCount);

    if (gyIndex < 0)
      return FALSE;

    banishIndices[excludedCount] = (u8)gyIndex;
    excludedCount++;
  }

  SortIndicesDescending(banishIndices, ANGELS_TEAR_BANISH_COUNT);
  for (i = 0; i < ANGELS_TEAR_BANISH_COUNT; i++)
    BanishGraveyardCardAt(turnDuelist, banishIndices[i]);

  GraveyardExpand_RefreshDisplay();
  return TRUE;
}

static enum DuelActionResult SpecialSummonFairyFromGrave(u8 turnDuelist, u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsFairyMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
  if (!IsFairyMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

u8 CanActivateAngelsTearForDuelist(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForTurnDuelist(turnDuelist)]) < 0)
    return FALSE;

  /* ponytail: need 4 banish targets plus 1 summon target. */
  if (CountFairyMonstersInGraveyard(fixedDuelist) < ANGELS_TEAR_BANISH_COUNT + 1)
    return FALSE;

  return GraveyardHasTargetableFairy(fixedDuelist);
}

static void ResolveAngelsTearZone(struct DuelCard *zone, u8 ownerTurnDuelist)
{
  u8 banishIndices[ANGELS_TEAR_BANISH_COUNT];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ownerTurnDuelist);
  s8 summonGyIndex;

  if (!CanActivateAngelsTearForDuelist(ownerTurnDuelist))
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectTextTyped(ANGELS_TEAR, 3);

  if (IsDuelOver() == TRUE)
    return;

  if (!PickBanishIndices(ownerTurnDuelist, fixedDuelist, banishIndices))
    return;

  if (!GraveyardHasTargetableFairy(fixedDuelist))
    return;

  if (OwnerUsesPlayerMenu(ownerTurnDuelist))
    summonGyIndex = PlayerPickFairyGyIndex(fixedDuelist, NULL, 0);
  else
    summonGyIndex = FindHighestAtkFairyGyIndex(fixedDuelist);

  if (summonGyIndex < 0)
    return;

  if (SpecialSummonFairyFromGrave(ownerTurnDuelist, (u8)summonGyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  if (zone != NULL)
    Duel_DestroyZone(zone, ownerTurnDuelist, TRUE);
}

void TryActivateAngelsTearOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != ANGELS_TEAR || zone->isFaceUp != FALSE)
      continue;

    if (!CanActivateAngelsTearForDuelist(INACTIVE_DUELIST))
      continue;

    ResolveAngelsTearZone(zone, INACTIVE_DUELIST);
  }
}

#if defined(ANGELS_TEAR_SELF_CHECK)
void AngelsTear_SelfCheck(void)
{
  if (ANGELS_TEAR_BANISH_COUNT != 4)
    while (1)
      ;
}
#endif
