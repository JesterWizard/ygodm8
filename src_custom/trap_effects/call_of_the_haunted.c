#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "call_of_the_haunted.h"

void SaveCallOfTheHauntedAttackResume(void);

void TryActivateCallOfTheHauntedOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != CALL_OF_THE_HAUNTED || zone->isFaceUp != FALSE)
      continue;

    FlipCardFaceUp(zone);
    zone->isLocked = TRUE;
  }
}

APPEND_TEXT void EffectCallOfTheHaunted(void)
{
  u16 cardId;
  s8 monsterZone;
  struct DuelCard *summonZone;
  struct DuelCard **monsterRow;

  SaveCallOfTheHauntedAttackResume();

  cardId = GetGraveCardAndClearGrave(INACTIVE_DUELIST);
  monsterRow = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW];
  monsterZone = FirstEmptyZoneInRow(monsterRow);
  if (monsterZone < 0)
    return;

  summonZone = monsterRow[monsterZone];
  summonZone->id = cardId;
  NoteCallOfTheHauntedRevivedMonster((u8)monsterZone);
  ResetPermStage(summonZone);
  ResetTempStage(summonZone);
  summonZone->unk4 = 0;
  UnlockCard(summonZone);
  summonZone->isDefending = FALSE;
  summonZone->isLocked = FALSE;
  summonZone->unkTwo = 0;
  summonZone->unkThree = 0;
  FlipCardFaceUp(summonZone);
  summonZone->willChangeSides = 0;

  ClearZoneAndSendMonToGraveyard(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                                 INACTIVE_DUELIST);
}
