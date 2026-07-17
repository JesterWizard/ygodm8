#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

extern u16 gNewButtons;
extern u16 gFilteredInput;
extern u16 gPressedButtons;

void UpdateFilteredInput_NoRepeat(void);
void DeckMenuSort(void);
unsigned IsPlayerDeckNonempty(void);
void RunPlayerDeckTask(u8 task);
void sub_801EF30(u8 task);
void sub_801F4A0(u8 task);
void sub_801F5F0(void);
void sub_801F5FC(void);
void sub_0801F62C(void);
void UpdateAllDuelGfx(void);

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 GraveyardHasSpell(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 CanReturnGraveyardSpellToHand(u8 turnDuelist)
{
  if (!GraveyardHasSpell(turnDuelist))
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
}

static u8 LoadGraveyardSpellMenu(u8 fixedDuelist, u8 *sourceIndexOut)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsSpellCard(cardId))
      continue;

    sourceIndexOut[menuCount] = i;
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

static u16 GraveyardSpellPickerProcessInput(void)
{
  u8 i;
  u16 mask;
  u16 ret = 0;

  UpdateFilteredInput_NoRepeat();

  mask = 1;
  for (i = 0; i < NUM_BUTTONS; i++) {
    if (mask & gNewButtons)
      ret = mask & gNewButtons;
    mask <<= 1;
  }

  mask = DPAD_RIGHT;
  for (i = 0; i < 4; i++) {
    if (mask & gFilteredInput)
      ret = mask & gFilteredInput;
    mask <<= 1;
  }

  if ((gFilteredInput & DPAD_UP) && (gPressedButtons & R_BUTTON))
    ret = DPAD_UP | R_BUTTON;
  if ((gFilteredInput & DPAD_DOWN) && (gPressedButtons & R_BUTTON))
    ret = DPAD_DOWN | R_BUTTON;

  return ret;
}

static s8 PickGraveyardSpellMenuIndex(void)
{
  u8 keepProcessing = TRUE;
  s8 selectedIndex = -1;

  if (IsPlayerDeckNonempty() != 1)
    return -1;

  DeckMenuSort();
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);

  while (keepProcessing) {
    switch (GraveyardSpellPickerProcessInput()) {
    case DPAD_UP:
      RunPlayerDeckTask(3);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case DPAD_UP | R_BUTTON:
      RunPlayerDeckTask(5);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case DPAD_DOWN:
      RunPlayerDeckTask(2);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case DPAD_DOWN | R_BUTTON:
      RunPlayerDeckTask(4);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case L_BUTTON:
      RunPlayerDeckTask(6);
      sub_801EF30(4);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case A_BUTTON:
      selectedIndex = (s8)gDeckMenu.currentPos;
      keepProcessing = FALSE;
      PlayMusic(SFX_SELECT);
      break;
    case B_BUTTON:
      keepProcessing = FALSE;
      PlayMusic(SFX_CANCEL);
      break;
    case 0:
    default:
      sub_801EF30(5);
      sub_0801F62C();
      sub_801F4A0(5);
      break;
    }

    if (IsPlayerDeckNonempty() != 1)
      keepProcessing = FALSE;
  }

  return selectedIndex;
}

static u8 ReturnGraveyardSpellToHand(u8 turnDuelist, u8 graveyardIndex)
{
  u16 cardId;
  s8 handZone;
  struct DuelCard *handSlot;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, graveyardIndex);
  if (!IsSpellCard(cardId))
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)(handZone));
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
  return TRUE;
}

static u8 PickGraveyardSpellIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  s8 i;

  for (i = (s8)gyCount - 1; i >= 0; i--) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
      return (u8)i;
  }

  return 0xFF;
}

static u8 TryReturnSelectedGraveyardSpell(u8 turnDuelist, u8 allowPlayerPicker)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 graveyardSpellSourceIndex[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;
  u8 graveyardIndex;

  DECKMENU_SAVE();

  menuCount = LoadGraveyardSpellMenu(fixedDuelist, graveyardSpellSourceIndex);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return FALSE;
  }

  if (WhoseTurn() == DUEL_PLAYER && turnDuelist == ACTIVE_DUELIST && allowPlayerPicker) {
    s8 menuIndex;

    menuIndex = PickGraveyardSpellMenuIndex();
    DECKMENU_RESTORE();

    if (menuIndex < 0)
      return FALSE;

    graveyardIndex = graveyardSpellSourceIndex[(u8)menuIndex];
    if (!ReturnGraveyardSpellToHand(turnDuelist, graveyardIndex))
      return FALSE;

    UpdateAllDuelGfx();
    return TRUE;
  }

  graveyardIndex = PickGraveyardSpellIndexForAi(fixedDuelist);
  DECKMENU_RESTORE();
  if (graveyardIndex == 0xFF)
    return FALSE;

  return ReturnGraveyardSpellToHand(turnDuelist, graveyardIndex);
}

unsigned char ShouldActivateDARK_MAGICIAN_OF_CHAOS(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != DARK_MAGICIAN_OF_CHAOS)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return CanReturnGraveyardSpellToHand(duelist);
}

void ActivateDARK_MAGICIAN_OF_CHAOS(void)
{
  u8 duelist;
  u8 hideEffectText;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowEffectTextTyped(DARK_MAGICIAN_OF_CHAOS, 8);
  gHideEffectText = hideEffectText;
  if (IsDuelOver() == TRUE)
    return;

  TryReturnSelectedGraveyardSpell(duelist, TRUE);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
