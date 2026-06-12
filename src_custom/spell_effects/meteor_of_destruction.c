#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "meteor_of_destruction.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

#define METEOR_OF_DESTRUCTION_DAMAGE 1000
#define METEOR_OF_DESTRUCTION_LP_THRESHOLD 3000

u8 CanActivateMeteorOfDestruction(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_OPPONENT] > METEOR_OF_DESTRUCTION_LP_THRESHOLD;

  return gDuelLifePoints[DUEL_PLAYER] > METEOR_OF_DESTRUCTION_LP_THRESHOLD;
}

APPEND_TEXT void EffectMeteorOfDestruction(void)
{
  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    if (!CanActivateMeteorOfDestruction())
      return;

    if (WhoseTurn() == DUEL_PLAYER)
      SetOpponentLifePointsToSubtract(METEOR_OF_DESTRUCTION_DAMAGE);
    else
      SetPlayerLifePointsToSubtract(METEOR_OF_DESTRUCTION_DAMAGE);

    HandleAtkAndLifePointsAction();
    CheckLoserFlags();

    ClearZoneAndSendMonToGraveyard(
        gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = METEOR_OF_DESTRUCTION;
      ActivateCardEffectText();
    }
  } else {
    ActivateTrapEffect(METEOR_OF_DESTRUCTION_DAMAGE);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
