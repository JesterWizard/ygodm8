#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHeroName[] APPEND_RODATA = "HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DESTINY_HERO_DECIDER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_IsElementalHeroCard(cardId))
    return TRUE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static s16 FindHeroGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsHeroMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
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

static u8 AddHeroFromGyToHand(s16 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsHeroMonster(cardId))
      return FALSE;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    InitHandSlotFromCard(
        SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
    return TRUE;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsHeroMonster(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

unsigned char CanActivateDESTINY_HERO_DECIDER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DECIDER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DECIDER)
    return FALSE;

  /* EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. Ceiling: GY quick
   * return-on-damage need chain hook. Ceiling: OPT add 1 HERO from GY to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindHeroGyIndex() >= 0;
}

void ActivateDESTINY_HERO_DECIDEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DECIDER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindHeroGyIndex();
  if (gyIndex < 0)
    return;

  if (!AddHeroFromGyToHand(gyIndex))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
