#include "global.h"
#include "card.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "duel_status.h"
#include "embodiment_of_apophis.h"

extern void (*g20245AC)(int, u8 *, int);
extern u8 gDebugRulesetTurnAttackUsed;

int sub_80588C4(u8 *, int, int);

static void DebugRuleset_Normalize(void) {
  if (gDebugRuleset != DEBUG_RULESET_DUELIST_KINGDOM)
    gDebugRuleset = DEBUG_RULESET_DEFAULT;
}

u8 DebugRuleset_GetMode(void) {
  return gDebugRuleset;
}

u8 DebugRuleset_IsDuelistKingdom(void) {
  return gDebugRuleset == DEBUG_RULESET_DUELIST_KINGDOM;
}

u8 DebugRuleset_AllowDirectAttacks(void) {
  return !DebugRuleset_IsDuelistKingdom();
}

u8 DebugRuleset_CanAttackThisTurn(void) {
  if (!DebugRuleset_IsDuelistKingdom())
    return TRUE;

  return !gDebugRulesetTurnAttackUsed;
}

void DebugRuleset_MarkAttackUsed(void) {
  if (DebugRuleset_IsDuelistKingdom())
    gDebugRulesetTurnAttackUsed = TRUE;
}

void DebugRuleset_ResetTurnAttack(void) {
  gDebugRulesetTurnAttackUsed = FALSE;
}

static u8 DebugRuleset_ZoneCountsAsBoardMonster(const struct DuelCard *zone) {
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return TRUE;

  return EmbodimentOfApophisZoneIsMonsterForm(zone);
}

static u8 DebugRuleset_DuelistHasMonsterOnBoard(u8 duelist) {
  u8 row = duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (DebugRuleset_ZoneCountsAsBoardMonster(gFixedZones[row][i]))
      return TRUE;
  }

  return FALSE;
}

void DebugRuleset_TryEnforceMustPlayMonsterRule(void) {
  u8 duelist;

  if (!DebugRuleset_IsDuelistKingdom() || IsDuelOver() == TRUE)
    return;

  duelist = WhoseTurn();

  if (DebugRuleset_DuelistHasMonsterOnBoard(duelist))
    return;

  DeclareLoser(duelist);
}

void DebugRuleset_SetMode(u8 mode) {
  gDebugRuleset =
      mode == DEBUG_RULESET_DUELIST_KINGDOM ? DEBUG_RULESET_DUELIST_KINGDOM : DEBUG_RULESET_DEFAULT;
  DebugRuleset_SaveToFlashPrimary();
  DebugRuleset_SaveToFlashBackup();
}

static void DebugRuleset_LoadFromFlash(int address) {
  if (g20245AC == NULL)
    return;
  g20245AC(address, &gDebugRuleset, 1);
  DebugRuleset_Normalize();
}

void DebugRuleset_LoadFromFlashPrimary(void) {
  DebugRuleset_LoadFromFlash((int)&gDebugRulesetFlashPrimary);
}

void DebugRuleset_LoadFromFlashBackup(void) {
  DebugRuleset_LoadFromFlash((int)&gDebugRulesetFlashBackup);
}

void DebugRuleset_SaveToFlashPrimary(void) {
  sub_80588C4(&gDebugRuleset, (int)&gDebugRulesetFlashPrimary, 1);
}

void DebugRuleset_SaveToFlashBackup(void) {
  sub_80588C4(&gDebugRuleset, (int)&gDebugRulesetFlashBackup, 1);
}

void DebugRuleset_Reset(void) {
  gDebugRuleset = DEBUG_RULESET_DEFAULT;
}
