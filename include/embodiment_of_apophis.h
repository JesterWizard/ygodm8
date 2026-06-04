#ifndef GUARD_EMBODIMENT_OF_APOPHIS_H
#define GUARD_EMBODIMENT_OF_APOPHIS_H

#include "global.h"

#define MAX_APOPHIS_LINKS 5
#define APOPHIS_BOARD_COORD_INVALID 0xFF

struct ApophisLink {
  u8 active;
  u8 trapBoardRow;
  u8 trapBoardCol;
  u8 monBoardRow;
  u8 monBoardCol;
};

extern struct ApophisLink gApophisLinks[MAX_APOPHIS_LINKS];
extern u8 gApophisClearingPartner;

void ResetApophisLinks(void);
void EffectEmbodimentOfApophis(void);
struct DuelCard *EmbodimentOfApophisMonsterZoneForTrap(struct DuelCard *trapZone);
u8 EmbodimentOfApophisHasEmptyMonsterZoneForTrap(struct DuelCard *trapZone);
u8 RegisterEmbodimentOfApophisLinkFromZones(struct DuelCard *trapZone, struct DuelCard *monsterZone);
void InitEmbodimentOfApophisMonsterZone(struct DuelCard *zone);
void OnEmbodimentOfApophisZoneAboutToClear(struct DuelCard *zone);
u8 EmbodimentOfApophisZoneOnMonsterRow(const struct DuelCard *zone);
u8 EmbodimentOfApophisZoneIsMonsterForm(const struct DuelCard *zone);
u8 EmbodimentOfApophisZoneIsTrapForm(const struct DuelCard *zone);
u8 EmbodimentOfApophisTrapZoneIsAwakened(const struct DuelCard *zone);
void ApplyEmbodimentOfApophisCardInfoOverridesForStatMod(struct StatMod *ptr);

#endif
