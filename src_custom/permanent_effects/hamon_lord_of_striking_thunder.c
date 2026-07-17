#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "duel_helpers.h"
#include "hamon_lord_of_striking_thunder.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void BlockTurnSummoning(u8);

static u8 IsFaceUpSpellInBackrow(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!zone->isFaceUp)
    return FALSE;
  return GetTypeGroup(zone->id) == TYPE_GROUP_SPELL;
}

static u8 CountFaceUpContinuousSpells(u8 fixedDuelist)
{
  u8 fixedRow = (fixedDuelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpSpellInBackrow(gFixedZones[fixedRow][col]))
      count++;
  }
  return count;
}

static void SendFaceUpSpellsToGrave(u8 fixedDuelist)
{
  u8 fixedRow = (fixedDuelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;
  u8 sent = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW && sent < HAMON_CONTINUOUS_SPELL_COST; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (!IsFaceUpSpellInBackrow(zone))
      continue;
    Duel_DestroyZone(zone, fixedDuelist, FALSE);
    sent++;
  }
}

u8 CanSpecialSummonHamonLordOfStrikingThunderFromHand(u8 handZone)
{
  u8 fixedDuelist;
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HAMON_LORD_OF_STRIKING_THUNDER)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  fixedDuelist = (WhoseTurn() == DUEL_PLAYER) ? DUEL_PLAYER : DUEL_OPPONENT;
  return CountFaceUpContinuousSpells(fixedDuelist) >= HAMON_CONTINUOUS_SPELL_COST;
}

u8 TrySpecialSummonHamonLordOfStrikingThunderFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (!CanSpecialSummonHamonLordOfStrikingThunderFromHand(handZone))
    return FALSE;

  fixedDuelist = (WhoseTurn() == DUEL_PLAYER) ? DUEL_PLAYER : DUEL_OPPONENT;
  SendFaceUpSpellsToGrave(fixedDuelist);

  Duel_ShowCardEffectText(HAMON_LORD_OF_STRIKING_THUNDER,
                          CARD_EFFECT_TEXT_HAMON_LORD_OF_STRIKING_THUNDER_POPUP_1);

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  BlockTurnSummoning(ACTIVE_DUELIST);
  return TRUE;
}

struct DuelCard *HamonLordOfStrikingThunder_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id != HAMON_LORD_OF_STRIKING_THUNDER)
      continue;
    if (!zone->isFaceUp)
      continue;
    if (!zone->isDefending)
      continue;
    return zone;
  }

  return NULL;
}

u8 HamonLordOfStrikingThunder_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == HAMON_LORD_OF_STRIKING_THUNDER)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return HamonLordOfStrikingThunder_GetForcedAttackTarget(
      Duel_FixedDuelistForMonsterRow(fixedRow)) == NULL;
}
