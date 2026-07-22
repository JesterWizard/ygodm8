#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

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

static struct DuelCard *FindOwnOtherWingedBeast(struct DuelCard *self)
{
  return FindOwnOtherWingedBeastFor(ACTIVE_DUELIST, self);
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

static struct DuelCard *FindOppFaceUpMonster(void)
{
  return FindOppFaceUpMonsterFor(ACTIVE_DUELIST);
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

static u8 CanBounceBoth(struct DuelCard *self)
{
  return CanBounceBothFor(ACTIVE_DUELIST, self);
}

static u16 FindHarpieInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsHarpieMonster(cardId) && cardId != HARPIE_HARPIST)
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSearchHarpie(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindHarpieInDeck() != CARD_NONE;
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

void TryHarpieHarpistOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != HARPIE_HARPIST || SummonModeIsSpecial(mode))
    return;

  if (EffectOpt_IsUsed(HARPIE_HARPIST))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (!CanBounceBothFor(turnDuelist, zone))
    return;

  Duel_ShowEffectTextTyped(HARPIE_HARPIST, 8);

  if (!DoBounceBothFor(turnDuelist, zone))
    return;

  EffectOpt_MarkUsed(HARPIE_HARPIST);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateHARPIE_HARPIST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_HARPIST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_HARPIST)
    return FALSE;

  /* NS bounce via TryHarpieHarpistOnNormalSummon (EffectOpt).
   * GY End Phase search (Lv4 WB ≤1500 ATK) needs EP hook.
   * OPT bounce own WB + opp face-up (shares EffectOpt). */
  if (EffectOpt_IsUsed(HARPIE_HARPIST))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanBounceBoth(zone))
    return TRUE;

  /* Search is printed EP-from-GY, not field ignition — keep as thin stand-in. */
  return CanSearchHarpie();
}

void ActivateHARPIE_HARPISTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(HARPIE_HARPIST, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanBounceBoth(self)) {
    if (!DoBounceBothFor(ACTIVE_DUELIST, self))
      return;

    EffectOpt_MarkUsed(HARPIE_HARPIST);
    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  searchId = FindHarpieInDeck();
  if (searchId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
