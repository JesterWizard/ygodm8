#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "substitoad.h"

u8 GetDuelistForZone(struct DuelCard *zone);

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);
void TryActivatingPermanentEffects(void);

static const char sFrogArchetypeName[] APPEND_RODATA = "Frog";

static u8 ControllerHasFaceUpSubstitoad(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == SUBSTITOAD)
      return TRUE;
  }
  return FALSE;
}

u8 Substitoad_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!Duel_CardNameContains(zone->id, sFrogArchetypeName))
    return FALSE;
  if (zone->id == FROG_THE_JAM)
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  return ControllerHasFaceUpSubstitoad(controller);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFrogDeckTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == FROG_THE_JAM)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sFrogArchetypeName))
    return FALSE;

  return !Duel_CardCannotBeSpecialSummoned(cardId);
}

static u16 FindDeckFrogTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFrogDeckTarget(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 frogId;

  if (!IsValidTributeTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  frogId = FindDeckFrogTarget();
  if (frogId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (self != NULL && self->id == SUBSTITOAD)
    MarkMonsterEffectUsed(self);

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, frogId, opts) != DUEL_ACTION_OK)
    return;

  /* Frog battle protect via Substitoad_PreventsBattleDestroy. */

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateSUBSTITOAD(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SUBSTITOAD)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SUBSTITOAD)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FieldHasTributeTarget() && FindDeckFrogTarget() != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateSUBSTITOADEffect(void)
{
  Duel_ShowEffectTextTyped(SUBSTITOAD, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
