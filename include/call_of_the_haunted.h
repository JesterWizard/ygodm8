#ifndef GUARD_CALL_OF_THE_HAUNTED_H
#define GUARD_CALL_OF_THE_HAUNTED_H

#define TRAP_CALL_OF_THE_HAUNTED 26

void EffectCallOfTheHaunted(void);
void SaveCallOfTheHauntedAttackResume(void);
void PrepareCallOfTheHauntedAttackResume(struct DuelCard *attacker,
    struct DuelCard *defender);
void TryResumeInterruptedAttackAfterCallOfTheHaunted(void);
void CallOfTheHauntedRequestAiResimulate(void);
void CallOfTheHauntedUnlockAiAttackerAfterTrap(void);
void AiResimulateAllActions(void);
void CallOfTheHauntedShowActivationText(void);
void MarkCallOfTheHauntedAttackTollPaid(void);
void TryActivateCallOfTheHauntedOnOpponentTurnStart(void);
void NoteCallOfTheHauntedRevivedMonster(u8 turnCol);
u8 CallOfTheHauntedRedirectsDirectAttack(u8 *defenderFixedCol);

extern u8 gAiResimulateAfterCallOfTheHaunted;
extern u8 gAiSimSavedResimulateAfterCallOfTheHaunted;

#endif // GUARD_CALL_OF_THE_HAUNTED_H
