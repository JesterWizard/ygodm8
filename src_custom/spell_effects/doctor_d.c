#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sDestinyHeroArchetypeName[] APPEND_RODATA = "Destiny HERO";

static const u8 sDoctorDPickLabels[] APPEND_RODATA = {
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

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroArchetypeName);
}

static u8 CountDestinyHeroInGy(u8 fixedDuelist)
{
  u8 gyCount;
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsDestinyHeroMonster(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsDestinyHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 HasEmptyHandSlot(void)
{
  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

static u8 CanSpecialSummonRecover(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

static u8 CanActivateDoctorD(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (CountDestinyHeroInGy(fixedDuelist) < 2)
    return FALSE;

  return HasEmptyHandSlot() || CanSpecialSummonRecover();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = add to hand, FALSE = Special Summon. */
static u8 PlayerChoosesAddToHand(void)
{
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static u8 LoadDestinyHeroGyMenu(u8 fixedDuelist, u8 excludeGyIndex, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId;

    if (i == excludeGyIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsDestinyHeroMonster(cardId))
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

static s8 PlayerPickDestinyHeroGyIndex(u8 fixedDuelist, u8 excludeGyIndex)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadDestinyHeroGyMenu(fixedDuelist, excludeGyIndex, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sDoctorDPickLabels,
                                         ARRAY_COUNT(sDoctorDPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static s8 FindFirstDestinyHeroGyIndex(u8 fixedDuelist, u8 excludeGyIndex)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (i == excludeGyIndex)
      continue;
    if (IsDestinyHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 AddGraveyardCardToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
  if (cardId == CARD_NONE || !IsDestinyHeroMonster(cardId))
    return FALSE;

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

static enum DuelActionResult SpecialSummonFromGyIndex(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsDestinyHeroMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void DOCTOR_D_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 costIndex;
  s8 recoverIndex;
  u8 addToHand;
  u8 canHand;
  u8 canSs;

  if (!CanActivateDoctorD())
    return;

  Duel_ShowEffectText(DOCTOR_D);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    costIndex = PlayerPickDestinyHeroGyIndex(fixedDuelist, 0xFF);
  else
    costIndex = FindFirstDestinyHeroGyIndex(fixedDuelist, 0xFF);

  if (costIndex < 0)
    return;

  if (Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)costIndex) == CARD_NONE)
    return;

  GraveyardExpand_RefreshDisplay();

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    recoverIndex = PlayerPickDestinyHeroGyIndex(fixedDuelist, 0xFF);
  else
    recoverIndex = FindFirstDestinyHeroGyIndex(fixedDuelist, 0xFF);

  if (recoverIndex < 0)
    return;

  canHand = HasEmptyHandSlot();
  canSs = CanSpecialSummonRecover();

  if (canHand && canSs) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      addToHand = PlayerChoosesAddToHand();
    else
      addToHand = FALSE; /* AI prefers SS */
  } else {
    addToHand = canHand;
  }

  if (addToHand) {
    if (!AddGraveyardCardToHand(ACTIVE_DUELIST, (u8)recoverIndex))
      return;
  } else {
    if (SpecialSummonFromGyIndex((u8)recoverIndex) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();

}

APPEND_TEXT void EffectDOCTOR_D(void)
{
  if (!CanActivateDoctorD()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DOCTOR_D, DOCTOR_D_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DOCTOR_D_SelfCheck(void)
{
  if (!IsDestinyHeroMonster(DESTINY_HERO_DIAMOND_DUDE))
    while (1)
      ;
  if (IsDestinyHeroMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
