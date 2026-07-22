#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "gladiator_beast_battled.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 FixedDuelistForZone(struct DuelCard *zone)
{
  u8 fixed = GetDuelistForZone(zone);

  if (fixed <= DUEL_OPPONENT)
    return fixed;
  return WhoseTurn();
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sGladiatorBeastName);
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

static void TryBestiariDestroyOppSpellTrap(struct DuelCard *self)
{
  u8 fixed = FixedDuelistForZone(self);
  u8 oppBack = fixed == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
  u8 oppTurn = TurnDuelistForFixed(fixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[oppBack][col];
    u8 typeGroup;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    typeGroup = GetTypeGroup(zone->id);
    if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
      continue;

    Duel_ShowEffectTextTyped(GLADIATOR_BEAST_BESTIARI, 8);
    Duel_DestroyZone(zone, oppTurn, FALSE);
    NotifyDynamicEquipFieldChanged();
    return;
  }
}

static void TryMurmilloDestroyOppMonster(struct DuelCard *self)
{
  u8 fixed = FixedDuelistForZone(self);
  u8 oppMon = Duel_FixedMonsterRowForDuelist(fixed == DUEL_PLAYER ? DUEL_OPPONENT
                                                                  : DUEL_PLAYER);
  u8 oppTurn = TurnDuelistForFixed(fixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[oppMon][col];

    if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
      continue;

    Duel_ShowEffectTextTyped(GLADIATOR_BEAST_MURMILLO, 8);
    Duel_DestroyZone(zone, oppTurn, FALSE);
    NotifyDynamicEquipFieldChanged();
    return;
  }
}

static void TryEquesteAddGbFromGy(struct DuelCard *self)
{
  u8 fixed = FixedDuelistForZone(self);
  u8 turn = TurnDuelistForFixed(fixed);
  u8 i;
  u16 cardId = CARD_NONE;
  s8 empty;

  empty = FirstEmptyZoneInRow(gTurnHands[turn]);
  if (empty < 0)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turn]->graveyard;
    if (!IsGladiatorBeastMonster(cardId))
      return;
    gTurnDuelistBattleState[turn]->graveyard = CARD_NONE;
  } else {
    for (i = 0; i < GraveyardExpand_GetCount(fixed); i++) {
      u16 gyId = GraveyardExpand_GetCardAt(fixed, i);

      if (!IsGladiatorBeastMonster(gyId))
        continue;
      cardId = GraveyardExpand_RemoveAtFixed(fixed, i);
      GraveyardExpand_SyncLegacyTop(fixed);
      break;
    }
    if (cardId == CARD_NONE)
      return;
  }

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_EQUESTE, 8);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turn], (u8)empty), cardId);
  UpdateDuelGfxExceptField();
}

static void TryDariusSsGbFromGy(struct DuelCard *self)
{
  u8 fixed = FixedDuelistForZone(self);
  u8 turn = TurnDuelistForFixed(fixed);
  u8 monRow = turn == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                     : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  u8 i;
  u16 cardId = CARD_NONE;
  u8 col;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turn]->graveyard;
    if (!IsGladiatorBeastMonster(cardId) || cardId == GLADIATOR_BEAST_DARIUS)
      return;
    if (Duel_SpecialSummonFromGrave(turn, cardId, opts) != DUEL_ACTION_OK)
      return;
  } else {
    for (i = 0; i < GraveyardExpand_GetCount(fixed); i++) {
      u16 gyId = GraveyardExpand_GetCardAt(fixed, i);

      if (!IsGladiatorBeastMonster(gyId) || gyId == GLADIATOR_BEAST_DARIUS)
        continue;
      cardId = GraveyardExpand_RemoveAtFixed(fixed, i);
      GraveyardExpand_SyncLegacyTop(fixed);
      if (Duel_SpecialSummonMonsterId(turn, cardId, opts) != DUEL_ACTION_OK)
        return;
      break;
    }
    if (cardId == CARD_NONE)
      return;
  }

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_DARIUS, 8);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[monRow][col];

    if (zone != NULL && zone->id == cardId) {
      zone->unk4 |= 0x80; /* effects negated stand-in */
      break;
    }
  }
  UpdateDuelGfxExceptField();
}

void GladiatorBeast_TryTagSummonTriggers(struct DuelCard *zone)
{
  if (zone == NULL || gHideEffectText)
    return;

  switch (zone->id) {
  case GLADIATOR_BEAST_BESTIARI:
    TryBestiariDestroyOppSpellTrap(zone);
    break;
  case GLADIATOR_BEAST_MURMILLO:
    TryMurmilloDestroyOppMonster(zone);
    break;
  case GLADIATOR_BEAST_EQUESTE:
    TryEquesteAddGbFromGy(zone);
    break;
  case GLADIATOR_BEAST_DARIUS:
    TryDariusSsGbFromGy(zone);
    break;
  default:
    break;
  }
}
