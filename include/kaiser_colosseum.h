#ifndef GUARD_KAISER_COLOSSEUM_H
#define GUARD_KAISER_COLOSSEUM_H

u8 IsActivatedKaiserColosseumZone(const struct DuelCard *zone);
u8 IsKaiserColosseumActiveOnField(void);
u8 KaiserColosseum_AllowsMonsterPlacement(u8 fixedMonsterRow);
void EffectKaiserColosseum(void);

#endif // GUARD_KAISER_COLOSSEUM_H
