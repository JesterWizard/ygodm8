#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectMAGICAL_ARM_SHIELD(void)
{
  u8 myRow = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  struct DuelCard *attacker;
  s8 empty;
  u8 col;
  struct DuelCard *taken = NULL;

  Duel_ShowTrapResponseText(MAGICAL_ARM_SHIELD, gTrapEffectData.originCardId);

  /* ponytail: attack declare + redirect damage calc need battle hooks.
   * Ceiling: take control of 1 face-up opp monster except origin attacker
   * (Change of Heart style move to our monster row). */

  empty = FirstEmptyZoneInRow(gFixedZones[myRow]);
  if (empty < 0 || ArchlordKristya_IsSpecialSummonLocked()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  attacker = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[oppRow][col];

    if (zone == NULL || !zone->isFaceUp || zone->id == CARD_NONE)
      continue;
    if (attacker != NULL && zone == attacker)
      continue;
    taken = zone;
    break;
  }

  if (taken != NULL) {
    struct DuelCard *dst = gFixedZones[myRow][empty];
    u16 cardId = taken->id;

    dst->id = cardId;
    dst->isFaceUp = TRUE;
    dst->isLocked = FALSE;
    dst->isDefending = FALSE;
    dst->unkTwo = taken->unkTwo;
    dst->unk4 = 2;
    SetPermStage(dst, PermStage(taken));
    dst->willChangeSides = FALSE;
    ClearZone(taken);
    Duel_NotifyMonsterControlSwitched(cardId, myRow);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
