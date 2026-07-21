#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

static const u8 sShallowGravePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 TurnDuelistHasEmptyMonsterZone(u8 turnDuelist)
{
  return FirstEmptyZoneInRow(gTurnZones[Duel_TurnMonsterRowForDuelist(turnDuelist)]) >= 0;
}

static s8 FindFirstMonsterGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u8 turnDuelist =
        (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
            ? ACTIVE_DUELIST
            : INACTIVE_DUELIST;

    if (IsMonsterCard(gTurnDuelistBattleState[turnDuelist]->graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsMonsterCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 TurnDuelistCanShallowGrave(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (!TurnDuelistHasEmptyMonsterZone(turnDuelist))
    return FALSE;

  return FindFirstMonsterGyIndex(fixedDuelist) >= 0;
}

u8 CanActivateTHE_SHALLOW_GRAVE(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return TurnDuelistCanShallowGrave(ACTIVE_DUELIST)
      && TurnDuelistCanShallowGrave(INACTIVE_DUELIST);
}

static u8 LoadMonsterGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

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

static s8 PlayerPickMonsterGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadMonsterGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sShallowGravePickLabels,
                                         ARRAY_COUNT(sShallowGravePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonFaceDownDefFromGrave(u8 turnDuelist, u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 monsterRow = Duel_TurnMonsterRowForDuelist(turnDuelist);
  s8 emptyZone;
  u16 cardId;
  enum DuelActionResult result;
  struct DuelCard *zone;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (emptyZone < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;
    if (!IsMonsterCard(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    opts.mode = DUEL_SUMMON_NORMAL_SET;
    result = Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
    if (!IsMonsterCard(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    opts.mode = DUEL_SUMMON_NORMAL_SET;
    result = Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
  }

  if (result != DUEL_ACTION_OK)
    return result;

  zone = gTurnZones[monsterRow][emptyZone];
  if (zone != NULL && zone->id != CARD_NONE) {
    zone->unk4 = 2;
    zone->isFaceUp = FALSE;
    zone->isDefending = TRUE;
    FlipCardFaceDown(zone);
  }

  return DUEL_ACTION_OK;
}

static s8 PickGyIndexForTurnDuelist(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (!GraveyardExpand_IsEnabled())
    return 0;

  /* Player only chooses when it is their own GY on their turn. */
  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText
      && FixedDuelistForTurnDuelist(ACTIVE_DUELIST) == DUEL_PLAYER
      && turnDuelist == ACTIVE_DUELIST)
    return PlayerPickMonsterGyIndex(fixedDuelist);

  return FindFirstMonsterGyIndex(fixedDuelist);
}

static void THE_SHALLOW_GRAVE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  s8 activeGyIndex;
  s8 inactiveGyIndex;

  Duel_ShowEffectText(THE_SHALLOW_GRAVE);

  if (IsDuelOver() == TRUE || !CanActivateTHE_SHALLOW_GRAVE())
    return;

  activeGyIndex = PickGyIndexForTurnDuelist(ACTIVE_DUELIST);
  if (activeGyIndex < 0)
    return;

  inactiveGyIndex = PickGyIndexForTurnDuelist(INACTIVE_DUELIST);
  if (inactiveGyIndex < 0)
    return;

  if (SpecialSummonFaceDownDefFromGrave(ACTIVE_DUELIST, (u8)activeGyIndex)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (SpecialSummonFaceDownDefFromGrave(INACTIVE_DUELIST, (u8)inactiveGyIndex)
      == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectTHE_SHALLOW_GRAVE(void)
{
  if (!CanActivateTHE_SHALLOW_GRAVE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_SHALLOW_GRAVE, THE_SHALLOW_GRAVE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
