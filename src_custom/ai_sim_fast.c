#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "ai_sim.h"
#include "configs/runtime.h"
#include "duel.h"

#define AI_ACTION_TABLE_COUNT 0x3B2
#define AI_FAST_MAX_FULL_SIMS  8
#define AI_FAST_MAX_LIGHT_SIMS 16
#define AI_SIM_PRIORITY (*(u32 *)((u8 *)gUnk_8DFF6A4 + 0x2298))

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern const struct AI_Command gAED58[];

void sub_800EE24__Replacement(void);
void sub_800EE94__Replacement(void);

typedef void (*FnVoid)(void);
typedef u8 (*FnU8Void)(void);

static inline void CallThumbVoid(u32 addr)
{
  ((FnVoid)(addr | 1))();
}

static inline u8 CallThumbU8(u32 addr)
{
  return ((FnU8Void)(addr | 1))();
}

static void AiSimFastScanHandFlags(u8 *handHasPermCard)
{
  u8 col;

  *handHasPermCard = FALSE;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_HAND][col];

    if (zone->id == CARD_NONE)
      continue;
    SetCardInfo(zone->id);
    if (gCardInfo.unk1E != 0)
      *handHasPermCard = TRUE;
  }
}

static u8 AiSimFastZoneEmpty(u8 row, u8 col)
{
  if (row > ACTIVE_DUELIST_HAND)
    return FALSE;
  return gTurnZones[row][col]->id == CARD_NONE;
}

static u8 AiSimFastQuickReject(u16 i, u8 handHasPermCard)
{
  const struct AI_Command *cmd = &gAED58[i];
  u16 action = cmd->action;
  u8 row = cmd->zone1Position >> 4;
  u8 col = cmd->zone1Position & 0xF;

  if (action >= AI_ACTION_PERM_CARD_DISCARD && !handHasPermCard)
    return TRUE;

  if (row <= ACTIVE_DUELIST_HAND && AiSimFastZoneEmpty(row, col)) {
    if (IsAiSummonAction(action) || IsAiSetSpellAction(action) ||
        IsAiSetTrapAction(action) || IsAiActivateSpellAction(action) ||
        action == AI_ACTION_DISCARD || IsAiMonsterEffectAction(action))
      return TRUE;
  }

  if ((IsAiAttackAction(action) || IsAiDefensePositionAction(action)) &&
      row <= ACTIVE_DUELIST_MONSTER_ROW && AiSimFastZoneEmpty(row, col))
    return TRUE;

  if (cmd->zone2Position != 0) {
    u8 row2 = cmd->zone2Position >> 4;
    u8 col2 = cmd->zone2Position & 0xF;

    /* ponytail: zone2 is often an empty summon/set destination; only reject when it must hold a card. */
    if (row2 <= ACTIVE_DUELIST_HAND && AiSimFastZoneEmpty(row2, col2)) {
      if (IsAiSummonAction(action))
        return FALSE;
      if (IsAiSetTrapAction(action))
        return FALSE;
      if (IsAiSetSpellAction(action) && action != AI_ACTION_PLACE_EQUIP_SPELL)
        return FALSE;
      return TRUE;
    }
  }

  return FALSE;
}

static u32 AiSimFastBestRecordedPriority(void)
{
  u16 i;
  u32 best = 0;
  struct AiActionPriorityTable *table = gUnk_8DFF6A4;

  for (i = 0; i < table->actionCount; i++) {
    if (table->entries[i].priority > best)
      best = table->entries[i].priority;
  }

  return best;
}

static u8 AiSimFastNeedsFullSim(u16 action)
{
  if (IsAiAttackAction(action) || IsAiSummonAction(action))
    return TRUE;
  if (IsAiHighImpactAction(action))
    return TRUE;
  if (IsAiActivateSpellAction(action) || IsAiMonsterEffectAction(action))
    return TRUE;
  return FALSE;
}

static void AiSimFastRecordLightPriority(void)
{
  struct AiActionPriorityTable *table = gUnk_8DFF6A4;
  u16 slot = table->actionCount;

  CallThumbVoid(0x0800F1EC);
  table->entries[slot].actionIndex = g2021BF8;
  table->entries[slot].priority = AI_SIM_PRIORITY;
  table->actionCount++;
}

static void AiSimFastRunFullCandidate(void)
{
  sub_800EE24__Replacement();
  CallThumbVoid(0x0800F1EC);
  CallThumbVoid(0x0800E0F8);
  CallThumbVoid(0x0800F248);
  sub_800EE94__Replacement();
}

static void AiSimFastRunLightCandidate(void)
{
  sub_800EE24__Replacement();
  AiSimFastRecordLightPriority();
  sub_800EE94__Replacement();
}

static u8 AiSimFastTryCandidate(u16 i, u8 handHasPermCard, u8 *fullSims, u8 *lightSims)
{
  u16 action;

  if (AiSimFastQuickReject(i, handHasPermCard))
    return FALSE;

  AiInitCommandData(i);
  if (CallThumbU8(0x0801A08C) != 1)
    return FALSE;

  action = gAED58[i].action;
  if (AiSimFastNeedsFullSim(action)) {
    if (*fullSims >= AI_FAST_MAX_FULL_SIMS)
      return FALSE;
    AiSimFastRunFullCandidate();
    (*fullSims)++;
  } else {
    if (*lightSims >= AI_FAST_MAX_LIGHT_SIMS)
      return FALSE;
    AiSimFastRunLightCandidate();
    (*lightSims)++;
  }

  return TRUE;
}

static u8 AiSimFastShouldStop(u8 fullSims, u8 lightSims)
{
  u32 best;

  if (fullSims + lightSims < 4)
    return FALSE;

  best = AiSimFastBestRecordedPriority();
  if (best >= AI_PRIORITY_LETHAL_MIN)
    return TRUE;
  if (best >= 0x7EE00000u)
    return TRUE;
  if (fullSims >= AI_FAST_MAX_FULL_SIMS && lightSims >= AI_FAST_MAX_LIGHT_SIMS)
    return TRUE;

  return FALSE;
}

void AiSimulateAllCandidateActionsFast(void)
{
  u16 i;
  u8 fullSims = 0;
  u8 lightSims = 0;
  u8 handHasPermCard = FALSE;
  struct AiActionPriorityTable *table = gUnk_8DFF6A4;

  AiClearCommandData();
  CallThumbVoid(0x0800F108);
  AiSimFastScanHandFlags(&handHasPermCard);

  for (i = 0; i < AI_ACTION_TABLE_COUNT; i++) {
    if (!IsAiAttackAction(gAED58[i].action))
      continue;
    if (AiSimFastTryCandidate(i, handHasPermCard, &fullSims, &lightSims) &&
        AiSimFastShouldStop(fullSims, lightSims))
      goto done;
  }

  for (i = 0; i < AI_ACTION_TABLE_COUNT; i++) {
    if (IsAiAttackAction(gAED58[i].action))
      continue;
    if (AiSimFastTryCandidate(i, handHasPermCard, &fullSims, &lightSims) &&
        AiSimFastShouldStop(fullSims, lightSims))
      break;
  }

  if (table->actionCount == 0) {
    for (i = 0; i < AI_ACTION_TABLE_COUNT; i++) {
      AiInitCommandData(i);
      if (CallThumbU8(0x0801A08C) != 1)
        continue;
      AiSimFastRunLightCandidate();
      if (table->actionCount != 0)
        break;
    }
  }

done:
  ;
}
