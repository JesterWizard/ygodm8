#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "premature_burial.h"

static const u8 sPrematureBurialPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveDuelistHasLpForCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= PREMATURE_BURIAL_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= PREMATURE_BURIAL_LP_COST;
}

static struct DuelCard *FindSummonedMonsterZone(u16 monsterId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == monsterId)
      return zone;
  }

  return NULL;
}

static s8 FindFirstEligibleGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (IsMonsterCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
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

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sPrematureBurialPickLabels, ARRAY_COUNT(sPrematureBurialPickLabels))) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

u8 CanActivatePrematureBurial(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!ActiveDuelistHasLpForCost())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return IsMonsterCard(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard);

  return FindFirstEligibleGyIndex(fixedDuelist) >= 0;
}

static enum DuelActionResult SpecialSummonMonsterFromGraveIndex(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsMonsterCard(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsMonsterCard(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void PrematureBurial_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;
  u16 monsterId;
  struct DuelCard *summonedZone;

  Duel_ShowEffectText(PREMATURE_BURIAL);

  if (IsDuelOver() == TRUE || !CanActivatePrematureBurial())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -PREMATURE_BURIAL_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE || !CanActivatePrematureBurial())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  } else {
    gyIndex = FindFirstEligibleGyIndex(fixedDuelist);
  }

  if (gyIndex < 0)
    return;

  if (!GraveyardExpand_IsEnabled())
    monsterId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
  else
    monsterId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);

  if (!IsMonsterCard(monsterId))
    return;

  if (SpecialSummonMonsterFromGraveIndex((u8)gyIndex) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  summonedZone = FindSummonedMonsterZone(monsterId);
  if (summonedZone == NULL)
    return;

  if (!RegisterDynamicEquip(spellZone, summonedZone, PREMATURE_BURIAL, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
}

APPEND_TEXT void EffectPrematureBurial(void)
{
  if (!CanActivatePrematureBurial()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(PREMATURE_BURIAL, PREMATURE_BURIAL_LP_COST,
                                         PrematureBurial_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
