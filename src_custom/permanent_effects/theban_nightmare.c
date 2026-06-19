#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define THEBAN_NIGHTMARE_BASE_ATK 1500
#define THEBAN_NIGHTMARE_BONUS_ATK 1500

static u8 FixedBackrowForMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return 0xFF;

  return fixedRow == PLAYER_MONSTER_ROW ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 ControllerHasEmptyHandAndBackrow(struct DuelCard *zone)
{
  u8 fixedBackrow;
  u8 fixedDuelist;
  u8 turnDuelist;

  fixedBackrow = FixedBackrowForMonsterZone(zone);
  if (fixedBackrow == 0xFF)
    return FALSE;

  fixedDuelist = fixedBackrow == PLAYER_BACKROW ? DUEL_PLAYER : DUEL_OPPONENT;
  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);

  if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) != 0)
    return FALSE;

  return NumEmptyZonesInRow(gFixedZones[fixedBackrow]) == MAX_ZONES_IN_ROW;
}

static u16 ThebanNightmareCurrentAtk(struct DuelCard *zone)
{
  if (ControllerHasEmptyHandAndBackrow(zone))
    return THEBAN_NIGHTMARE_BASE_ATK + THEBAN_NIGHTMARE_BONUS_ATK;

  return THEBAN_NIGHTMARE_BASE_ATK;
}

u8 ThebanNightmare_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THEBAN_NIGHTMARE)
    return FALSE;

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, ThebanNightmareCurrentAtk(zone), gCardInfo.def);
  return TRUE;
}

#if !defined(__GNUC__)
#error Theban Nightmare stat hook self-check requires GCC
#elif __GNUC__
void ThebanNightmare_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = THEBAN_NIGHTMARE;
  ThebanNightmare_ApplyDynamicZoneStats(&zone);
}
#endif
