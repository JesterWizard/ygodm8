#ifndef GUARD_THE_GRAND_JUPITER_H
#define GUARD_THE_GRAND_JUPITER_H

#include "global.h"
#include "duel.h"

#define GRAND_JUPITER_BACKROW_SLOT_COUNT 10
#define GRAND_JUPITER_MONSTER_CELL_COUNT 10
#define GRAND_JUPITER_ABSORB_USED 1
#define GRAND_JUPITER_END_PHASE_USED 2
#define DUEL_CURSOR_THE_GRAND_JUPITER_ABSORB_TARGET 40

extern u8 gGrandJupiterEquipActive[GRAND_JUPITER_BACKROW_SLOT_COUNT];
extern u8 gGrandJupiterEquipOriginalAtk[GRAND_JUPITER_BACKROW_SLOT_COUNT * 2];
extern u8 gGrandJupiterEquipJupiterRow[GRAND_JUPITER_BACKROW_SLOT_COUNT];
extern u8 gGrandJupiterEquipJupiterCol[GRAND_JUPITER_BACKROW_SLOT_COUNT];

void ApplyTheGrandJupiterEquipAtkBonus(struct DuelCard *zone);

u8 IsGrandJupiterEquipZone(u8 fixedBackrowRow, u8 fixedBackrowCol);
void ClearTheGrandJupiterEquipsForJupiterZone(struct DuelCard *jupiterZone);
void ClearTheGrandJupiterEquipSlot(u8 fixedBackrowRow, u8 fixedBackrowCol);
void ResetTheGrandJupiterEquipState(void);
void ResetTheGrandJupiterEndPhaseFlags(void);
unsigned char ShouldActivateTheGrandJupiterTurnEffect(void);
void ActivateTheGrandJupiterTurnEffect(void);
unsigned char CanActivateTheGrandJupiter(void);
void ActivateTheGrandJupiterEffect(void);
void TrySelectTheGrandJupiterAbsorbTarget(void);
void CancelTheGrandJupiterAbsorbTargeting(void);
u8 CanActivateGrandJupiterEquippedMonster(u8 fixedBackrowRow, u8 fixedBackrowCol);
void ActivateGrandJupiterEquippedMonster(u8 fixedBackrowRow, u8 fixedBackrowCol);

#endif // GUARD_THE_GRAND_JUPITER_H
