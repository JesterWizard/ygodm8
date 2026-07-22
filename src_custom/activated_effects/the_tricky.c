#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;

#define PLAYER_HAND_ROW 4

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 HasTrickyDiscardCost(struct DuelCard **handRow, u8 summonZone)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (i != summonZone && handRow[i]->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 HandZoneIsTrickyDiscardCost(struct DuelCard **handRow, u8 handZone, u8 summonZone)
{
  return handZone != summonZone && SixCardHand_ZoneAtHandRow(handRow, handZone)->id != CARD_NONE;
}

static s8 FindFirstTrickyDiscardZone(struct DuelCard **handRow, u8 summonZone)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (HandZoneIsTrickyDiscardCost(handRow, i, summonZone))
      return (s8)i;
  }

  return -1;
}

static s8 PickTrickyDiscardZoneForAi(struct DuelCard **handRow, u8 summonZone)
{
  s8 i;
  s8 trickyFallback = -1;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (!HandZoneIsTrickyDiscardCost(handRow, (u8)i, summonZone))
      continue;

    if (handRow[i]->id != THE_TRICKY)
      return i;

    trickyFallback = i;
  }

  return trickyFallback;
}

/* discard pick excludes summon slot; upgrade path: exchange_hand_selection helper */
static s8 SelectTrickyDiscardZone(struct DuelCard **handRow, u8 summonZone)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 running;
  s8 firstZone;

  firstZone = FindFirstTrickyDiscardZone(handRow, summonZone);
  if (firstZone < 0)
    return -1;

  InitButtonMaps();
  gDuelCursor.currentY = PLAYER_HAND_ROW;
  gDuelCursor.destY = PLAYER_HAND_ROW;
  gDuelCursor.currentX = (u8)firstZone;
  gDuelCursor.destX = gDuelCursor.currentX;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, PLAYER_HAND_ROW);

  WaitForNoButtonsHeld();
  InitButtonMaps();

  running = TRUE;
  while (running) {
    scrollY = gDuelCursor.currentY;
    UpdateFilteredInput_WithRepeat();

    if (gRepeatedOrNewButtons & DPAD_LEFT) {
      MoveCursorLeft();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
      MoveCursorRight();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gNewButtons & A_BUTTON) {
      if (HandZoneIsTrickyDiscardCost(handRow, gDuelCursor.currentX, summonZone)) {
        PlayMusic(SFX_SELECT);
        running = FALSE;
      } else {
        PlayMusic(SFX_FORBIDDEN);
      }
    }

    WaitForVBlank();
  }

  return (s8)gDuelCursor.currentX;
}

static u8 DiscardTrickyCost(struct DuelCard **handRow, u8 summonZone)
{
  s8 discardZone;

  if (WhoseTurn() == DUEL_PLAYER)
    discardZone = SelectTrickyDiscardZone(handRow, summonZone);
  else
    discardZone = PickTrickyDiscardZoneForAi(handRow, summonZone);

  if (discardZone < 0)
    return FALSE;

  ClearZoneAndSendMonToGraveyard(handRow[discardZone], ACTIVE_DUELIST);
  return IsDuelOver() != TRUE;
}

u8 CanSpecialSummonTheTrickyFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != THE_TRICKY)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HasTrickyDiscardCost(handRow, handZone);
}

u8 TrySpecialSummonTheTrickyFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonTheTrickyFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(THE_TRICKY, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!DiscardTrickyCost(handRow, handZone))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != THE_TRICKY)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  return TRUE;
}
