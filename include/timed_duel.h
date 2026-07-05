#ifndef GUARD_TIMED_DUEL_H
#define GUARD_TIMED_DUEL_H

#include "gba/types.h"
#include "constants/duel_fields.h"
#include "duel.h"

#define TIMED_DUEL_PENDING_NONE 0xFF
#define TIMED_DUEL_COMPLETION_BYTES 16
#define TIMED_DUEL_BOARD_ROWS 4
#define TIMED_DUEL_GRAVEYARD_SLOTS 40

struct TimedDuelCardSlot {
  u16 cardId;
  u8 faceUp;
  u8 defending;
  s8 permStage;
};

struct TimedDuelLayout {
  struct TimedDuelCardSlot board[TIMED_DUEL_BOARD_ROWS][MAX_ZONES_IN_ROW];
  struct TimedDuelCardSlot hands[2][MAX_ZONES_IN_ROW];
  u16 graveyard[2][TIMED_DUEL_GRAVEYARD_SLOTS];
  u16 playerLp;
  u16 opponentLp;
  u8 field;
  u16 turnCount;     /* 0 = random 2..30 on the board HUD */
  u16 rewardCardId;
};

struct TimedDuelEntry {
  u8 opponentId;
  const struct TimedDuelLayout *layout;
};

extern u8 gTimedDuelActiveId;
extern u8 gDebugMenuPendingTimedDuelIndex;
extern u8 gTimedDuelCompletionFlags[TIMED_DUEL_COMPLETION_BYTES];
extern u8 gTimedDuelCompletionFlagsFlashPrimary[TIMED_DUEL_COMPLETION_BYTES];
extern u8 gTimedDuelCompletionFlagsFlashBackup[TIMED_DUEL_COMPLETION_BYTES];

u8 TimedDuel_GetCount(void);
const struct TimedDuelEntry *TimedDuel_GetEntry(u8 index);
const struct TimedDuelEntry *TimedDuel_GetActiveEntry(void);
const struct TimedDuelLayout *TimedDuel_GetActiveLayout(void);
void TimedDuel_FormatMenuTitle(u8 index, u8 *out);

u8 TimedDuel_IsActive(void);
u8 TimedDuel_IsCompleted(u8 index);
void TimedDuel_MarkCompleted(u8 index);

void TimedDuel_ApplySetupIfActive(void);
void TimedDuel_ApplyLifePointsIfActive(void);
u8 TimedDuel_ShouldSkipDrawPhase(u8 turnDuelist);
void TimedDuel_OnPlayerTurnEnded(void);

void TimedDuel_HandleWin(void);
void TimedDuel_OnDuelEnd(void);
void TimedDuel_RunAtIndex(u8 index);

void TimedDuel_LoadFromFlashPrimary(void);
void TimedDuel_LoadFromFlashBackup(void);
void TimedDuel_SaveToFlashPrimary(void);
void TimedDuel_SaveToFlashBackup(void);
void TimedDuel_ResetRuntime(void);
void TimedDuel_ResetOnNewGame(void);

#endif // GUARD_TIMED_DUEL_H
