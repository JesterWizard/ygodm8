#include "global.h"
#include "common-chax.h"
#include "aroma_lp_gain.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 FixedRowForController(u8 controller)
{
  return Duel_FixedMonsterRowForDuelist(controller);
}

static struct DuelCard *FindFaceUpById(u8 controller, u16 cardId)
{
  u8 row = FixedRowForController(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == cardId)
      return zone;
  }
  return NULL;
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

static u8 BounceFirstOppSpellTrapToHand(u8 gainingController)
{
  u8 opp = gainingController == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 oppTurn = gTurnDuelistBattleState[ACTIVE_DUELIST]
                   == &gDuel.duelistbattleState[opp]
                   ? ACTIVE_DUELIST
                   : INACTIVE_DUELIST;
  u8 backRow = opp == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 handTurn = oppTurn;
  s8 empty;
  u8 col;

  empty = FirstEmptyZoneInRow(gTurnHands[handTurn]);
  if (empty < 0)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backRow][col];
    u8 typeGroup;
    u16 cardId;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    typeGroup = GetTypeGroup(zone->id);
    if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
      continue;

    cardId = zone->id;
    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[handTurn][empty], cardId);
    return TRUE;
  }
  return FALSE;
}

static void TryBergamotOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_BERGAMOT);

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_BERGAMOT))
    return;
  if (zone->tempStage > 124)
    return;

  zone->tempStage += 2;
  EffectOpt_MarkUsed(AROMAGE_BERGAMOT);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

static void TryCanangaOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_CANANGA);

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_CANANGA))
    return;
  if (!BounceFirstOppSpellTrapToHand(controller))
    return;

  EffectOpt_MarkUsed(AROMAGE_CANANGA);
  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void TryJasmineOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_JASMINE);
  u8 turnDuelist;

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_JASMINE))
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST]
                    == &gDuel.duelistbattleState[controller]
                    ? ACTIVE_DUELIST
                    : INACTIVE_DUELIST;

  if (Duel_DrawCards(turnDuelist, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(AROMAGE_JASMINE);
  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}

static void OnLpGain(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->controller > DUEL_OPPONENT)
    return;
  if (gHideEffectText)
    return;

  TryBergamotOnLpGain(ev->controller);
  TryCanangaOnLpGain(ev->controller);
  TryJasmineOnLpGain(ev->controller);
}

void AromaLpGain_EnsureInit(void)
{
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LP_GAIN, OnLpGain);
}
