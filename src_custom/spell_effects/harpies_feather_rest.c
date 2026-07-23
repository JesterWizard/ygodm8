#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define HARPIES_FEATHER_REST_RETURN_COUNT 3

void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static const u8 sFeatherRestPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

/* Printed: "Harpie Lady" and/or "Harpie Lady Sisters" (incl. name-as). */
static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  return cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == HARPIE_LADY_SISTERS || cardId == CYBER_HARPIE
      || cardId == CYBER_SLASH_HARPIE_LADY || cardId == CYBER_SLASH_HARPY_LADY
      || cardId == HARPIE_PERFUMER || cardId == HARPIE_QUEEN || cardId == HARPIE_DANCER
      || cardId == HARPIE_ORACLE || cardId == HARPIE_CONDUCTOR || cardId == HARPIE_CHANNELER
      || cardId == HARPIE_HARPIST;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 CountHarpieLadyOrSistersInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsHarpieLadyOrSisters(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsHarpieLadyOrSisters(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControlsLevel5OrHigherHarpie(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (!MonsterIsFaceUp(zone) || !IsHarpieMonster(zone->id))
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level >= 5)
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateHarpiesFeatherRest(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (EffectOpt_IsUsed(HARPIES_FEATHER_REST))
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  return CountHarpieLadyOrSistersInGy(fixedDuelist) >= HARPIES_FEATHER_REST_RETURN_COUNT;
}

u8 HarpiesFeatherRest_CanSpecialSummonCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;
  if (!EffectOpt_IsUsed(HARPIES_FEATHER_REST))
    return TRUE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WIND;
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 IndexExcluded(const u8 *excluded, u8 excludedCount, u8 gyIndex)
{
  u8 i;

  for (i = 0; i < excludedCount; i++) {
    if (excluded[i] == gyIndex)
      return TRUE;
  }
  return FALSE;
}

static u8 LoadFeatherRestGyMenu(u8 fixedDuelist, const u8 *excluded, u8 excludedCount,
                                u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < gyCount && menuCount < ARRAY_COUNT(gDeckMenu.cards); i++) {
    u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsHarpieLadyOrSisters(id))
      continue;
    if (IndexExcluded(excluded, excludedCount, i))
      continue;

    gDeckMenu.cards[menuCount] = id;
    gyIndexMap[menuCount] = i;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static s8 PlayerPickFeatherRestGyIndex(u8 fixedDuelist, const u8 *excluded, u8 excludedCount)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosen;

  DECKMENU_SAVE();
  menuCount = LoadFeatherRestGyMenu(fixedDuelist, excluded, excludedCount, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosen = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosen;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sFeatherRestPickLabels,
                                         ARRAY_COUNT(sFeatherRestPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosen = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosen;
}

static u8 CollectAiGyIndices(u8 fixedDuelist, u8 *outIndices)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 found = 0;
  s8 i;

  for (i = (s8)gyCount - 1; i >= 0 && found < HARPIES_FEATHER_REST_RETURN_COUNT; i--) {
    if (!IsHarpieLadyOrSisters(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
      continue;
    outIndices[found++] = (u8)i;
  }

  return found;
}

static void ShuffleSelectedHarpieLadyFromGraveToDeck(u8 turnDuelist, const u8 *indices, u8 count)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 sorted[HARPIES_FEATHER_REST_RETURN_COUNT];
  u8 i;
  u8 j;

  /* Remove high→low so indices stay valid. */
  for (i = 0; i < count; i++)
    sorted[i] = indices[i];
  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if (sorted[j] > sorted[i]) {
        u8 tmp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = tmp;
      }
    }
  }

  for (i = 0; i < count; i++) {
    u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, sorted[i]);

    ReturnCardToDeck(turnDuelist, cardId);
  }

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  Duel_ShuffleDeckFromDrawn(turnDuelist);
}

static void HARPIES_FEATHER_REST_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 indices[HARPIES_FEATHER_REST_RETURN_COUNT];
  u8 excluded[HARPIES_FEATHER_REST_RETURN_COUNT];
  u8 found = 0;
  u8 drawCount;
  u8 hadLevel5Harpie;
  u8 i;

  if (!CanActivateHarpiesFeatherRest())
    return;

  hadLevel5Harpie = ControlsLevel5OrHigherHarpie();
  drawCount = hadLevel5Harpie ? 2 : 1;

  Duel_ShowEffectText(HARPIES_FEATHER_REST);
  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    for (i = 0; i < HARPIES_FEATHER_REST_RETURN_COUNT; i++) {
      s8 pick = PlayerPickFeatherRestGyIndex(fixedDuelist, excluded, found);

      if (pick < 0)
        return;
      indices[found] = (u8)pick;
      excluded[found] = (u8)pick;
      found++;
    }
  } else {
    found = CollectAiGyIndices(fixedDuelist, indices);
    if (found < HARPIES_FEATHER_REST_RETURN_COUNT)
      return;
  }

  ShuffleSelectedHarpieLadyFromGraveToDeck(ACTIVE_DUELIST, indices, found);

  if (Duel_DrawCards(ACTIVE_DUELIST, drawCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(HARPIES_FEATHER_REST);

  if (spellZone != NULL && spellZone->id == HARPIES_FEATHER_REST)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectHARPIES_FEATHER_REST(void)
{
  if (!CanActivateHarpiesFeatherRest()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(HARPIES_FEATHER_REST, HARPIES_FEATHER_REST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
