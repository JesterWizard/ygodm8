#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define SKILL_DRAIN_LP_COST 1000

unsigned char IsSkillDrainActiveOnField(void)
{
  return Duel_IsBackrowCardOnField(SKILL_DRAIN, TRUE);
}

unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId)
{
  struct DuelCard *zone;
  u8 backrowRow;
  u8 col;
  u8 payerTurn;

  zone = Duel_FindBackrowCardOnField(SKILL_DRAIN, FALSE);
  if (zone == NULL)
    return FALSE;

  if (!zone->isFaceUp) {
    if (!Duel_FindFixedZone(zone, &backrowRow, &col))
      return FALSE;

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
