#ifndef GUARD_DESTINY_HERO_DASHER_H
#define GUARD_DESTINY_HERO_DASHER_H

void MarkDestinyHeroDasherAttackedFromBattle(void);
void TryApplyDestinyHeroDasherBattlePhaseEnd(void);
void TryApplyDestinyHeroDasherOnDraw(u8 duelist, u16 cardDrawn, u8 handSlot);

#endif // GUARD_DESTINY_HERO_DASHER_H
