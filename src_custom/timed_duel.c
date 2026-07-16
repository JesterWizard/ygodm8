#include "global.h"
#include "configs/runtime.h"
#include "timed_duel.h"
#include "debug_menu_timed_duel_layouts.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "duel.h"
#include "duel_main.h"
#include "duel_status.h"
#include "expanded_graveyard.h"
#include "overworld.h"

#define TIMED_DUEL_ENTRY(layoutSym, opponent) \
  { (opponent), &(layoutSym) },

#define TIMED_DUEL_DEFAULT_SECONDS 60
#define TIMED_DUEL_FRAMES_PER_SECOND 60

static const struct TimedDuelEntry sTimedDuels[] APPEND_RODATA = {
#include "debug/debug_menu_timed_duel_table.inc"
};

#undef TIMED_DUEL_ENTRY

extern void ClearZone(struct DuelCard *zone);
extern void AddCardQtyToTrunk(unsigned cardId, unsigned quantity);
extern void SetCardInfo(u16 cardId);
extern void ShowCardDetailView(void);
extern void DisplayDuelText(struct DuelText *duelText);
extern void ResetDuelTextData(struct DuelText *duelText);
extern int sub_80588C4(u8 *, int, int);
extern void (*g20245AC)(int, u8 *, int);
extern void DeclareLoser(unsigned char);
extern u16 gDuelBoardTurnCount;
extern u16 gTimedDuelTimerFrames;
extern void RefreshDuelBoardTurnHud(void);

static const struct TimedDuelEntry *TimedDuel_EntryForIndex(u8 index) {
  if (index >= ARRAY_COUNT(sTimedDuels))
    return NULL;
  return &sTimedDuels[index];
}

u8 TimedDuel_GetCount(void) {
  return ARRAY_COUNT(sTimedDuels);
}

const struct TimedDuelEntry *TimedDuel_GetEntry(u8 index) {
  return TimedDuel_EntryForIndex(index);
}

const struct TimedDuelEntry *TimedDuel_GetActiveEntry(void) {
  if (gTimedDuelActiveId == 0)
    return NULL;
  return TimedDuel_EntryForIndex(gTimedDuelActiveId - 1);
}

const struct TimedDuelLayout *TimedDuel_GetActiveLayout(void) {
  const struct TimedDuelEntry *entry;

  entry = TimedDuel_GetActiveEntry();
  if (entry == NULL)
    return NULL;
  return entry->layout;
}

void TimedDuel_FormatMenuTitle(u8 index, u8 *out) {
  u8 i;
  u8 n;

  out[0] = 'T';
  out[1] = 'i';
  out[2] = 'm';
  out[3] = 'e';
  out[4] = 'd';
  out[5] = ' ';
  out[6] = 'D';
  out[7] = 'u';
  out[8] = 'e';
  out[9] = 'l';
  out[10] = ' ';
  i = 11;
  n = index + 1;
  if (n >= 10) {
    out[i++] = (u8)('0' + n / 10);
    out[i++] = (u8)('0' + n % 10);
  } else {
    out[i++] = (u8)('0' + n);
  }
  out[i] = '\0';
}

u8 TimedDuel_IsActive(void) {
  return gTimedDuelActiveId != 0;
}

u8 TimedDuel_IsCompleted(u8 index) {
  u8 byteIndex;
  u8 bitMask;

  if (index >= TimedDuel_GetCount())
    return FALSE;
  byteIndex = index / 8;
  bitMask = 1 << (index % 8);
  return (gTimedDuelCompletionFlags[byteIndex] & bitMask) != 0;
}

void TimedDuel_MarkCompleted(u8 index) {
  u8 byteIndex;
  u8 bitMask;

  if (index >= TimedDuel_GetCount())
    return;
  byteIndex = index / 8;
  bitMask = 1 << (index % 8);
  gTimedDuelCompletionFlags[byteIndex] |= bitMask;
}

static void TimedDuel_ApplyCardSlot(struct DuelCard *slot, const struct TimedDuelCardSlot *spec) {
  ClearZone(slot);
  if (spec->cardId == CARD_NONE)
    return;
  slot->id = spec->cardId;
  slot->isFaceUp = spec->faceUp;
  slot->isDefending = spec->defending;
  slot->permStage = spec->permStage;
}

static void TimedDuel_ApplyGraveyardStacks(const struct TimedDuelLayout *layout) {
  u8 duelist;

  if (GraveyardExpand_IsEnabled() == TRUE) {
    GraveyardExpand_LoadStacks((const u16 *)layout->graveyard);
    GraveyardExpand_SyncAllLegacyTops();
    GraveyardExpand_RefreshDisplay();
    return;
  }

  for (duelist = 0; duelist < 2; duelist++) {
    u8 i;
    u16 top = CARD_NONE;

    for (i = 0; i < TIMED_DUEL_GRAVEYARD_SLOTS; i++) {
      if (layout->graveyard[duelist][i] == CARD_NONE)
        break;
      top = layout->graveyard[duelist][i];
    }
    gDuel.duelistbattleState[duelist].graveyard = top;
  }
}

void TimedDuel_ApplySetupIfActive(void) {
  const struct TimedDuelEntry *entry;
  const struct TimedDuelLayout *layout;
  u8 row;
  u8 col;

  entry = TimedDuel_GetActiveEntry();
  if (entry == NULL || entry->layout == NULL)
    return;

  layout = entry->layout;
  gWhoseTurn = DUEL_PLAYER;
  gDuel.field = layout->field < NUM_FIELDS ? layout->field : FIELD_NONE;

  for (row = 0; row < TIMED_DUEL_BOARD_ROWS; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      TimedDuel_ApplyCardSlot(&gDuel.board[row][col], &layout->board[row][col]);
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    TimedDuel_ApplyCardSlot(&gDuel.hands[DUEL_PLAYER][col], &layout->hands[DUEL_PLAYER][col]);
    TimedDuel_ApplyCardSlot(&gDuel.hands[DUEL_OPPONENT][col], &layout->hands[DUEL_OPPONENT][col]);
  }

  TimedDuel_ApplyGraveyardStacks(layout);
  TimedDuel_ApplyLifePointsIfActive();
}

