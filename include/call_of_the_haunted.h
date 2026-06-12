#ifndef GUARD_CALL_OF_THE_HAUNTED_H
#define GUARD_CALL_OF_THE_HAUNTED_H

#define TRAP_CALL_OF_THE_HAUNTED 26

void EffectCallOfTheHaunted(void);
void SaveCallOfTheHauntedAttackResume(void);
void TryResumeInterruptedAttackAfterCallOfTheHaunted(void);
void CallOfTheHauntedShowActivationText(void);
void MarkCallOfTheHauntedAttackTollPaid(void);
void TryActivateCallOfTheHauntedOnOpponentTurnStart(void);
void NoteCallOfTheHauntedRevivedMonster(u8 turnCol);
u8 CallOfTheHauntedRedirectsDirectAttack(u8 *defenderFixedCol);

#endif // GUARD_CALL_OF_THE_HAUNTED_H
