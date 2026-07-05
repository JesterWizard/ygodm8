#include "global.h"
#include "card.h"
#include "configs/runtime.h"
#include "duel.h"
#include "duel_b_menu.h"
#include "expanded_graveyard.h"
#include "removed_from_play.h"

extern u16 gNewButtons;
extern u16 gFilteredInput;
extern u16 gPressedButtons;

void UpdateFilteredInput_NoRepeat(void);
void DeckMenuSort(void);
void ToggleDeckSortMode(void);
unsigned IsPlayerDeckNonempty(void);
void RunPlayerDeckTask(u8 task);
void sub_801EF30(u8 task);
void sub_801F4A0(u8 task);
void sub_801F5F0(void);
void sub_801F5FC(void);
void sub_801F120(void);
void sub_801F630(void);
void sub_801F644(void);
void sub_0801F62C(void);
u16 GetSelectedCardWithOffset(u8 offset);
void SetCardInfoWithWarning(u16 *id);
void ShowCardDetailView(void);

static u16 CardListViewerProcessInput(void)
{
  u8 i;
  u16 mask;
  u16 ret;

  ret = 0;
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

static void CardListViewerInitGraphics(void)
{
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);
}

static void CardListViewerRestoreAfterCardDetails(void)
{
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);
  sub_801F5FC();
  sub_801EF30(3);
  sub_801F4A0(4);
  WaitForVBlank();
  LoadCharblock1();
}

static void CardListViewerShowSelectedCardDetails(void)
{
  u16 cardId;

  cardId = GetSelectedCardWithOffset(2);
  SetCardInfoWithWarning(&cardId);
  PlayMusic(SFX_SELECT);
  ShowCardDetailView();
  CardListViewerRestoreAfterCardDetails();
}

static void CardListViewerMain(void)
{
  u8 keepProcessing;

  if (IsPlayerDeckNonempty() != 1)
    return;

  DeckMenuSort();
  CardListViewerInitGraphics();
  keepProcessing = TRUE;
  while (keepProcessing) {
    switch (CardListViewerProcessInput()) {
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
        CardListViewerShowSelectedCardDetails();
        sub_801F4A0(7);
        break;
      case B_BUTTON:
        keepProcessing = FALSE;
        PlayMusic(SFX_CANCEL);
        break;
      case START_BUTTON:
        sub_801F120();
        sub_801EF30(7);
        sub_801F4A0(9);
        sub_801F644();
        break;
      case SELECT_BUTTON:
        ToggleDeckSortMode();
        sub_801EF30(6);
        PlayMusic(SFX_SELECT);
        sub_801F4A0(8);
        sub_801F630();
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
}

static void CardListViewerOpenLoaded(u8 cardCount)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;

  if (cardCount == 0) {
    PlayMusic(SFX_FORBIDDEN);
    return;
  }

  for (i = 0; i < sizeof(gDeckMenu); i++)
    savedDeckMenu[i] = ((u8 *)&gDeckMenu)[i];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = cardCount;
  PlayMusic(SFX_SELECT);
  CardListViewerMain();

  for (i = 0; i < sizeof(gDeckMenu); i++)
    ((u8 *)&gDeckMenu)[i] = savedDeckMenu[i];
}

static void CardListViewerLoadCards(u8 fixedDuelist, u8 count, u8 capacity,
                                    u16 (*getCardAt)(u8, u8))
{
  u8 i;

  for (i = 0; i < capacity; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < count; i++)
    gDeckMenu.cards[i] = getCardAt(fixedDuelist, i);

  CardListViewerOpenLoaded(count);
}

void Duel_GraveyardViewer_Open(u8 fixedDuelist)
{
  if (gRuntimeConfig.expand_graveyard != TRUE)
    return;

  CardListViewerLoadCards(fixedDuelist, GraveyardExpand_GetCount(fixedDuelist),
                          EXPANDED_GRAVEYARD_CAPACITY, GraveyardExpand_GetCardAt);
}

void Duel_RemovedFromPlayViewer_Open(u8 fixedDuelist)
{
  if (RemovedFromPlay_IsEnabled() != TRUE)
    return;

  CardListViewerLoadCards(fixedDuelist, RemovedFromPlay_GetCount(fixedDuelist),
                          REMOVED_FROM_PLAY_CAPACITY, RemovedFromPlay_GetCardAt);
}
