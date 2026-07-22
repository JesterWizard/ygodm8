#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define ARIEL_MAX_BANISH 3

static u8 AnyGraveyardHasCard(void)
{
  u8 fixedDuelist;

  if (!GraveyardExpand_IsEnabled()) {
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != CARD_NONE;
  }

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    if (GraveyardExpand_GetCount(fixedDuelist) > 0)
      return TRUE;
  }

  return FALSE;
}

static u8 BanishUpToThreeFromAnyGraveyard(void)
{
  u8 banished = 0;
  u8 fixedDuelist;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == CARD_NONE)
      return 0;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return 1;
  }

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT && banished < ARIEL_MAX_BANISH;
       fixedDuelist++) {
    while (banished < ARIEL_MAX_BANISH && GraveyardExpand_GetCount(fixedDuelist) > 0) {
      u8 top = (u8)(GraveyardExpand_GetCount(fixedDuelist) - 1);

      if (Duel_BanishGraveyardAtFixed(fixedDuelist, top) == CARD_NONE)
        break;

      banished++;
    }
  }

  if (banished > 0)
    GraveyardExpand_RefreshDisplay();

  return banished;
}

unsigned char CanActivateNAELSHADDOLL_ARIEL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != NAELSHADDOLL_ARIEL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != NAELSHADDOLL_ARIEL)
    return FALSE;

  /* FLIP SS banished Shaddoll + sent-by-effect branch need flip/RFP hooks.
   * Ceiling: OPT banish up to 3 cards from either GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return AnyGraveyardHasCard();
}

void ActivateNAELSHADDOLL_ARIELEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(NAELSHADDOLL_ARIEL, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (BanishUpToThreeFromAnyGraveyard() == 0)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
