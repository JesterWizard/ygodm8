#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gravekeepers_servant.h"
#include "imperial_order.h"
#include "spell_effects.h"

static u8 BackrowForDuelist(u8 duelist)
{
  return (duelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

u8 IsActivatedGravekeepersServantZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == GRAVEKEEPERS_SERVANT && zone->isFaceUp == TRUE;
}

static u8 IsGravekeepersServantActiveForController(u8 controller)
{
  u8 i;
  u8 backrow = BackrowForDuelist(controller);
  struct DuelCard *zone;

  if (IsImperialOrderNegatingSpell(GRAVEKEEPERS_SERVANT))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (IsActivatedGravekeepersServantZone(zone))
      return TRUE;
  }

  return FALSE;
}

u8 IsGravekeepersServantActiveAgainstAttacker(void)
{
  u8 attacker = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 controller = attacker == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return IsGravekeepersServantActiveForController(controller);
}

static u8 AttackerCanMillForGravekeepersServant(void)
{
  u8 attacker = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;

  return gDuelDecks[attacker].cardsDrawn < NumCardsInDeck(attacker);
}

u8 TryPayGravekeepersServantAttackCost(void)
{
  if (!IsGravekeepersServantActiveAgainstAttacker())
    return TRUE;

  if (!AttackerCanMillForGravekeepersServant())
    return FALSE;

  Duel_ShowEffectText(GRAVEKEEPERS_SERVANT);

  if (IsDuelOver() == TRUE)
    return FALSE;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, 1, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  return IsDuelOver() != TRUE;
}

APPEND_TEXT void EffectGravekeepersServant(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(GRAVEKEEPERS_SERVANT);
}
