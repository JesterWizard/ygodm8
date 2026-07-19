#ifndef GUARD_SYNCHRO_DUEL_H
#define GUARD_SYNCHRO_DUEL_H

#include "gba/types.h"

struct DuelCard;

#define SYNCHRO_MAX_SOURCES 5

struct SynchroMaterialSource {
  struct DuelCard *zone;
  u16 cardId;
  u8 level;
  u8 isTuner;
};

u8 Card_IsTuner(u16 cardId);

u8 SynchroDuel_CollectFaceUpFieldSources(struct SynchroMaterialSource *out, u8 maxOut);
u8 SynchroDuel_CanMakeLevel(const struct SynchroMaterialSource *sources, u8 sourceCount,
                            u8 targetLevel);
u8 SynchroDuel_SelectMaterialsForLevel(const struct SynchroMaterialSource *sources,
                                       u8 sourceCount, u8 targetLevel,
                                       struct SynchroMaterialSource *selected, u8 maxSelected);
u8 SynchroDuel_BuildFeasibleExtraDeckTargets(const struct SynchroMaterialSource *sources,
                                             u8 sourceCount, u16 *outIds, u8 maxOut);
u16 SynchroDuel_PlayerPickTarget(const u16 *targetIds, u8 count);
void SynchroDuel_Execute(u16 resultId, const struct SynchroMaterialSource *selected,
                         u8 selectedCount);
u8 SynchroDuel_PlayerCanSummon(void);
/* TRUE if a Synchro Summon is legal that uses the cursor's monster as material. */
u8 SynchroDuel_PlayerCanSummonWithSelected(void);
void SynchroDuel_RunPlayerFlow(void);

#if defined(DUEL_HELPERS_SELF_CHECK)
void SynchroDuel_SelfCheck(void);
#endif

#endif /* GUARD_SYNCHRO_DUEL_H */
