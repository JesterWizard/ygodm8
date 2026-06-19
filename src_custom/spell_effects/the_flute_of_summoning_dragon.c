#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"
#include "the_flute_of_summoning_dragon.h"

#define FLUTE_MAX_SUMMONS 2

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_DRAGON;
}

static u8 HandHasDragonMonster(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDragonMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasLordOfD(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], LORD_OF_D);
}

static u8 CountDragonMonstersInHand(struct DuelCard **handRow)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDragonMonster(handRow[i]->id))
      count++;
  }

  return count;
}

static s8 PickDragonHandZone(struct DuelCard **handRow, u8 pickHighestAtk)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!IsDragonMonster(cardId))
      continue;

    if (!pickHighestAtk)
      return i;

    SetCardInfo(cardId);
    if (chosenZone < 0 || gCardInfo.atk > bestAtk) {
      chosenZone = i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenZone;
}

static u8 SummonCountForFlute(void)
{
  u8 count = CountDragonMonstersInHand(gTurnHands[ACTIVE_DUELIST]);
  u8 emptyZones = (u8)NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);

  if (count > FLUTE_MAX_SUMMONS)
    count = FLUTE_MAX_SUMMONS;

  if (count > emptyZones)
    count = emptyZones;

  return count;
}

u8 CanActivateTheFluteOfSummoningDragon(void)
{
  if (!FieldHasLordOfD())
    return FALSE;

  if (!HandHasDragonMonster(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void SpecialSummonDragonsFromHand(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 summons = SummonCountForFlute();
  u8 i;

  for (i = 0; i < summons; i++) {
    s8 handZone;
    enum DuelActionResult result;

    if (IsDuelOver() == TRUE || !FieldHasLordOfD())
      return;

    if (!HandHasDragonMonster(handRow))
      return;

    if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      return;

    if (WhoseTurn() == DUEL_PLAYER) {
      result = Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsDragonMonster, opts);
      if (result == DUEL_ACTION_DUEL_OVER)
        return;
      continue;
    }

    handZone = PickDragonHandZone(handRow, TRUE);
    if (handZone < 0)
      return;

    result = Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
    if (result == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

APPEND_TEXT void EffectTheFluteOfSummoningDragon(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(THE_FLUTE_OF_SUMMONING_DRAGON);

  if (IsDuelOver() == TRUE || !CanActivateTheFluteOfSummoningDragon())
    return;

  SpecialSummonDragonsFromHand();

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}
