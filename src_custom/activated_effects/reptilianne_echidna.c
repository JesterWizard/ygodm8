#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidOppAtkTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return IsFaceUpMonsterZone(zone);
}

static u8 FieldHasOppAtkTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppAtkTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void SetZoneAtkToZero(struct DuelCard *zone)
{
  u16 baseAtk = gCardData_NEW[zone->id].atk;
  u16 withPerm = Duel_StageModifiedStat(baseAtk, zone->permStage);
  s8 stages = (s8)(-((s32)withPerm + 499) / 500);

  zone->tempStage = stages;
}

static u8 CountOppZeroAtkMonsters(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsFaceUpMonsterZone(zone) || IsGodCard(zone->id))
      continue;

    if (Duel_GetZoneFinalAtk(zone) == 0)
      count++;
  }

  return count;
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u16 FindReptileInDeckExcluding(u16 excludeA, u16 excludeB)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsReptileMonster(cardId))
      continue;

    if (cardId == excludeA || cardId == excludeB)
      continue;

    return cardId;
  }

  return CARD_NONE;
}

static u8 CanSearchReptiles(void)
{
  u8 zeroCount = CountOppZeroAtkMonsters();

  if (zeroCount == 0)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindReptileInDeckExcluding(CARD_NONE, CARD_NONE) != CARD_NONE;
}

static void ResolveAtkZeroTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidOppAtkTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  SetZoneAtkToZero(zone);

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickAtkTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidOppAtkTarget(*outRow, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol < 0 || atk > bestAtk) {
      bestCol = (s8)col;
      bestAtk = atk;
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

static void AddReptilesFromDeck(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 maxAdd = CountOppZeroAtkMonsters();
  u16 addedA = CARD_NONE;
  u16 addedB = CARD_NONE;
  u8 added = 0;

  while (added < maxAdd && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0) {
    u16 cardId = FindReptileInDeckExcluding(addedA, addedB);

    if (cardId == CARD_NONE)
      break;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) != DUEL_ACTION_OK)
      break;

    if (addedA == CARD_NONE)
      addedA = cardId;
    else if (addedB == CARD_NONE)
      addedB = cardId;

    added++;
  }

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateREPTILIANNE_ECHIDNA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != REPTILIANNE_ECHIDNA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != REPTILIANNE_ECHIDNA)
    return FALSE;

  /* Link Summon trigger + Extra Deck lock FALSE.
   * OPT set 1 opp face-up ATK to 0, else OPT add Reptiles up to 0-ATK count.
   * Separate OPT flags share one MarkMonsterEffectUsed. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FieldHasOppAtkTarget())
    return TRUE;

  return CanSearchReptiles();
}

void ActivateREPTILIANNE_ECHIDNAEffect(void)
{
  Duel_ShowEffectTextTyped(REPTILIANNE_ECHIDNA, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (FieldHasOppAtkTarget()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    Duel_SetupPickZone(IsValidOppAtkTarget, ResolveAtkZeroTarget, CancelTargeting,
                       AiPickAtkTarget);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  if (!CanSearchReptiles())
    return;

  AddReptilesFromDeck();
}
