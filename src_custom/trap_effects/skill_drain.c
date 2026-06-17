#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define SKILL_DRAIN_LP_COST 1000

static struct DuelCard *FindSkillDrainOnBackrow(u8 row)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[row][i];
    if (zone != NULL && zone->id == SKILL_DRAIN)
      return zone;
  }

  return NULL;
}

unsigned char IsSkillDrainActiveOnField(void)
{
  struct DuelCard *zone;

  zone = FindSkillDrainOnBackrow(PLAYER_BACKROW);
  if (zone != NULL && zone->isFaceUp)
    return TRUE;

  zone = FindSkillDrainOnBackrow(OPPONENT_BACKROW);
  if (zone != NULL && zone->isFaceUp)
    return TRUE;

  return FALSE;
}

unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId)
{
  struct DuelCard *zone;
  u8 backrowRow;
  u8 payerTurn;

  zone = FindSkillDrainOnBackrow(OPPONENT_BACKROW);
  if (zone != NULL) {
    backrowRow = OPPONENT_BACKROW;
  } else {
    zone = FindSkillDrainOnBackrow(PLAYER_BACKROW);
    if (zone == NULL)
      return FALSE;
    backrowRow = PLAYER_BACKROW;
  }

  if (!zone->isFaceUp) {
    Duel_ActivateContinuousZone(zone);

    payerTurn = (backrowRow == PLAYER_BACKROW) == (WhoseTurn() == DUEL_PLAYER)
        ? ACTIVE_DUELIST : INACTIVE_DUELIST;
    Duel_ChangeLp(payerTurn, -SKILL_DRAIN_LP_COST, FALSE);
  }

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SKILL_DRAIN;
    gCardEffectTextData.cardId2 = negatedCardId;
    ActivateCardEffectText();
  }

  return TRUE;
}

unsigned char TryActivateSkillDrainAndNegate(void)
{
  return TryActivateSkillDrainAndNegateCardId(gMonEffect.id);
}
