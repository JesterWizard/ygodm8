#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 BanishRandomOpponentHandCard(void)
{
  s8 handZone;
  struct DuelCard *slot;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);
  if (handZone < 0)
    return FALSE;

  slot = gTurnHands[INACTIVE_DUELIST][handZone];
  if (slot == NULL || slot->id == CARD_NONE)
    return FALSE;

  return Duel_BanishZone(slot, TRUE) != DUEL_ACTION_DUEL_OVER;
}

static u8 BanishOneOpponentFieldCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;

      NotifyDynamicEquipFieldChanged();
      return TRUE;
    }
  }

  return FALSE;
}

static u8 BanishOneOpponentGraveyardCard(void)
{
  u8 fixedDuelist = DUEL_OPPONENT;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (cardId == CARD_NONE)
      return FALSE;

    Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);
    return TRUE;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  if (gyCount == 0)
    return FALSE;

  return Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)(gyCount - 1)) != CARD_NONE;
}

static u8 OpponentFieldHasCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 OpponentGyHasCard(void)
{
  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[DUEL_OPPONENT].graveyard != CARD_NONE;

  return GraveyardExpand_GetCount(DUEL_OPPONENT) > 0;
}

unsigned char CanActivateTRISHULA_DRAGON_OF_THE_ICE_BARRIER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TRISHULA_DRAGON_OF_THE_ICE_BARRIER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TRISHULA_DRAGON_OF_THE_ICE_BARRIER)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * random opp hand + 1 field + 1 GY when available. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0
      || OpponentFieldHasCard() || OpponentGyHasCard();
}

void ActivateTRISHULA_DRAGON_OF_THE_ICE_BARRIEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(TRISHULA_DRAGON_OF_THE_ICE_BARRIER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0) {
    if (!BanishRandomOpponentHandCard())
      return;

    if (IsDuelOver() == TRUE)
      return;
  }

  BanishOneOpponentFieldCard();

  if (IsDuelOver() == TRUE)
    return;

  BanishOneOpponentGraveyardCard();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
