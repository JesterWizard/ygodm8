#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";
static u8 sDragonlingInit APPEND_DATA = {0};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistForTurn(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsLightswornCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 GyHasLightsworn(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLightswornCard(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 IsLightDragon3000_2600(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_LIGHT)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_DRAGON))
    return FALSE;

  return gCardInfo.atk == 3000 && gCardInfo.def == 2600;
}

static u16 FindDeckLightDragonOrBewd(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurn(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 hasBewd = FALSE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsLightDragon3000_2600(cardId))
      return cardId;
    if (cardId == BLUE_EYES_WHITE_DRAGON)
      hasBewd = TRUE;
  }

  /* ponytail: exact 3000/2600 preferred; BEWD fallback if none. */
  return hasBewd ? BLUE_EYES_WHITE_DRAGON : CARD_NONE;
}

static void OnDragonlingLeaveField(const struct EffectEvent *ev)
{
  u8 turnDuelist;
  u16 cardId;

  if (ev == NULL || ev->cardId != LIGHTSWORN_DRAGONLING || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  /* Separate OPT from on-SS mill / field mill (shared EffectOpt bucket).
   * ponytail: one EffectOpt for all Dragonling effects. */
  if (EffectOpt_IsUsed(LIGHTSWORN_DRAGONLING))
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  cardId = FindDeckLightDragonOrBewd(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(LIGHTSWORN_DRAGONLING, 8);
  if (Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(LIGHTSWORN_DRAGONLING);
  UpdateDuelGfxExceptField();
}

void LightswornDragonling_EnsureInit(void)
{
  if (sDragonlingInit)
    return;

  sDragonlingInit = TRUE;
  /* ON_LEAVE covers destroy + battle-destroy (both emit leave). */
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnDragonlingLeaveField);
}

static u16 FindDeckLightswornExceptSelfFor(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurn(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsLightswornCard(cardId) && cardId != LIGHTSWORN_DRAGONLING)
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindDeckLightswornExceptSelf(void)
{
  return FindDeckLightswornExceptSelfFor(ACTIVE_DUELIST);
}

static u8 SendDeckLightswornToGyFor(u8 turnDuelist, u16 cardId)
{
  s16 deckIndex;
  u8 fixedDuelist = FixedDuelistForTurn(turnDuelist);

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushFixed(fixedDuelist, cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

static u8 SendDeckLightswornToGy(u16 cardId)
{
  return SendDeckLightswornToGyFor(ACTIVE_DUELIST, cardId);
}

u8 CanSpecialSummonLightswornDragonlingFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForActive();

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != LIGHTSWORN_DRAGONLING)
    return FALSE;

  if (!GyHasLightsworn(fixedDuelist))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonLightswornDragonlingFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonLightswornDragonlingFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(LIGHTSWORN_DRAGONLING, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

void TryLightswornDragonlingOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 cardId;

  if (zone == NULL || zone->id != LIGHTSWORN_DRAGONLING || !SummonModeIsSpecial(mode))
    return;

  if (EffectOpt_IsUsed(LIGHTSWORN_DRAGONLING))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  cardId = FindDeckLightswornExceptSelfFor(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(LIGHTSWORN_DRAGONLING, 8);

  if (!SendDeckLightswornToGyFor(turnDuelist, cardId))
    return;

  EffectOpt_MarkUsed(LIGHTSWORN_DRAGONLING);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateLIGHTSWORN_DRAGONLING(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LIGHTSWORN_DRAGONLING)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LIGHTSWORN_DRAGONLING)
    return FALSE;

  /* hand SS when Lightsworn in GY uses FromHand path.
   * On-SS mill via TryLightswornDragonlingOnMonsterPlacement (EffectOpt).
   * Leave → LIGHT Dragon 3000/2600 (or BEWD) via LightswornDragonling_EnsureInit.
   * OPT send 1 other Lightsworn from Deck to GY (shares EffectOpt). */
  if (EffectOpt_IsUsed(LIGHTSWORN_DRAGONLING))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindDeckLightswornExceptSelf() != CARD_NONE;
}

void ActivateLIGHTSWORN_DRAGONLINGEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(LIGHTSWORN_DRAGONLING, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckLightswornExceptSelf();
  if (cardId == CARD_NONE)
    return;

  if (!SendDeckLightswornToGy(cardId))
    return;

  EffectOpt_MarkUsed(LIGHTSWORN_DRAGONLING);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if !defined(__GNUC__)
u8 CanSpecialSummonLightswornDragonlingFromHand(u8 handZone);
u8 TrySpecialSummonLightswornDragonlingFromHand(u8 handZone);
#endif
