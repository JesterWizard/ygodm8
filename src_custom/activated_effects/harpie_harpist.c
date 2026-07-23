#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "harpie_harpist.h"

void UpdateDuelGfxExceptField(void);

static u8 sHarpieHarpistInit APPEND_DATA = {0};
static u8 sHarpistSentToGyMask APPEND_DATA = {0};
/* ponytail: EffectOpt is one flag per cardId — EP search uses a separate turn OPT. */
static u8 sHarpistEpSearchOptUsedMask APPEND_DATA = {0};

static u8 IsWingedBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WINGED_BEAST);
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static struct DuelCard *FindOwnOtherWingedBeastFor(u8 turnDuelist, struct DuelCard *self)
{
  u8 col;
  u8 row = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                         : INACTIVE_DUELIST_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;

    if (IsWingedBeastMonster(zone->id))
      return zone;
  }

  return NULL;
}

static struct DuelCard *FindOppFaceUpMonsterFor(u8 turnDuelist)
{
  u8 col;
  u8 row = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                         : ACTIVE_DUELIST_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (IsCardFaceUp(zone) || zone->isDefending == FALSE)
      return zone;
  }

  return NULL;
}

static u8 CanBounceBothFor(u8 turnDuelist, struct DuelCard *self)
{
  u8 oppTurn = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (FindOwnOtherWingedBeastFor(turnDuelist, self) == NULL)
    return FALSE;

  if (FindOppFaceUpMonsterFor(turnDuelist) == NULL)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[oppTurn]) >= 0;
}

static u16 FindLv4WingedBeastInDeck(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsWingedBeastMonster(cardId))
      continue;

    SetCardInfo(cardId);
    if (gCardInfo.level != 4 || gCardInfo.atk > 1500)
      continue;

    return cardId;
  }

  return CARD_NONE;
}

static u8 GyContainsHarpist(u8 fixedDuelist)
{
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == HARPIE_HARPIST;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == HARPIE_HARPIST)
      return TRUE;
  }

  return FALSE;
}

static u8 DoBounceBothFor(u8 turnDuelist, struct DuelCard *self)
{
  struct DuelCard *ownWb = FindOwnOtherWingedBeastFor(turnDuelist, self);
  struct DuelCard *oppMon = FindOppFaceUpMonsterFor(turnDuelist);

  if (ownWb == NULL || oppMon == NULL)
    return FALSE;

  if (Duel_ReturnMonsterZoneToOwnerHand(ownWb, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  if (Duel_ReturnMonsterZoneToOwnerHand(oppMon, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  return TRUE;
}

static void OnHarpistSentToGy(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != HARPIE_HARPIST)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;

  sHarpistSentToGyMask |= 1 << ev->controller;
}

void HarpieHarpist_EnsureInit(void)
{
  if (sHarpieHarpistInit)
    return;

  sHarpieHarpistInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnHarpistSentToGy);
}

void HarpieHarpist_OnTurnBoundary(void)
{
  sHarpistEpSearchOptUsedMask = 0;
}

void TryApplyHarpieHarpistEndPhase(void)
{
  u8 fixedDuelist;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 bit = 1 << fixedDuelist;
    u8 turnDuelist;
    u16 searchId;

    if (!(sHarpistSentToGyMask & bit))
      continue;

    sHarpistSentToGyMask &= (u8)~bit;

    if (sHarpistEpSearchOptUsedMask & bit)
      continue;

    if (!GyContainsHarpist(fixedDuelist))
      continue;

    turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
    if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
      continue;

    searchId = FindLv4WingedBeastInDeck(fixedDuelist);
    if (searchId == CARD_NONE)
      continue;

    Duel_ShowEffectTextTyped(HARPIE_HARPIST, 4);
    if (Duel_AddDeckCardToHand(turnDuelist, searchId, FALSE) != DUEL_ACTION_OK)
      continue;

    sHarpistEpSearchOptUsedMask |= bit;
    UpdateDuelGfxExceptField();
  }
}

void TryHarpieHarpistOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != HARPIE_HARPIST || SummonModeIsSpecial(mode))
    return;

  if (EffectOpt_IsUsed(HARPIE_HARPIST))
    return;

  {
    u8 fixedRow;
    u8 col;

    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
      return;
    fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  }
  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (!CanBounceBothFor(turnDuelist, zone))
    return;

  Duel_ShowEffectTextTyped(HARPIE_HARPIST, 3);

  if (!DoBounceBothFor(turnDuelist, zone))
    return;

  EffectOpt_MarkUsed(HARPIE_HARPIST);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateHARPIE_HARPIST(void)
{
  /* NS bounce via TryHarpieHarpistOnNormalSummon; EP search via TryApplyHarpieHarpistEndPhase. */
  return FALSE;
}

void ActivateHARPIE_HARPISTEffect(void)
{
  /* Field ignition removed — effects fire from on-summon / EP hooks. */
}
