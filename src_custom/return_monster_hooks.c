#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "duel_helpers.h"

static void ReturnMonsterToOpponentWithNotify(struct DuelCard *zone)
{
  u16 cardId = CARD_NONE;
  u8 newFixedRow = Duel_FixedMonsterRowForDuelist(INACTIVE_DUELIST);

  if (NumEmptyZonesInRow(gTurnZones[1]) != 0) {
    u8 emptyZoneId = FirstEmptyZoneInRow(gTurnZones[1]);

    cardId = zone->id;
    gTurnZones[1][emptyZoneId]->id = zone->id;
    gTurnZones[1][emptyZoneId]->isFaceUp = TRUE;
    gTurnZones[1][emptyZoneId]->isLocked = FALSE;
    gTurnZones[1][emptyZoneId]->isDefending = FALSE;
    gTurnZones[1][emptyZoneId]->unkTwo = zone->unkTwo;
    gTurnZones[1][emptyZoneId]->unk4 = 2;
    SetPermStage(gTurnZones[1][emptyZoneId], PermStage(zone));
    ResetTempStage(gTurnZones[1][emptyZoneId]);
    gTurnZones[1][emptyZoneId]->willChangeSides = FALSE;
  }

  ClearZone(zone);

  if (cardId != CARD_NONE)
    Duel_NotifyMonsterControlSwitched(cardId, newFixedRow);
}

LYN_REPLACE_CHECK(ReturnMonstersToOwner);
APPEND_TEXT void ReturnMonstersToOwner__Replacement(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[2][i]->id == CARD_NONE || !gTurnZones[2][i]->willChangeSides)
      continue;

    ReturnMonsterToOpponentWithNotify(gTurnZones[2][i]);
  }
}
