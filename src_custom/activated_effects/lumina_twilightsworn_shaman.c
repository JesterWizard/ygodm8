#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);

extern const CardData gCardData_NEW[];
extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";
static const u8 sTwilightPickLabels[] APPEND_RODATA = {
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

static u8 IsBanishableLightswornCost(u16 cardId)
{
  return IsLightswornMonster(cardId) && cardId != LUMINA_TWILIGHTSWORN_SHAMAN;
}

static u8 IsTargetableBanishedLightsworn(u16 cardId)
{
  if (!IsBanishableLightswornCost(cardId))
    return FALSE;

  return !Duel_CardCannotBeSpecialSummoned(cardId);
}

static u8 HandHasBanishableLightsworn(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsBanishableLightswornCost(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasBanishableLightsworn(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsBanishableLightswornCost(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsBanishableLightswornCost(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 RfpHasTargetableLightsworn(u8 fixedDuelist)
{
  u8 i;
  u8 count;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (IsTargetableBanishedLightsworn(RemovedFromPlay_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 BanishOneLightswornFromHandOrGy(void)
{
  u8 col;
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = gTurnHands[ACTIVE_DUELIST][col];

    if (!IsBanishableLightswornCost(slot->id))
      continue;

    if (Duel_BanishZone(slot, TRUE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    return TRUE;
  }

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (!IsBanishableLightswornCost(cardId))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (!IsBanishableLightswornCost(cardId))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    return TRUE;
  }

  return FALSE;
}

static u8 LoadBanishedLightswornMenu(u8 fixedDuelist, u8 *rfpIndexMap)
{
  u8 rfpCount = RemovedFromPlay_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < rfpCount; i++) {
    u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

    if (!IsTargetableBanishedLightsworn(cardId))
      continue;

    rfpIndexMap[menuCount] = i;
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

static s8 FindBestBanishedLightswornIndex(u8 fixedDuelist)
{
  u8 rfpCount = RemovedFromPlay_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < rfpCount; i++) {
    u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsTargetableBanishedLightsworn(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static s8 PlayerPickBanishedLightswornIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 rfpIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenIndex;

  DECKMENU_SAVE();

  menuCount = LoadBanishedLightswornMenu(fixedDuelist, rfpIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenIndex = (s8)rfpIndexMap[0];
    DECKMENU_RESTORE();
    return chosenIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sTwilightPickLabels,
                                         ARRAY_COUNT(sTwilightPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenIndex = (s8)rfpIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenIndex;
}

/* ponytail: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. */
static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  u8 count;
  u8 i;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  if (index >= count)
    return;

  for (i = index + 1; i < count; i++)
    gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];

  gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
}

static enum DuelActionResult SpecialSummonBanishedLightsworn(u8 fixedDuelist, u8 index)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;

  cardId = RemovedFromPlay_GetCardAt(fixedDuelist, index);
  if (!IsTargetableBanishedLightsworn(cardId))
    return DUEL_ACTION_NO_TARGET;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return DUEL_ACTION_BLOCKED;

  RemoveBanishedAt(fixedDuelist, index);
  return DUEL_ACTION_OK;
}

unsigned char CanActivateLUMINA_TWILIGHTSWORN_SHAMAN(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;

  if (gMonEffect.id != LUMINA_TWILIGHTSWORN_SHAMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LUMINA_TWILIGHTSWORN_SHAMAN)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  if (!RfpHasTargetableLightsworn(fixedDuelist))
    return FALSE;

  return HandHasBanishableLightsworn() || GyHasBanishableLightsworn(fixedDuelist);
}

void ActivateLUMINA_TWILIGHTSWORN_SHAMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  s8 rfpIndex;

  Duel_ShowEffectTextTyped(LUMINA_TWILIGHTSWORN_SHAMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE || !RemovedFromPlay_IsEnabled())
    return;

  if (!BanishOneLightswornFromHandOrGy())
    return;

  if (IsDuelOver() == TRUE || !RfpHasTargetableLightsworn(fixedDuelist))
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    rfpIndex = PlayerPickBanishedLightswornIndex(fixedDuelist);
  else
    rfpIndex = FindBestBanishedLightswornIndex(fixedDuelist);

  if (rfpIndex < 0)
    return;

  if (SpecialSummonBanishedLightsworn(fixedDuelist, (u8)rfpIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: EP mill 3 on other LS effect needs End Phase / LS trigger hook. */
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
