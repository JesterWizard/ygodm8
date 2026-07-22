#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "michael_the_arch_lightsworn.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MICHAEL_LP_COST 1000
#define MICHAEL_END_PHASE_MILL 3
#define MICHAEL_SHUFFLE_LP_EACH 300
#define MICHAEL_SHUFFLE_MAX 10

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 sMichaelInit APPEND_DATA = {0};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsOtherLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == MICHAEL_THE_ARCH_LIGHTSWORN)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

/* Auto-shuffle up to MICHAEL_SHUFFLE_MAX other LS (no GY picker). */
static u8 ShuffleOtherLightswornFromGy(u8 fixedDuelist, u8 turnDuelist)
{
  u8 shuffled = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsOtherLightswornMonster(cardId))
      return 0;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    ReturnCardToDeckTop(fixedDuelist, cardId);
    Duel_ShuffleDeckFromDrawn(turnDuelist);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && shuffled < MICHAEL_SHUFFLE_MAX; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (!IsOtherLightswornMonster(cardId))
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i - 1);
    ReturnCardToDeckTop(fixedDuelist, cardId);
    shuffled++;
  }

  if (shuffled > 0) {
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
    Duel_ShuffleDeckFromDrawn(turnDuelist);
  }

  return shuffled;
}

static void OnMichaelDestroyed(const struct EffectEvent *ev)
{
  u8 turnDuelist;
  u8 shuffled;

  if (ev == NULL || ev->cardId != MICHAEL_THE_ARCH_LIGHTSWORN || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  shuffled = ShuffleOtherLightswornFromGy(ev->controller, turnDuelist);
  if (shuffled == 0)
    return;

  Duel_ShowEffectTextTyped(MICHAEL_THE_ARCH_LIGHTSWORN, 8);
  if (Duel_ChangeLp(turnDuelist, (s32)shuffled * MICHAEL_SHUFFLE_LP_EACH, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void MichaelTheArchLightsworn_EnsureInit(void)
{
  if (sMichaelInit)
    return;

  sMichaelInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnMichaelDestroyed);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnMichaelDestroyed);
}

static u8 CanPayMichaelCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= MICHAEL_LP_COST;
}

static u8 IsAnyFieldCardZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FieldHasAnyCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsAnyFieldCardZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsAnyFieldCardZone(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)MICHAEL_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  EffectOpt_MarkUsed(MICHAEL_THE_ARCH_LIGHTSWORN);
  if (self != NULL)
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

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsAnyFieldCardZone(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = PLAYER_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsAnyFieldCardZone(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateMICHAEL_THE_ARCH_LIGHTSWORN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MICHAEL_THE_ARCH_LIGHTSWORN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MICHAEL_THE_ARCH_LIGHTSWORN)
    return FALSE;

  /* EP mill via TryApplyMichaelEndPhase.
   * Destroy→shuffle other LS + LP via MichaelTheArchLightsworn_EnsureInit.
   * OPT pay 1000 LP → banish 1 field card (EffectOpt; Batch13). */
  if (EffectOpt_IsUsed(MICHAEL_THE_ARCH_LIGHTSWORN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanPayMichaelCost() && FieldHasAnyCard();
}

void ActivateMICHAEL_THE_ARCH_LIGHTSWORNEffect(void)
{
  Duel_ShowEffectTextTyped(MICHAEL_THE_ARCH_LIGHTSWORN, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(MICHAEL_THE_ARCH_LIGHTSWORN))
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsAnyFieldCardZone, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

void TryApplyMichaelEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != MICHAEL_THE_ARCH_LIGHTSWORN)
      continue;

    Duel_ShowEffectTextTyped(MICHAEL_THE_ARCH_LIGHTSWORN, 2);
    Duel_MillTopDeckCards(turn, MICHAEL_END_PHASE_MILL, TRUE);
    return;
  }
}
