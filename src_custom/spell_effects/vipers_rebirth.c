#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"
#include "synchro_duel.h"
#include "vipers_rebirth.h"

static const u8 sVipersRebirthPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sVipersStampRow APPEND_DATA = {0xFF};
static u8 sVipersStampCol APPEND_DATA = {0xFF};
static u16 sVipersStampId APPEND_DATA = {CARD_NONE};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 IsEligibleVipersTarget(u16 cardId)
{
  if (!IsReptileMonster(cardId))
    return FALSE;

  return !Card_IsTuner(cardId);
}

static u8 GyMonstersAllReptile(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;
  u8 sawMonster = FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (top == CARD_NONE || GetTypeGroup(top) != TYPE_GROUP_MONSTER)
      return FALSE;

    return IsReptileMonster(top);
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    sawMonster = TRUE;
    if (!IsReptileMonster(cardId))
      return FALSE;
  }

  return sawMonster;
}

static s8 FindFirstEligibleGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsEligibleVipersTarget(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsEligibleVipersTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

u8 CanActivateVIPERS_REBIRTH(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GyMonstersAllReptile(fixedDuelist))
    return FALSE;

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

    if (!IsEligibleVipersTarget(cardId))
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
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleGyMenu(fixedDuelist, gyIndexMap);
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
          sVipersRebirthPickLabels, ARRAY_COUNT(sVipersRebirthPickLabels))) {
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
    if (!IsEligibleVipersTarget(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsEligibleVipersTarget(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void VIPERS_REBIRTH_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  Duel_ShowEffectText(VIPERS_REBIRTH);

  if (IsDuelOver() == TRUE || !CanActivateVIPERS_REBIRTH())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    if (SpecialSummonEligibleFromGrave(0) == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      gyIndex = PlayerPickGyIndex(fixedDuelist);
    else
      gyIndex = FindFirstEligibleGyIndex(fixedDuelist);

    if (gyIndex < 0)
      return;

    if (SpecialSummonEligibleFromGrave((u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  {
    u8 col;
    u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && IsEligibleVipersTarget(zone->id)) {
        VipersRebirth_StampSummonedZone(zone);
        break;
      }
    }
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

void VipersRebirth_StampSummonedZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  sVipersStampRow = fixedRow;
  sVipersStampCol = fixedCol;
  sVipersStampId = zone->id;
}

void TryApplyVipersRebirthEndPhase(void)
{
  struct DuelCard *zone;

  if (sVipersStampRow > PLAYER_MONSTER_ROW || sVipersStampCol >= MAX_ZONES_IN_ROW) {
    sVipersStampRow = 0xFF;
    sVipersStampCol = 0xFF;
    sVipersStampId = CARD_NONE;
    return;
  }

  zone = gFixedZones[sVipersStampRow][sVipersStampCol];
  if (zone != NULL && zone->id == sVipersStampId && zone->id != CARD_NONE)
    Duel_DestroyZone(zone, Duel_FixedDuelistForMonsterRow(sVipersStampRow), TRUE);

  sVipersStampRow = 0xFF;
  sVipersStampCol = 0xFF;
  sVipersStampId = CARD_NONE;
}

APPEND_TEXT void EffectVIPERS_REBIRTH(void)
{
  if (!CanActivateVIPERS_REBIRTH()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(VIPERS_REBIRTH, VIPERS_REBIRTH_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
