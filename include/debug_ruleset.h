#ifndef GUARD_DEBUG_RULESET_H
#define GUARD_DEBUG_RULESET_H

#include "gba/types.h"

#define DEBUG_RULESET_DEFAULT 0
#define DEBUG_RULESET_DUELIST_KINGDOM 1

#define DEBUG_RULESET_DUELIST_KINGDOM_LP 2000

extern u8 gDebugRuleset;
extern u8 gDebugRulesetFlashPrimary;
extern u8 gDebugRulesetFlashBackup;

u8 DebugRuleset_GetMode(void);
u8 DebugRuleset_IsDuelistKingdom(void);
u8 DebugRuleset_AllowDirectAttacks(void);
u8 DebugRuleset_CanAttackThisTurn(void);
void DebugRuleset_MarkAttackUsed(void);
void DebugRuleset_ResetTurnAttack(void);
void DebugRuleset_TryEnforceMustPlayMonsterRule(void);
void DebugRuleset_SetMode(u8 mode);
void DebugRuleset_LoadFromFlashPrimary(void);
void DebugRuleset_LoadFromFlashBackup(void);
void DebugRuleset_SaveToFlashPrimary(void);
void DebugRuleset_SaveToFlashBackup(void);
void DebugRuleset_Reset(void);

#endif
