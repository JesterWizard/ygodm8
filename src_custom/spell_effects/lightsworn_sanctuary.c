#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

static const char sLightswornArchetypeName[] APPEND_RODATA = "Lightsworn";

static const u8 sSanctuaryPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornArchetypeName);
}

static u8 HandHasLightsworn(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLightswornMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static s8 PickLightswornHandZone(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsLightswornMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLightswornMonster(handRow[i]->id))
      return (s8)i;
  }

  return -1;
}

/* Exclude excludeGyIndex (the just-sent hand card) when looking for "other" LS. */
static u8 GyHasOtherLightsworn(u8 fixedDuelist, s8 excludeGyIndex)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    /* Legacy single-slot GY: after send, top is the sent card — no "other". */
    (void)excludeGyIndex;
    return FALSE;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if ((s8)i == excludeGyIndex)
      continue;
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstOtherLightswornGyIndex(u8 fixedDuelist, s8 excludeGyIndex)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if ((s8)i == excludeGyIndex)
      continue;
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadOtherLightswornGyMenu(u8 fixedDuelist, s8 excludeGyIndex, u8 *gyIndexMap)
{
  u8 menuCount = 0;
  u8 i;
  u8 gyCount;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled())
    return 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId;

    if ((s8)i == excludeGyIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsLightswornMonster(cardId))
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

static s8 PlayerPickOtherLightswornGyIndex(u8 fixedDuelist, s8 excludeGyIndex)
{
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 chosen;

  DECKMENU_SAVE();

  menuCount = LoadOtherLightswornGyMenu(fixedDuelist, excludeGyIndex, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosen = gyIndexMap[0];
    DECKMENU_RESTORE();
    return (s8)chosen;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sSanctuaryPickLabels,
                                         ARRAY_COUNT(sSanctuaryPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosen = gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return (s8)chosen;
}

static u8 AddLightswornFromGyToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsLightswornMonster(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static u8 CanActivateSanctuaryIgnition(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 i;
  u8 otherCount = 0;

  if (zone == NULL || zone->id != LIGHTSWORN_SANCTUARY || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (!HandHasLightsworn())
    return FALSE;

  /* Need room in hand after send (send frees a slot, so always room for add-back).
   * Need at least 1 Lightsworn already in GY before send ("other"). */
  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      otherCount++;
  }

  return otherCount > 0;
}

static void ResolveSanctuaryIgnition(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 handZone;
  s8 excludeGyIndex;
  s8 gyIndex;
  u16 sentId;

  if (!CanActivateSanctuaryIgnition(zone))
    return;

  Duel_ShowEffectText(LIGHTSWORN_SANCTUARY);

  if (IsDuelOver() == TRUE)
    return;

  handZone = PickLightswornHandZone();
  if (handZone < 0)
    return;

  sentId = gTurnHands[ACTIVE_DUELIST][handZone]->id;
  ClearZoneAndSendMonToGraveyard(gTurnHands[ACTIVE_DUELIST][handZone], ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  /* Just-sent card is typically the last GY entry. */
  excludeGyIndex = -1;
  if (GraveyardExpand_IsEnabled()) {
    u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);

    if (gyCount > 0
        && GraveyardExpand_GetCardAt(fixedDuelist, gyCount - 1) == sentId)
      excludeGyIndex = (s8)(gyCount - 1);
  }

  if (!GyHasOtherLightsworn(fixedDuelist, excludeGyIndex))
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    gyIndex = PlayerPickOtherLightswornGyIndex(fixedDuelist, excludeGyIndex);
  else
    gyIndex = FindFirstOtherLightswornGyIndex(fixedDuelist, excludeGyIndex);

  if (gyIndex < 0)
    return;

  if (!AddLightswornFromGyToHand(ACTIVE_DUELIST, (u8)gyIndex))
    return;

  zone->effectUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void LIGHTSWORN_SANCTUARY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateSanctuaryIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveSanctuaryIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);

  if (CanActivateSanctuaryIgnition(zone))
    ResolveSanctuaryIgnition(zone);
  else
    Duel_ShowEffectText(LIGHTSWORN_SANCTUARY);

  /* ponytail: Shine Counters on Deck→GY mill / remove 2 instead of destroy need
   * mill + destroy-gate + counter storage outside this file (DuelCard has no
   * shine-counter field). Ceiling: continuous face-up + OPT recycle only;
   * upgrade: mill hook → ++Shine; Duel_DestroyZone on Lightsworn → if counters
   * >= 2*n then counters -= 2*n and skip destroy. */
}

APPEND_TEXT void EffectLIGHTSWORN_SANCTUARY(void)
{
  /* ponytail: not in GetSpellType NORMAL override — face-up OPT re-activation
   * may need card_hooks GetSpellType + LIGHTSWORN_SANCTUARY listed. */
  if (Duel_TryResolveSpellThroughTraps(LIGHTSWORN_SANCTUARY, LIGHTSWORN_SANCTUARY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LIGHTSWORN_SANCTUARY_SelfCheck(void)
{
  if (!IsLightswornMonster(JAIN_LIGHTSWORN_PALADIN))
    while (1)
      ;
  if (IsLightswornMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
