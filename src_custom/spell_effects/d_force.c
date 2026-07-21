#include "global.h"
#include "common-chax.h"
#include "d_force.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 DForceControlsPlasma(u8 fixedDuelist)
{
  return Duel_FindBackrowCard(fixedDuelist, D_FORCE, TRUE) != NULL
      && Duel_FindFixedZoneById(Duel_FixedMonsterRowForDuelist(fixedDuelist),
                                DESTINY_HERO_PLASMA, TRUE) != NULL;
}

static u8 DForcePlasmaController(const struct DuelCard *zone, u8 *fixedDuelist)
{
  u8 row;
  u8 col;

  if (zone == NULL || zone->id != DESTINY_HERO_PLASMA || zone->isFaceUp == FALSE)
    return FALSE;
  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &row, &col))
    return FALSE;

  *fixedDuelist = Duel_FixedDuelistForMonsterRow(row);
  return DForceControlsPlasma(*fixedDuelist);
}

u8 DForce_ShouldBlockDrawPhase(void)
{
  return DForceControlsPlasma(DUEL_PLAYER) || DForceControlsPlasma(DUEL_OPPONENT);
}

u8 DForce_CanTargetPlasmaByCardEffect(const struct DuelCard *target,
                                      u8 effectControllerFixedDuelist)
{
  u8 plasmaController;

  if (!DForcePlasmaController(target, &plasmaController))
    return TRUE;

  return effectControllerFixedDuelist == plasmaController;
}

void ApplyDForcePlasmaAtkBonusToCardInfo(struct DuelCard *zone)
{
  u8 plasmaController;
  u8 opponent;
  u8 gyCount;

  if (!DForcePlasmaController(zone, &plasmaController))
    return;
  if (gCardInfo.atk == 0xFFFF)
    return;

  opponent = plasmaController == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  gyCount = GraveyardExpand_IsEnabled() ? GraveyardExpand_GetCount(opponent)
                                        : (gDuel.duelistbattleState[opponent].graveyard != CARD_NONE);
  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + (u32)gyCount * 100);
}

u8 DForce_PreventsPlasmaEffectDestruction(const struct DuelCard *target)
{
  u8 plasmaController;

  return DForcePlasmaController(target, &plasmaController);
}

u8 DForce_PlasmaCanAttackAgain(const struct DuelCard *attacker)
{
  u8 plasmaController;

  return DForcePlasmaController(attacker, &plasmaController);
}

void TryUnlockDForcePlasmaForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL || attacker->effectUsedThisTurn == TRUE)
    return;
  if (!DForce_PlasmaCanAttackAgain(attacker))
    return;

  attacker->effectUsedThisTurn = TRUE;
  attacker->isLocked = FALSE;
}

/* Parent continuous hooks use the exported DForce_* queries in d_force.h. */
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

static s16 FindPlasmaDeckIndex(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == DESTINY_HERO_PLASMA)
      return (s16)i;
  }

  return -1;
}

static s16 FindPlasmaGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DESTINY_HERO_PLASMA)
      return 0;
    return -1;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_PLASMA)
      return (s16)i;
  }

  return -1;
}

static void AddPlasmaToHand(void)
{
  s8 empty;
  s16 deckIdx;
  s16 gyIdx;
  u8 fixedDuelist;
  u16 cardId;
  u8 i;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  deckIdx = FindPlasmaDeckIndex();
  gyIdx = FindPlasmaGyIndex();
  if (deckIdx < 0 && gyIdx < 0)
    return;

  /* Prefer Deck if both available (AI); player: Deck first as default. */
  if (deckIdx >= 0) {
    fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
    cardId = gDuelDecks[fixedDuelist].cards[deckIdx];
    for (i = (u8)deckIdx; i > gDuelDecks[fixedDuelist].cardsDrawn; i--)
      gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[i - 1];
    gDuelDecks[fixedDuelist].cardsDrawn++;
    InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
    return;
  }

  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  if (GraveyardExpand_IsEnabled()) {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIdx);
  } else {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
  }
  InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
}

static void D_FORCE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(D_FORCE);
  AddPlasmaToHand();
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectD_FORCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(D_FORCE, D_FORCE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
