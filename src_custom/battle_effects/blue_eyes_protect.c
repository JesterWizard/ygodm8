#include "global.h"
#include "common-chax.h"
#include "blue_eyes_protect.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

static u8 ControllerHasBewdOnFieldOrGy(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;
  u8 i;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == BLUE_EYES_WHITE_DRAGON)
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == BLUE_EYES_WHITE_DRAGON;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == BLUE_EYES_WHITE_DRAGON)
      return TRUE;
  }

  return FALSE;
}

static u8 JetDragonProtected(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 fixedDuelist;

  if (zone == NULL || zone->id != BLUE_EYES_JET_DRAGON || !zone->isFaceUp)
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return FALSE;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  return ControllerHasBewdOnFieldOrGy(fixedDuelist);
}

u8 BlueEyesJetDragon_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return JetDragonProtected(zone);
}

u8 BlueEyesJetDragon_PreventsDestroy(const struct DuelCard *zone)
{
  return JetDragonProtected(zone);
}

u8 BlueEyesSolidDragon_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == BLUE_EYES_SOLID_DRAGON && zone->isFaceUp;
}

u8 BlueEyesSolidDragon_PreventsDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == BLUE_EYES_SOLID_DRAGON && zone->isFaceUp;
}
