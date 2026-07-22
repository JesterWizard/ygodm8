#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sSanctuaryName[] APPEND_RODATA = "Sanctuary in the Sky";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsSanctuaryOrMentions(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == THE_SANCTUARY_IN_THE_SKY)
    return TRUE;

  return Duel_CardNameContains(cardId, sSanctuaryName);
}

static u8 SanctuaryOnFieldOrGy(void)
{
  u8 fixed;
  u8 i;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    return TRUE;

  for (fixed = 0; fixed < 2; fixed++) {
    if (!GraveyardExpand_IsEnabled()) {
      if (gDuel.duelistbattleState[fixed].graveyard == THE_SANCTUARY_IN_THE_SKY)
        return TRUE;
      continue;
    }

    for (i = 0; i < GraveyardExpand_GetCount(fixed); i++) {
      if (GraveyardExpand_GetCardAt(fixed, i) == THE_SANCTUARY_IN_THE_SKY)
        return TRUE;
    }
  }

  return FALSE;
}

static u16 FindMillTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY) >= 0)
    return THE_SANCTUARY_IN_THE_SKY;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSanctuaryOrMentions(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 MillCardFromDeck(u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s16 deckIndex;
  u8 turnDuelist;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist]) {
      GraveyardExpand_PushTurn(turnDuelist, cardId);
      break;
    }
  }

  return TRUE;
}

static u8 AddAgentEarthFromDeckOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s8 handZone;
  u8 i;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_AGENT_OF_MYSTERU_EARTH) >= 0) {
    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, THE_AGENT_OF_MYSTERU_EARTH, TRUE)
        == DUEL_ACTION_OK)
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard != THE_AGENT_OF_MYSTERU_EARTH)
      return FALSE;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
        THE_AGENT_OF_MYSTERU_EARTH);
    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != THE_AGENT_OF_MYSTERU_EARTH)
      continue;

    GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
        THE_AGENT_OF_MYSTERU_EARTH);
    return TRUE;
  }

  return FALSE;
}

static struct DuelCard *FindFairyTribute(struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;

    if (Duel_CardHasMonsterType(zone->id, TYPE_FAIRY))
      return zone;
  }

  /* May tribute self if Fairy. */
  if (self != NULL && Duel_CardHasMonsterType(self->id, TYPE_FAIRY))
    return self;

  return NULL;
}

static u8 IsOppCardTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  return zone != NULL && zone->id != CARD_NONE;
}

static u8 OppHasCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppCardTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 AgentEarthInDeckOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_AGENT_OF_MYSTERU_EARTH) >= 0)
    return TRUE;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == THE_AGENT_OF_MYSTERU_EARTH;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == THE_AGENT_OF_MYSTERU_EARTH)
      return TRUE;
  }

  return FALSE;
}

static u8 CanMillOrAddPath(void)
{
  if (SanctuaryOnFieldOrGy()) {
    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      return FALSE;
    return AgentEarthInDeckOrGy();
  }

  return FindMillTargetInDeck() != CARD_NONE;
}

static u8 CanTributeDestroyPath(struct DuelCard *self)
{
  return FindFairyTribute(self) != NULL && OppHasCard();
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *fairy;
  u8 fixedDuelist = FixedDuelistForActive();

  if (!IsOppCardTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* dual PickZone needs scratch; auto first Fairy tribute. */
  fairy = FindFairyTribute(self);
  if (fairy == NULL)
    return;

  ClearZoneAndSendMonToGraveyard2(fairy, fixedDuelist);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (self != NULL && self->id == PROTECTOR_OF_THE_AGENTS_MOON)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppCardTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivatePROTECTOR_OF_THE_AGENTS_MOON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != PROTECTOR_OF_THE_AGENTS_MOON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != PROTECTOR_OF_THE_AGENTS_MOON)
    return FALSE;

  /* Link Summon trigger gate missing. Ceiling: OPT mill/add Sanctuary
   * path, else OPT tribute Fairy → destroy 1 opp. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanMillOrAddPath())
    return TRUE;

  return CanTributeDestroyPath(zone);
}

void ActivatePROTECTOR_OF_THE_AGENTS_MOONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 millId;

  Duel_ShowEffectTextTyped(PROTECTOR_OF_THE_AGENTS_MOON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (SanctuaryOnFieldOrGy() && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0) {
    if (AddAgentEarthFromDeckOrGy()) {
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
      return;
    }
  }

  millId = FindMillTargetInDeck();
  if (millId != CARD_NONE) {
    if (!MillCardFromDeck(millId))
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanTributeDestroyPath(self))
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppCardTarget, ResolveDestroyTarget, CancelTargeting, AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
