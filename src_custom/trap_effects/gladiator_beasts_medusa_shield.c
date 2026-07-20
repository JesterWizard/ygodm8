#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 IsGladiatorBeast(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

APPEND_TEXT void EffectGLADIATOR_BEASTS_MEDUSA_SHIELD(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *target = NULL;
  struct DuelCard *trapZone;
  u8 targetCol = 0;

  Duel_ShowTrapResponseText(GLADIATOR_BEASTS_MEDUSA_SHIELD, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsGladiatorBeast(zone->id)) {
      target = zone;
      targetCol = col;
      break;
    }
  }

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (target != NULL && trapZone != NULL) {
    Duel_ActivateContinuousZone(trapZone);
    /* Link via unk4 on trap = target col+1; target gets effect-protect mark. */
    trapZone->unk4 = (u8)(targetCol + 1);
    target->unk4 |= 2;

    /* ponytail: cannot be destroyed by card effects / OPT negate opp monster /
     * if sent GY this turn Set GB Trap from Deck need destroy/negate/GY hooks.
     * Ceiling: continuous face-up + marks only. */
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();

  /* ponytail: needs trapEffect ID + dispatcher wire + PickZone. */
}
