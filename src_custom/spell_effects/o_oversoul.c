#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

static const u8 sOversoulPickLabels[] APPEND_RODATA = {
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

static s8 FindFirstEligibleGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (IsElementalHeroNormalMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 CanActivateOOversoul(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return IsElementalHeroNormalMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard);

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

    if (!IsElementalHeroNormalMonster(cardId))
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

  menuCount = LoadEligibleGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0)
    return -1;

  if (menuCount == 1)
    return (s8)gyIndexMap[0];

  DECKMENU_SAVE();

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sOversoulPickLabels, ARRAY_COUNT(sOversoulPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonEligibleFromGrave(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsElementalHeroNormalMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsElementalHeroNormalMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void OOversoul_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  Duel_ShowEffectText(O_OVERSOUL);

  if (IsDuelOver() == TRUE || !CanActivateOOversoul())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    if (SpecialSummonEligibleFromGrave(0) == DUEL_ACTION_DUEL_OVER)
      return;
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  else
    gyIndex = FindFirstEligibleGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return;

  if (SpecialSummonEligibleFromGrave((u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectOOversoul(void)
{
  if (!CanActivateOOversoul()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(O_OVERSOUL, OOversoul_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void OOversoul_SelfCheck(void)
{
  if (IsElementalHeroNormalMonster(ELEMENTAL_HERO_SPARKMAN) == FALSE)
    while (1)
      ;
  if (IsElementalHeroNormalMonster(ELEMENTAL_HERO_BUBBLEMAN) == TRUE)
    while (1)
      ;
}
#endif
