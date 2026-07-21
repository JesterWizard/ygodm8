#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "gladiator_beasts_medusa_shield.h"

void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 IsGladiatorBeast(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

u8 GladiatorBeastsMedusaShield_PreventsDestroy(struct DuelCard *zone)
{
  u8 controller;
  u8 backrow;
  u8 col;
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || !(zone->unk4 & 2) || !IsGladiatorBeast(zone->id))
    return FALSE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return FALSE;

  controller = Duel_FixedDuelistForMonsterRow(fixedRow);
  backrow = controller == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *trap = gFixedZones[backrow][col];

    if (trap != NULL && trap->isFaceUp && trap->id == GLADIATOR_BEASTS_MEDUSA_SHIELD
        && trap->unk4 == (u8)(fixedCol + 1))
      return TRUE;
  }

  return FALSE;
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
    trapZone->unk4 = (u8)(targetCol + 1);
    target->unk4 |= 2; /* effect-destroy protect mark */
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();
}
