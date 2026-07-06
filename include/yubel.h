#ifndef GUARD_YUBEL_H
#define GUARD_YUBEL_H

#include "global.h"

#define YUBEL_PENDING_DESTROY_NONE 0xFF

#define DUEL_CURSOR_YUBEL_TRIBUTE_TARGET 42

extern u8 gYubelOwnEffectSummon;
extern u8 gYubelSelfDestructActive;
extern u8 gYubelSuppressGyEvolution;
extern u8 gYubelTerrorLeftFieldPending;
extern u8 gPendingYubelUltimateDestroyRow;
extern u8 gPendingYubelUltimateDestroyCol;
extern u8 gYubelTributeOriginRow;
extern u8 gYubelTributeOriginCol;
extern u8 gYubelTributeOwner;
extern u8 gYubelEndPhaseResolvedThisTurn;

u8 Yubel_IsFamilyCard(u16 cardId);
u8 Yubel_IsEvolutionForm(u16 cardId);

void Yubel_ClearBattlePending(void);
void Yubel_ClearTurnState(void);
void Yubel_NoteMonsterLeftField(struct DuelCard *zone);
void Yubel_NoteGraveyardMonsterSend(struct DuelCard *zone);

void ApplyYubelBattleEffects(void);
void ResolveYubelUltimateNightmareBattleEffect(void);

unsigned char ShouldActivateYubelEndPhase(void);
void ActivateYubelEndPhase(void);
void TryApplyYubelEndPhaseEffect(void);
unsigned char ShouldActivateYubelTerrorEndPhase(void);
void ActivateYubelTerrorEndPhase(void);
void TryApplyYubelTerrorEndPhaseEffect(void);
void ResolveYubelEndPhaseEffectsAtTurnEnd(void);
u8 Yubel_ConfirmTurnEndFromMenu(void);
void TrySelectYubelTributeTarget(void);

unsigned char ShouldActivateYubelEvolution(void);
void ActivateYubelEvolution(void);
unsigned char ShouldActivateYubelTerrorEvolution(void);
void ActivateYubelTerrorEvolution(void);

#endif
