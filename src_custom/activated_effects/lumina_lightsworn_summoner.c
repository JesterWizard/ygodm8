#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "lumina_lightsworn_summoner.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static const u8 sLuminaPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 IsTargetableLightswornGyMonster(u16 cardId)
{
  if (!IsLightswornMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.level > 4)
    return FALSE;

  return !Duel_CardCannotBeSpecialSummoned(cardId);
}

static u8 GyHasTargetableLightsworn(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsTargetableLightswornGyMonster(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsTargetableLightswornGyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadTargetableLightswornGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsTargetableLightswornGyMonster(cardId))
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

static s8 FindBestTargetableLightswornGyIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsTargetableLightswornGyMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static s8 PlayerPickTargetableLightswornGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadTargetableLightswornGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sLuminaPickLabels,
                                         ARRAY_COUNT(sLuminaPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonLightswornFromGy(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsTargetableLightswornGyMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsTargetableLightswornGyMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtTurn(ACTIVE_DUELIST, gyIndex);
  if (!IsTargetableLightswornGyMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateLUMINA_LIGHTSWORN_SUMMONER(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;

  if (gMonEffect.id != LUMINA_LIGHTSWORN_SUMMONER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LUMINA_LIGHTSWORN_SUMMONER)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  return GyHasTargetableLightsworn(fixedDuelist);
}

void ActivateLUMINA_LIGHTSWORN_SUMMONEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  s8 gyIndex;

  Duel_ShowEffectTextTyped(LUMINA_LIGHTSWORN_SUMMONER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0
      || !GyHasTargetableLightsworn(fixedDuelist))
    return;

  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickTargetableLightswornGyIndex(fixedDuelist);
  else if (GraveyardExpand_IsEnabled())
    gyIndex = FindBestTargetableLightswornGyIndexForAi(fixedDuelist);
  else
    gyIndex = 0;

  if (gyIndex < 0)
    return;

  if (SpecialSummonLightswornFromGy((u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}

#define LUMINA_END_PHASE_MILL 3

void TryApplyLuminaEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != LUMINA_LIGHTSWORN_SUMMONER)
      continue;

    Duel_ShowEffectTextTyped(LUMINA_LIGHTSWORN_SUMMONER, 2);
    Duel_MillTopDeckCards(turn, LUMINA_END_PHASE_MILL, TRUE);
    return;
  }
}
