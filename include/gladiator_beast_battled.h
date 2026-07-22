#ifndef GUARD_GLADIATOR_BEAST_BATTLED_H
#define GUARD_GLADIATOR_BEAST_BATTLED_H

#include "global.h"

#define GLADIATOR_BEAST_BATTLED_MARK 0x20
#define GLADIATOR_BEAST_TAG_SS_MARK 0x40

struct DuelCard;

u8 GladiatorBeast_InBattlePhase(void);
void GladiatorBeast_MarkBattlePhaseActive(void);
void GladiatorBeast_ClearBattlePhaseActive(void);
u8 GladiatorBeast_CanActivateTagOutEffect(const struct DuelCard *zone);
u8 GladiatorBeast_HasOtherMonsterInDeck(u16 excludeId);
u8 GladiatorBeast_CanActivateDeckTagOut(u16 cardId, struct DuelCard *zone);
void GladiatorBeast_ActivateDeckTagOut(struct DuelCard *self, u16 selfCardId);
u8 GladiatorBeast_CanActivateTagOutDraw(u16 cardId, struct DuelCard *zone);
void GladiatorBeast_ActivateDeckTagOutDraw(struct DuelCard *self, u16 selfCardId);
void GladiatorBeast_MarkTagSummonedZone(u16 cardId);
void ApplyGladiatorBeastTagOutStatBoostToCardInfo(const struct DuelCard *zone);
u8 GladiatorBeast_ZoneBattledThisBattlePhase(const struct DuelCard *zone);
void ApplyGladiatorBeastBattledMarks(void);
void ClearGladiatorBeastBattledMarks(void);

#endif /* GUARD_GLADIATOR_BEAST_BATTLED_H */
