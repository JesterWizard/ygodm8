#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "the_supremacy_sun.h"

void ClearTheSupremacySunState(void)
{
  gTheSupremacySunArmed[DUEL_PLAYER] = FALSE;
  gTheSupremacySunArmed[DUEL_OPPONENT] = FALSE;
  gTheSupremacySunStandbyReady[DUEL_PLAYER] = FALSE;
  gTheSupremacySunStandbyReady[DUEL_OPPONENT] = FALSE;
  gTheSupremacySunOwnEffectSummon = FALSE;
}

void MarkTheSupremacySunDestroyedFromField(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 owner;

  if (zone == NULL || zone->id != THE_SUPREMACY_SUN)
    return;

  if (Duel_ZoneIsHandSlot(zone)) {
    gTheSupremacySunArmed[DUEL_PLAYER] = FALSE;
    gTheSupremacySunArmed[DUEL_OPPONENT] = FALSE;
    return;
  }

  if (!zone->isFaceUp)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  owner = GetDuelistForZone(zone);
  if (owner > DUEL_OPPONENT)
    return;

  gTheSupremacySunArmed[owner] = TRUE;
  gTheSupremacySunStandbyReady[owner] = FALSE;
}

void TheSupremacySun_AgeStandbyFlags(void)
{
  u8 d;

  for (d = 0; d < 2; d++) {
    if (gTheSupremacySunArmed[d] && !gTheSupremacySunStandbyReady[d])
      gTheSupremacySunStandbyReady[d] = TRUE;
  }
}

static u8 OwnerHasSunInGraveyard(u8 fixedDuelist)
{
  u8 count;
  u8 i;

  if (GraveyardExpand_IsEnabled()) {
    count = GraveyardExpand_GetCount(fixedDuelist);
    for (i = 0; i < count; i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == THE_SUPREMACY_SUN)
        return TRUE;
    }
    return FALSE;
  }

  return gDuel.duelistbattleState[fixedDuelist].graveyard == THE_SUPREMACY_SUN;
}

static u8 OwnerHasEmptyMonsterZone(u8 fixedDuelist)
{
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

static u8 OwnerHasHandCard(u8 fixedDuelist)
{
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);

  return Duel_CountCardsInHand(gTurnHands[turnDuelist]) > 0;
}

static void RemoveSunFromGraveyard(u8 fixedDuelist)
{
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  u8 count;
  s8 i;

  if (GraveyardExpand_IsEnabled()) {
    count = GraveyardExpand_GetCount(fixedDuelist);
    for (i = (s8)count - 1; i >= 0; i--) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, (u8)i) != THE_SUPREMACY_SUN)
        continue;

      GraveyardExpand_RemoveAtTurn(turnDuelist, (u8)i);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      return;
    }
  }

  if (gTurnDuelistBattleState[turnDuelist]->graveyard == THE_SUPREMACY_SUN)
    GetGraveCardAndClearGrave(turnDuelist);
}

static void ResolveStandbyRevive(u8 fixedDuelist)
{
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  Duel_ShowEffectTextTyped(THE_SUPREMACY_SUN, 9);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(turnDuelist, 1, NULL, FALSE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  RemoveSunFromGraveyard(fixedDuelist);

  gTheSupremacySunOwnEffectSummon = TRUE;
  Duel_SpecialSummonMonsterId(turnDuelist, THE_SUPREMACY_SUN, opts);
  gTheSupremacySunOwnEffectSummon = FALSE;
}

void TheSupremacySun_TryResolveStandbyRevive(void)
{
  u8 d;

  for (d = 0; d < 2; d++) {
    if (!gTheSupremacySunArmed[d] || !gTheSupremacySunStandbyReady[d])
      continue;

    if (WhoseTurn() != d)
      continue;

    if (!OwnerHasSunInGraveyard(d) || !OwnerHasHandCard(d) || !OwnerHasEmptyMonsterZone(d)) {
      gTheSupremacySunArmed[d] = FALSE;
      gTheSupremacySunStandbyReady[d] = FALSE;
      continue;
    }

    ResolveStandbyRevive(d);
    gTheSupremacySunArmed[d] = FALSE;
    gTheSupremacySunStandbyReady[d] = FALSE;
  }
}

#if defined(THE_SUPREMACY_SUN_SELF_CHECK)
void TheSupremacySun_SelfCheck(void)
{
  if (ARRAY_COUNT(gTheSupremacySunArmed) != 2)
    while (1)
      ;
}
#endif
