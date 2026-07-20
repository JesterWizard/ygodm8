#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

void UpdateDuelGfxExceptField(void);

static u8 AnyCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 HasFieldTarget(void)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE)
        return TRUE;
    }
  }

  return FALSE;
}

APPEND_TEXT void EffectRAIGEKI_BREAK(void)
{
  s8 handZone;
  u8 row;
  u8 col;
  struct DuelCard *target = NULL;

  Duel_ShowTrapResponseText(RAIGEKI_BREAK, gTrapEffectData.originCardId);

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0 || !HasFieldTarget()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], AnyCard);
  else
    handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);

  if (handZone >= 0)
    Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][handZone], INACTIVE_DUELIST, FALSE);

  /* Destroy first available field card (AI); player would PickZone — ponytail. */
  for (row = 0; row < 4 && target == NULL; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE) {
        target = zone;
        break;
      }
    }
  }

  if (target != NULL)
    Duel_DestroyZone(target, DUEL_PLAYER, FALSE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: needs trapEffect ID + CheckTrapActivationConditions / Effect dispatch
   * + player PickZone for field target. Ceiling: Effect body only. */
}
