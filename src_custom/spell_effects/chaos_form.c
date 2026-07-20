#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define CHAOS_FORM_MAX_CANDS 16

#define CHAOS_FORM_SRC_FIELD 0
#define CHAOS_FORM_SRC_HAND 1
#define CHAOS_FORM_SRC_GY 2

void UpdateDuelGfxExceptField(void);

static const char sChaosName[] APPEND_RODATA = "Chaos";
static const char sBlackLusterSoldierName[] APPEND_RODATA = "Black Luster Soldier";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsChaosFormRitual(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != RITUAL_CARD)
    return FALSE;

  if (Duel_CardNameContains(cardId, sBlackLusterSoldierName))
    return TRUE;

  return Duel_CardNameContains(cardId, sChaosName);
}

static u8 RitualLevel(u16 cardId)
{
  if (!IsChaosFormRitual(cardId))
    return 0;

  SetCardInfo(cardId);
  return gCardInfo.level;
}

static u8 IsTributeableMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 IsChaosFormGySubstitute(u16 cardId)
{
  return cardId == BLUE_EYES_WHITE_DRAGON || cardId == DARK_MAGICIAN;
}

static u8 MonsterLevel(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.level;
}

static s8 FindRitualHandZone(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsChaosFormRitual(handRow[i]->id))
      return (s8)i;
  }

  return -1;
}

static u8 CollectTributeCandidates(s8 ritualHandZone, struct DuelCard **outZones, u8 *outLevels,
                                   u8 *outSrc, u8 *outGyIndex, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (!IsTributeableMonster(zone->id))
      continue;
    if (count >= maxOut)
      break;

    outZones[count] = zone;
    outLevels[count] = MonsterLevel(zone->id);
    outSrc[count] = CHAOS_FORM_SRC_FIELD;
    outGyIndex[count] = 0xFF;
    count++;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if ((s8)i == ritualHandZone)
      continue;
    if (!IsTributeableMonster(zone->id))
      continue;
    if (count >= maxOut)
      break;

    outZones[count] = zone;
    outLevels[count] = MonsterLevel(zone->id);
    outSrc[count] = CHAOS_FORM_SRC_HAND;
    outGyIndex[count] = 0xFF;
    count++;
  }

  if (GraveyardExpand_IsEnabled()) {
    u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);

    for (i = 0; i < gyCount; i++) {
      u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (!IsChaosFormGySubstitute(cardId))
        continue;
      if (count >= maxOut)
        break;

      outZones[count] = NULL;
      outLevels[count] = MonsterLevel(cardId);
      outSrc[count] = CHAOS_FORM_SRC_GY;
      outGyIndex[count] = i;
      count++;
    }
  } else {
    u16 top = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (IsChaosFormGySubstitute(top) && count < maxOut) {
      outZones[count] = NULL;
      outLevels[count] = MonsterLevel(top);
      outSrc[count] = CHAOS_FORM_SRC_GY;
      outGyIndex[count] = 0;
      count++;
    }
  }

  return count;
}

static u8 FindExactTributeMask(u8 targetLevel, u8 candCount, const u8 *levels, const u8 *src,
                               u8 needFieldTribute, u16 *outMask)
{
  u16 mask;
  u16 maxMask;

  if (candCount == 0 || candCount > 15 || targetLevel == 0)
    return FALSE;

  maxMask = (u16)(1u << candCount);
  for (mask = 1; mask < maxMask; mask++) {
    u8 sum = 0;
    u8 i;
    u8 hasField = FALSE;

    for (i = 0; i < candCount; i++) {
      if (!(mask & (1u << i)))
        continue;
      sum += levels[i];
      if (src[i] == CHAOS_FORM_SRC_FIELD)
        hasField = TRUE;
    }

    if (sum != targetLevel)
      continue;
    if (needFieldTribute && !hasField)
      continue;

    *outMask = mask;
    return TRUE;
  }

  return FALSE;
}