void TimedDuel_ApplyLifePointsIfActive(void) {
  const struct TimedDuelLayout *layout;

  if (!TimedDuel_IsActive())
    return;
  layout = TimedDuel_GetActiveLayout();
  if (layout == NULL)
    return;

  gDuelLifePoints[DUEL_PLAYER] = layout->playerLp;
  gDuelLifePoints[DUEL_OPPONENT] = layout->opponentLp;
  gUnk2023EA0.unk0[DUEL_PLAYER].initialLifePoints = layout->playerLp;
  gUnk2023EA0.unk0[DUEL_PLAYER].lifePointsAfterDamage = layout->playerLp;
  gUnk2023EA0.unk0[DUEL_OPPONENT].initialLifePoints = layout->opponentLp;
  gUnk2023EA0.unk0[DUEL_OPPONENT].lifePointsAfterDamage = layout->opponentLp;
}

u8 TimedDuel_ShouldSkipDrawPhase(u8 turnDuelist) {
  if (!TimedDuel_IsActive())
    return FALSE;
  return turnDuelist == DUEL_PLAYER;
}

void TimedDuel_OnPlayerTurnEnded(void) {
  if (!TimedDuel_IsActive())
    return;
  if (IsDuelOver() == TRUE)
    return;
  DeclareLoser(DUEL_PLAYER);
}

void TimedDuel_OnVBlank(void) {
  if (!TimedDuel_IsActive())
    return;
  if (IsDuelOver() == TRUE)
    return;

  gTimedDuelTimerFrames++;
  if (gTimedDuelTimerFrames < TIMED_DUEL_FRAMES_PER_SECOND)
    return;

  gTimedDuelTimerFrames = 0;
  if (gDuelBoardTurnCount > 0)
    gDuelBoardTurnCount--;

  RefreshDuelBoardTurnHud();

  if (gDuelBoardTurnCount == 0)
    DeclareLoser(DUEL_PLAYER);
}

void TimedDuel_HandleWin(void) {
  const struct TimedDuelLayout *layout;
  struct DuelText duelText;
  u8 index;
  u16 rewardCardId;

  layout = TimedDuel_GetActiveLayout();
  if (layout == NULL)
    return;

  index = gTimedDuelActiveId - 1;
  rewardCardId = layout->rewardCardId;
  TimedDuel_MarkCompleted(index);
  AddCardQtyToTrunk(rewardCardId, 1);

  if (gDuelData.unk2d) {
    PlayMusic(gDuelData.winMusic);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_DUEL_VICTORY;
    DisplayDuelText(&duelText);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_CARD_OBTAINED;
    duelText.unk0 = rewardCardId;
    DisplayDuelText(&duelText);
    SetCardInfo(rewardCardId);
    ShowCardDetailView();
  }

  TimedDuel_OnDuelEnd();
}

void TimedDuel_OnDuelEnd(void) {
  gTimedDuelActiveId = 0;
  gTimedDuelTimerFrames = 0;
}

void TimedDuel_RunAtIndex(u8 index) {
  const struct TimedDuelEntry *entry;

  entry = TimedDuel_GetEntry(index);
  if (entry == NULL || TimedDuel_IsCompleted(index) == TRUE)
    return;

  gTimedDuelActiveId = index + 1;
  gDuelData.opponent = entry->opponentId;
  gDuelData.unk2A = 0;
  gDuelData.moneyReward = 0;
  gDuelData.capacityYield = 0;

  DuelMain();
  TimedDuel_OnDuelEnd();
}

static void TimedDuel_LoadFromFlash(int address) {
  if (g20245AC == NULL)
    return;
  g20245AC(address, gTimedDuelCompletionFlags, TIMED_DUEL_COMPLETION_BYTES);
}

void TimedDuel_LoadFromFlashPrimary(void) {
  TimedDuel_LoadFromFlash((int)&gTimedDuelCompletionFlagsFlashPrimary);
}

void TimedDuel_LoadFromFlashBackup(void) {
  TimedDuel_LoadFromFlash((int)&gTimedDuelCompletionFlagsFlashBackup);
}

void TimedDuel_SaveToFlashPrimary(void) {
  sub_80588C4(gTimedDuelCompletionFlags, (int)&gTimedDuelCompletionFlagsFlashPrimary,
              TIMED_DUEL_COMPLETION_BYTES);
}

void TimedDuel_SaveToFlashBackup(void) {
  sub_80588C4(gTimedDuelCompletionFlags, (int)&gTimedDuelCompletionFlagsFlashBackup,
              TIMED_DUEL_COMPLETION_BYTES);
}

void TimedDuel_ResetRuntime(void) {
  gTimedDuelActiveId = 0;
  gDebugMenuPendingTimedDuelIndex = TIMED_DUEL_PENDING_NONE;
  gTimedDuelTimerFrames = 0;
}

void TimedDuel_ResetOnNewGame(void) {
  u8 i;

  for (i = 0; i < TIMED_DUEL_COMPLETION_BYTES; i++)
    gTimedDuelCompletionFlags[i] = 0;
  TimedDuel_ResetRuntime();
}

u16 TimedDuel_ResolveTimerSeconds(const struct TimedDuelLayout *layout) {
  if (layout == NULL || layout->timerSeconds == 0)
    return TIMED_DUEL_DEFAULT_SECONDS;
  return layout->timerSeconds;
}
