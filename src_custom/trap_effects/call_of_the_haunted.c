#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "call_of_the_haunted.h"
#include "duel_helpers.h"

void SaveCallOfTheHauntedAttackResume(void);

void TryActivateCallOfTheHauntedOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != CALL_OF_THE_HAUNTED || zone->isFaceUp != FALSE)
      continue;

    Duel_ActivateContinuousZone(zone);
  }
}

APPEND_TEXT void EffectCallOfTheHaunted(void)
{
  s8 monsterZone;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  SaveCallOfTheHauntedAttackResume();

  monsterZone = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterZone < 0)
    return;

  if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, CARD_NONE, opts) != DUEL_ACTION_OK)
    return;

  NoteCallOfTheHauntedRevivedMonster((u8)monsterZone);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST,
                   FALSE);
}