static u8 CanActivateChaosForm(void)
{
  struct DuelCard *zones[CHAOS_FORM_MAX_CANDS];
  u8 levels[CHAOS_FORM_MAX_CANDS];
  u8 src[CHAOS_FORM_MAX_CANDS];
  u8 gyIndex[CHAOS_FORM_MAX_CANDS];
  s8 ritualZone;
  u8 candCount;
  u16 mask;
  u8 needField;
  u16 ritualId;
  u8 level;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  ritualZone = FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (ritualZone < 0)
    return FALSE;

  ritualId = gTurnHands[ACTIVE_DUELIST][ritualZone]->id;
  level = RitualLevel(ritualId);
  if (level == 0)
    return FALSE;

  needField = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0;
  candCount = CollectTributeCandidates(ritualZone, zones, levels, src, gyIndex,
                                       CHAOS_FORM_MAX_CANDS);
  return FindExactTributeMask(level, candCount, levels, src, needField, &mask);
}

static s8 PickRitualHandZone(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsChaosFormRitual);

  return FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
}

static void CHAOS_FORM_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *zones[CHAOS_FORM_MAX_CANDS];
  u8 levels[CHAOS_FORM_MAX_CANDS];
  u8 src[CHAOS_FORM_MAX_CANDS];
  u8 gyIndex[CHAOS_FORM_MAX_CANDS];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 ritualZone;
  u8 candCount;
  u16 mask;
  u8 needField;
  u16 ritualId;
  u8 level;
  u8 i;
  u8 gyIndices[CHAOS_FORM_MAX_CANDS];
  u8 gyCount = 0;

  if (!CanActivateChaosForm())
    return;

  Duel_ShowEffectText(CHAOS_FORM);

  if (IsDuelOver() == TRUE)
    return;

  ritualZone = PickRitualHandZone();
  if (ritualZone < 0)
    return;

  ritualId = gTurnHands[ACTIVE_DUELIST][ritualZone]->id;
  level = RitualLevel(ritualId);
  needField = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0;
  candCount = CollectTributeCandidates(ritualZone, zones, levels, src, gyIndex,
                                       CHAOS_FORM_MAX_CANDS);
  if (!FindExactTributeMask(level, candCount, levels, src, needField, &mask))
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  for (i = 0; i < candCount; i++) {
    if (!(mask & (1u << i)))
      continue;

    if (src[i] == CHAOS_FORM_SRC_GY) {
      gyIndices[gyCount++] = gyIndex[i];
      continue;
    }

    if (Duel_DestroyZone(zones[i], ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  /* Banish GY substitutes highest-index first so earlier indices stay stable. */
  while (gyCount > 0) {
    u8 best = 0;
    u8 g;

    for (g = 1; g < gyCount; g++) {
      if (gyIndices[g] > gyIndices[best])
        best = g;
    }

    if (GraveyardExpand_IsEnabled())
      Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndices[best]);
    else
      Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);

    gyIndices[best] = gyIndices[gyCount - 1];
    gyCount--;
  }

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (IsDuelOver() == TRUE)
    return;

  ritualZone = FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (ritualZone < 0)
    return;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, ritualZone, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectCHAOS_FORM(void)
{
  if (!CanActivateChaosForm()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CHAOS_FORM, CHAOS_FORM_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CHAOS_FORM_SelfCheck(void)
{
  if (!IsChaosFormRitual(BLACK_LUSTER_SOLDIER))
    while (1)
      ;
  if (!IsChaosFormRitual(MAGICIAN_OF_BLACK_CHAOS))
    while (1)
      ;
  if (!IsChaosFormRitual(BLUE_EYES_CHAOS_MAX_DRAGON))
    while (1)
      ;
  if (IsChaosFormRitual(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsChaosFormGySubstitute(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsChaosFormGySubstitute(DARK_MAGICIAN))
    while (1)
      ;
}
#endif
