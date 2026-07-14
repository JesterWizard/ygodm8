#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "elemental_hero_core.h"
#include "expanded_graveyard.h"
#include "constants/card_effect_texts.h"
#include "graveyard_effects.h"

static const u8 sCoreGyPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsEligibleCoreReviveTarget(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ELEMENTAL_HERO_CORE)
    return FALSE;

  if (!Duel_IsElementalHeroCard(cardId))
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return gCardInfo.level <= 8;
}

static u8 OwnerHasEmptyMonsterZone(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

static s8 FindFirstEligibleGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    /* Core is top of GY when this effect fires; no second eligible card. */
    (void)top;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsEligibleCoreReviveTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 HasEligibleReviveTarget(u8 fixedDuelist)
{
  return FindFirstEligibleGyIndex(fixedDuelist) >= 0;
}

static u8 LoadEligibleGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsEligibleCoreReviveTarget(cardId))
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

static s8 PlayerPickGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 j;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  /* Always open the picker, even for a single eligible Fusion. */
  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sCoreGyPickLabels, ARRAY_COUNT(sCoreGyPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonEligibleFromGrave(u8 turnDuelist, u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsEligibleCoreReviveTarget(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

void MarkElementalHeroCoreDestroyedFromField(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_CORE)
    return;

  /* Hand discard often goes through Duel_DestroyZone — never arm from hand. */
  if (Duel_ZoneIsHandSlot(zone)) {
    gElementalHeroCoreRevivePending = FALSE;
    return;
  }

  /* Only monster-field destruction (battle or effect). */
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  gElementalHeroCoreRevivePending = TRUE;
}

void ClearElementalHeroCoreReviveIfHandSend(struct DuelCard *zone)
{
  if (zone != NULL && zone->id == ELEMENTAL_HERO_CORE && Duel_ZoneIsHandSlot(zone))
    gElementalHeroCoreRevivePending = FALSE;
}

/* Revive is resolved explicitly via ElementalHeroCore_TryResolveRevive after battle
 * finish — permanent-effect GY scan is unreliable on the opponent's turn. */
unsigned char ShouldActivateElementalHeroCore(void)
{
  return FALSE;
}

void ActivateElementalHeroCore(void)
{
}

void ElementalHeroCore_TryResolveRevive(void)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 gyIndex;
  u8 hideEffectText;

  if (gDeferGraveyardDrawBattleResolve)
    return;

  if (!gElementalHeroCoreRevivePending)
    return;

  if (gDuel.duelistbattleState[DUEL_PLAYER].graveyard == ELEMENTAL_HERO_CORE)
    fixedDuelist = DUEL_PLAYER;
  else if (gDuel.duelistbattleState[DUEL_OPPONENT].graveyard == ELEMENTAL_HERO_CORE)
    fixedDuelist = DUEL_OPPONENT;
  else
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);

  if (!OwnerHasEmptyMonsterZone(turnDuelist))
    return;

  if (!HasEligibleReviveTarget(fixedDuelist)) {
    gElementalHeroCoreRevivePending = FALSE;
    return;
  }

  gElementalHeroCoreRevivePending = FALSE;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(ELEMENTAL_HERO_CORE, CARD_EFFECT_TEXT_ELEMENTAL_HERO_CORE_POPUP_2);
  gHideEffectText = hideEffectText;

  if (IsDuelOver() == TRUE)
    return;

  /* Player GY picker only on the player's turn (opponent-turn UI freezes). */
  if (fixedDuelist == DUEL_PLAYER && WhoseTurn() == DUEL_PLAYER)
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  else
    gyIndex = FindFirstEligibleGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return;

  if (SpecialSummonEligibleFromGrave(turnDuelist, (u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;
}
