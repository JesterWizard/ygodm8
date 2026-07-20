#ifndef GUARD_NEO_SPACIAN_GLOW_MOSS_H
#define GUARD_NEO_SPACIAN_GLOW_MOSS_H

extern u8 gPendingNeoSpacianGlowMossDraw;

void ApplyNeoSpacianGlowMossBattleEffect(void);
void ResolveNeoSpacianGlowMossBattleEffect(void);
void ApplyNeoSpacianMossDrawnTypeEffect(u16 drawnCardId, u8 mossFixedRow, u8 mossFixedCol,
                                        u16 effectCardId);
u8 CanNeoSpacianGlowMossAttackDirectly(const struct DuelCard *zone);

#endif
