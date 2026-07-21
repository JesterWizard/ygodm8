#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define END_OF_THE_WORLD_MAX_CANDS 10

void UpdateDuelGfxExceptField(void);

static u8 IsEndOfTheWorldRitual(u16 cardId)
{
  return cardId == DEMISE_KING_OF_ARMAGEDDON;
}

static u8 RitualLevel(u16 cardId)
{
  if (!IsEndOfTheWorldRitual(cardId))
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

static u8 MonsterLevel(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.level;
}

static s8 FindRitualHandZone(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsEndOfTheWorldRitual(handRow[i]->id))
      return (s8)i;
  }

  return -1;
}

static u8 CollectTributeCandidates(s8 ritualHandZone, struct DuelCard **outZones, u8 *outLevels,
                                   u8 *outIsField, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (!IsTributeableMonster(zone->id))
      continue;
    if (count >= maxOut)
      break;

    outZones[count] = zone;
    outLevels[count] = MonsterLevel(zone->id);
    outIsField[count] = TRUE;
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
    outIsField[count] = FALSE;
    count++;
  }

  return count;
}

/* Prefer a mask that frees a monster zone when the row is full. */
static u8 FindExactTributeMask(u8 targetLevel, u8 candCount, const u8 *levels,
                               const u8 *isField, u8 needFieldTribute, u16 *outMask)
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
      if (isField[i])
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

static u8 CanActivateEndOfTheWorld(void)
{
  struct DuelCard *zones[END_OF_THE_WORLD_MAX_CANDS];
  u8 levels[END_OF_THE_WORLD_MAX_CANDS];
  u8 isField[END_OF_THE_WORLD_MAX_CANDS];
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
  candCount = CollectTributeCandidates(ritualZone, zones, levels, isField,
                                       END_OF_THE_WORLD_MAX_CANDS);
  return FindExactTributeMask(level, candCount, levels, isField, needField, &mask);
}

static s8 PickRitualHandZone(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsEndOfTheWorldRitual);

  return FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
}

static void END_OF_THE_WORLD_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *zones[END_OF_THE_WORLD_MAX_CANDS];
  u8 levels[END_OF_THE_WORLD_MAX_CANDS];
  u8 isField[END_OF_THE_WORLD_MAX_CANDS];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 ritualZone;
  u8 candCount;
  u16 mask;
  u8 needField;
  u16 ritualId;
  u8 level;
  u8 i;

  if (!CanActivateEndOfTheWorld())
    return;

  Duel_ShowEffectText(END_OF_THE_WORLD);

  if (IsDuelOver() == TRUE)
    return;

  ritualZone = PickRitualHandZone();
  if (ritualZone < 0)
    return;

  ritualId = gTurnHands[ACTIVE_DUELIST][ritualZone]->id;
  level = RitualLevel(ritualId);
  needField = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0;
  candCount = CollectTributeCandidates(ritualZone, zones, levels, isField,
                                       END_OF_THE_WORLD_MAX_CANDS);
  if (!FindExactTributeMask(level, candCount, levels, isField, needField, &mask))
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  for (i = 0; i < candCount; i++) {
    if (!(mask & (1u << i)))
      continue;

    if (Duel_DestroyZone(zones[i], ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (IsDuelOver() == TRUE)
    return;

  /* Re-find ritual hand zone — tribute from hand may have shifted slots. */
  ritualZone = FindRitualHandZone(gTurnHands[ACTIVE_DUELIST]);
  if (ritualZone < 0)
    return;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, ritualZone, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectEND_OF_THE_WORLD(void)
{
  if (!CanActivateEndOfTheWorld()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(END_OF_THE_WORLD, END_OF_THE_WORLD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void END_OF_THE_WORLD_SelfCheck(void)
{
  if (!IsEndOfTheWorldRitual(DEMISE_KING_OF_ARMAGEDDON))
    while (1)
      ;
  if (IsEndOfTheWorldRitual(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  SetCardInfo(DEMISE_KING_OF_ARMAGEDDON);
  if (gCardInfo.level != 8)
    while (1)
      ;
}
#endif
