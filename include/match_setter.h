#ifndef GUARD_MATCH_SETTER_H
#define GUARD_MATCH_SETTER_H

#include "global.h"

#define DEBUG_MATCH_SETTER_NONE 0
#define MATCH_SETTER_OBJECT_SLOT 1
#define MATCH_SETTER_SPAWN_X 72
#define MATCH_SETTER_SPAWN_Y 54

struct MatchSetterEntry {
  u8 spriteId;
  u8 portraitId;
  u8 title[24];
  struct Script *scriptA;
  struct Script *scriptR;
};

extern u8 gDebugMatchSetterSelection;

void MatchSetter_Init(void);
void MatchSetter_ApplySpawn(void);
void MatchSetter_RefreshField(void);
const struct MatchSetterEntry *MatchSetter_GetEntry(u8 index);
u8 MatchSetter_GetEntryCount(void);

#endif // GUARD_MATCH_SETTER_H
