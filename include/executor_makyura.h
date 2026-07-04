#ifndef GUARD_EXECUTOR_MAKYURA_H
#define GUARD_EXECUTOR_MAKYURA_H

void ResetExecutorMakyuraTurnState(void);
void TryArmExecutorMakyuraOnGraveyardSendFixed(u8 fixedDuelist, u16 cardId);
void TryArmExecutorMakyuraOnGraveyardSend(u8 turnDuelist, u16 cardId);
void TryShowPendingExecutorMakyuraPopup(void);
u8 IsExecutorMakyuraActiveForDuelist(u8 fixedDuelist);
u8 CanPlayTrapFromHandViaMakyura(u16 trapId);
u8 TryActivateExecutorMakyuraTrapFromBackrow(u8 fixedRow, u8 fixedCol);

#endif // GUARD_EXECUTOR_MAKYURA_H
