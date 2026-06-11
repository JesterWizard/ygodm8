#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

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

static void PaySkillDrainCost(u8 backrowRow)
{
  if (backrowRow == PLAYER_BACKROW)
    SetPlayerLifePointsToSubtract(SKILL_DRAIN_LP_COST);
  else
    SetOpponentLifePointsToSubtract(SKILL_DRAIN_LP_COST);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId)
{
  struct DuelCard *zone;
  u8 backrowRow;

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
    FlipCardFaceUp(zone);
    zone->isLocked = TRUE;
    PaySkillDrainCost(backrowRow);
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
