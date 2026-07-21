#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "hero_flash.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const u16 sHeroFlashCostIds[] APPEND_RODATA = {
  H_HEATED_HEART,
  E_EMERGENCY_CALL,
  R_RIGHTEOUS_JUSTICE,
  O_OVERSOUL,
};

static const u8 sHeroFlashPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsElementalHeroNormalMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_IsElementalHeroCard(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == NORMAL_CARD;
}

u8 HeroFlash_CanMonsterAttackDirectly(const struct DuelCard *zone)
{
  return zone != NULL && zone->unkTwo && IsElementalHeroNormalMonster(zone->id);
}

static s8 FindGyIndexOfId(u8 fixedDuelist, u16 cardId)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == cardId)
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == cardId)
      return (s8)i;
  }

  return -1;
}

static u8 GyHasAllHeroFlashCosts(u8 fixedDuelist)
{
  u8 i;

  /* Legacy single-slot GY cannot hold all 4 cost cards. */
  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sHeroFlashCostIds); i++) {
    if (FindGyIndexOfId(fixedDuelist, sHeroFlashCostIds[i]) < 0)
      return FALSE;
  }

  return TRUE;
}

static s16 FindFirstHeroNormalDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsElementalHeroNormalMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CanActivateHeroFlash(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GyHasAllHeroFlashCosts(fixedDuelist))
    return FALSE;

  return FindFirstHeroNormalDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 BanishHeroFlashCosts(u8 fixedDuelist)
{
  u8 i;
  s8 indices[ARRAY_COUNT(sHeroFlashCostIds)];
  s8 a;
  s8 b;
  u8 tmp;

  for (i = 0; i < ARRAY_COUNT(sHeroFlashCostIds); i++) {
    indices[i] = FindGyIndexOfId(fixedDuelist, sHeroFlashCostIds[i]);
    if (indices[i] < 0)
      return FALSE;
  }

  /* Banish high index first so lower indices stay valid. */
  for (a = 0; a < (s8)ARRAY_COUNT(indices) - 1; a++) {
    for (b = a + 1; b < (s8)ARRAY_COUNT(indices); b++) {
      if (indices[a] < indices[b]) {
        tmp = (u8)indices[a];
        indices[a] = indices[b];
        indices[b] = (s8)tmp;
      }
    }
  }

  for (i = 0; i < ARRAY_COUNT(indices); i++)
    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)indices[i]);

  GraveyardExpand_RefreshDisplay();
  return TRUE;
}

static u8 LoadHeroNormalDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsElementalHeroNormalMonster(cardId))
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

static u8 PickHeroNormalDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadHeroNormalDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sHeroFlashPickLabels, ARRAY_COUNT(sHeroFlashPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static void GrantDirectAttackToControlledHeroNormals(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || !IsElementalHeroNormalMonster(zone->id))
      continue;

    zone->unkTwo = TRUE;
  }
}

static void HERO_FLASH_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckIndex;
  u16 cardId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  Duel_ShowEffectText(HERO_FLASH);

  if (IsDuelOver() == TRUE || !CanActivateHeroFlash())
    return;

  if (!BanishHeroFlashCosts(fixedDuelist))
    return;

  if (spellZone != NULL && spellZone->id == HERO_FLASH)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickHeroNormalDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF)
    return;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsElementalHeroNormalMonster(cardId))
    return;

  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  GrantDirectAttackToControlledHeroNormals();
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectHERO_FLASH(void)
{
  if (!CanActivateHeroFlash()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(HERO_FLASH, HERO_FLASH_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HERO_FLASH_SelfCheck(void)
{
  if (!IsElementalHeroNormalMonster(ELEMENTAL_HERO_AVIAN))
    while (1)
      ;
  if (IsElementalHeroNormalMonster(ELEMENTAL_HERO_BUBBLEMAN))
    while (1)
      ;
  if (ARRAY_COUNT(sHeroFlashCostIds) != 4)
    while (1)
      ;
}
#endif
