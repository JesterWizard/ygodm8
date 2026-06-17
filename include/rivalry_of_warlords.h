#ifndef GUARD_RIVALRY_OF_WARLORDS_H
#define GUARD_RIVALRY_OF_WARLORDS_H

u8 IsActivatedRivalryOfWarlordsZone(const struct DuelCard *zone);
u8 IsRivalryOfWarlordsActiveOnField(void);
void RivalryOfWarlords_CheckAfterFieldChange(void);
void TryRivalryOfWarlordsOnMonsterPlacement(struct DuelCard *zone);
void EffectRivalryOfWarlords(void);

#endif // GUARD_RIVALRY_OF_WARLORDS_H
