#ifndef GUARD_XYZ_DUEL_H
#define GUARD_XYZ_DUEL_H

#include "gba/types.h"

struct DuelCard;

#define XYZ_MAX_SOURCES 5
#define XYZ_MAX_OVERLAYS 5

struct XyzMaterialSource {
  struct DuelCard *zone;
  u16 cardId;
  u8 level;
};

u8 Card_XyzMaterialCount(u16 cardId);

void XyzOverlays_InitBoard(void);
void XyzOverlays_ClearZone(u8 fixedDuelist, u8 col);
void XyzOverlays_Attach(u8 fixedDuelist, u8 col, const u16 *cardIds, u8 count);
u8 XyzOverlays_GetCount(u8 fixedDuelist, u8 col);
/* Detach top overlay to GY. Returns detached card ID, or CARD_NONE. */
u16 XyzOverlays_DetachToGraveyard(u8 fixedDuelist, u8 col, u8 graveyardTurn);
void XyzOverlays_DumpAllToGraveyard(u8 fixedDuelist, u8 col, u8 graveyardTurn);
/* Call before clearing a monster zone that may hold an XYZ with overlays. */
void XyzOverlays_OnMonsterZoneCleared(struct DuelCard *zone, u8 graveyardTurn);

u8 XyzDuel_CollectFaceUpFieldSources(struct XyzMaterialSource *out, u8 maxOut);
u8 XyzDuel_CanMakeRank(const struct XyzMaterialSource *sources, u8 sourceCount, u8 rank,
                       u8 needCount);
u8 XyzDuel_SelectMaterialsForRank(const struct XyzMaterialSource *sources, u8 sourceCount,
                                  u8 rank, u8 needCount, struct XyzMaterialSource *selected,
                                  u8 maxSelected);
u8 XyzDuel_BuildFeasibleExtraDeckTargets(const struct XyzMaterialSource *sources, u8 sourceCount,
                                         u16 *outIds, u8 maxOut);
u16 XyzDuel_PlayerPickTarget(const u16 *targetIds, u8 count);
void XyzDuel_Execute(u16 resultId, const struct XyzMaterialSource *selected, u8 selectedCount);
u8 XyzDuel_PlayerCanSummon(void);
void XyzDuel_RunPlayerFlow(void);

#if defined(DUEL_HELPERS_SELF_CHECK)
void XyzDuel_SelfCheck(void);
#endif

#endif /* GUARD_XYZ_DUEL_H */
