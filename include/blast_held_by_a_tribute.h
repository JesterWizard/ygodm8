#ifndef GUARD_BLAST_HELD_BY_A_TRIBUTE_H
#define GUARD_BLAST_HELD_BY_A_TRIBUTE_H

#define TRAP_BLAST_HELD_BY_A_TRIBUTE 31

extern u8 gTributeSummonedMonsterMaskOpponentRow;
extern u8 gTributeSummonedMonsterMaskPlayerRow;

void BlastHeldByATribute_ClearAllMarks(void);
void BlastHeldByATribute_ClearZoneMark(struct DuelCard *zone);
void BlastHeldByATribute_TransferZoneMark(struct DuelCard *dst, struct DuelCard *src);
void TryBlastHeldByATributeOnMonsterPlacement(struct DuelCard *zone);
void BlastHeldByATribute_MarkTributeSummonedMonster(u16 cardId);
u8 BlastHeldByATribute_WasTributeSummoned(struct DuelCard *zone);
u8 BlastHeldByATribute_ShouldActivateTrap(void);
void EffectBlastHeldByATribute(void);

#endif // GUARD_BLAST_HELD_BY_A_TRIBUTE_H
